import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
import os

# --- Configuration ---
DATA_FILE = "ghidra_metrics_all.csv"
OUTPUT_DIR = "../results/figures"
TABLE_DIR = "../results/tables"

os.makedirs(OUTPUT_DIR, exist_ok=True)
os.makedirs(TABLE_DIR, exist_ok=True)

def main():
    print("=======================================================")
    print("    EXPERIMENT 2: COMPREHENSIVE COMPLEXITY ANALYSIS    ")
    print("=======================================================\n")

    if not os.path.exists(DATA_FILE):
        print(f"Error: {DATA_FILE} not found.")
        return

    df = pd.read_csv(DATA_FILE)
    print(f"Loaded {len(df)} rows of metrics.")

    # Define groups
    llm_groups = ['gemini', 'gpt5']
    
    # Define variants to analyze (Excluding _cff and _stripped due to decompiler failure)
    target_variants = ['_base', '_O0', '_O3', '_clang_O2', '_elit']
    
    results_list = []

    print("\n--- Comparing Complexity Across Variants ---")
    print(f"{'Variant':<12} | {'Human CC':<10} | {'LLM CC':<10} | {'% Diff':<8} | {'p-value':<10}")
    print("-" * 65)

    for variant in target_variants:
        # Filter data
        subset = df[df['Variant'] == variant]
        
        human_cc = subset[subset['Group'] == 'human']['Cyclomatic']
        llm_cc = subset[subset['Group'].isin(llm_groups)]['Cyclomatic']
        
        # Skip if empty
        if len(human_cc) == 0 or len(llm_cc) == 0:
            continue
            
        # Calculate Stats
        h_mean = human_cc.mean()
        l_mean = llm_cc.mean()
        diff = ((l_mean - h_mean) / h_mean) * 100
        
        # Mann-Whitney U Test
        u_stat, p_val = stats.mannwhitneyu(human_cc, llm_cc, alternative='two-sided')
        
        # Store for CSV
        results_list.append({
            'Variant': variant,
            'Human_Mean_CC': h_mean,
            'LLM_Mean_CC': l_mean,
            'Percent_Difference': diff,
            'P_Value': p_val
        })
        
        print(f"{variant:<12} | {h_mean:<10.2f} | {l_mean:<10.2f} | {diff:+.1f}%   | {p_val:.4f}")

    # --- SAVE MASTER TABLE ---
    df_results = pd.DataFrame(results_list).round(3)
    csv_path = os.path.join(TABLE_DIR, "comprehensive_complexity.csv")
    df_results.to_csv(csv_path, index=False)
    print(f"\n[Saved] Comprehensive complexity data to: {csv_path}")

    # --- VISUALIZATION: Complexity Evolution ---
    plt.figure(figsize=(12, 6))
    
    # Filter main DF for plotting
    df_plot = df[df['Variant'].isin(target_variants)].copy()
    df_plot['Origin'] = df_plot['Group'].apply(lambda x: 'Human' if x == 'human' else 'LLM')
    
    sns.barplot(x='Variant', y='Cyclomatic', hue='Origin', data=df_plot, errorbar='ci', palette='muted', order=target_variants)
    
    plt.title('Evolution of Structural Complexity Across Defense Variants')
    plt.ylabel('Mean Cyclomatic Complexity')
    plt.xlabel('Defense Technique')
    plt.legend(title='Code Origin')
    
    plot_path = os.path.join(OUTPUT_DIR, "complexity_evolution.png")
    plt.savefig(plot_path, dpi=300)
    print(f"[Saved] Evolution plot to {plot_path}")

    # --- DECOMPILER FAILURE CHECK (CFF) ---
    print("\n--- Decompiler Resilience (CFF) ---")
    df_cff = df[df['Variant'] == '_cff']
    BROKEN_THRESHOLD = 5
    h_fail = (df_cff[df_cff['Group'] == 'human']['Nodes'] <= BROKEN_THRESHOLD).mean() * 100
    l_fail = (df_cff[df_cff['Group'].isin(llm_groups)]['Nodes'] <= BROKEN_THRESHOLD).mean() * 100
    print(f"Human Failure Rate: {h_fail:.1f}%")
    print(f"LLM Failure Rate:   {l_fail:.1f}%")

if __name__ == "__main__":
    main()
