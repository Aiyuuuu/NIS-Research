import os
import json
import pandas as pd

# Define paths relative to this script location
current_dir = os.path.dirname(os.path.abspath(__file__))
metrics_dir = os.path.join(current_dir, "../metrics")
output_csv = os.path.join(current_dir, "../ghidra_metrics_all.csv")

all_data = []

print(f"Walking through metrics directory: {metrics_dir}")

if not os.path.exists(metrics_dir):
    print(f"Error: Metrics directory not found at {metrics_dir}")
    exit(1)

# Walk the directory tree recursively
for root, dirs, files in os.walk(metrics_dir):
    for filename in files:
        if filename.endswith(".json"):
            filepath = os.path.join(root, filename)
            
            # Get path relative to the metrics root to extract Task/Group
            # Structure is: metrics/TASK/GROUP/filename.json
            rel_path = os.path.relpath(filepath, metrics_dir)
            path_parts = rel_path.split(os.sep)
            
            # Safety check: ensure we are deep enough (Task/Group/File)
            if len(path_parts) < 3:
                print(f"Skipping malformed path: {rel_path}")
                continue

            task_name = path_parts[0]  # e.g., T1_WordCount
            group_name = path_parts[1] # e.g., human, gpt5
            
            with open(filepath, "r") as f:
                try:
                    data = json.load(f)
                    basename = data.get('basename', filename.replace('.json', ''))
                    
                    # Extract variant from filename (e.g. 1_base -> _base)
                    # Split by underscore, usually the last part is the variant
                    # But sometimes filenames are complex. 
                    # Known variants: _base, _O0, _O3, _cff, _elit, _stripped, _clang_O2
                    
                    variant = "unknown"
                    possible_variants = ["_base", "_O0", "_O3", "_cff", "_elit", "_stripped", "_clang_O2"]
                    
                    for v in possible_variants:
                        if basename.endswith(v):
                            variant = v
                            break
                    
                    # Fallback if O0 (which doesn't start with underscore in your naming sometimes)
                    if variant == "unknown" and basename.endswith("O0"):
                        variant = "O0"

                    entry = {
                        'Task': task_name,
                        'Group': group_name,
                        'Variant': variant,
                        'Basename': basename,
                        'Cyclomatic': data.get('cyclomatic_est', 0),
                        'Nodes': data.get('nodes', 0),
                        'Edges': data.get('edges', 0),
                        'Decompiled_Len': data.get('decompiled_text_len', 0)
                    }
                    all_data.append(entry)
                except Exception as e:
                    print(f"Error reading {filename}: {e}")

if all_data:
    df = pd.DataFrame(all_data)
    # Sort for cleaner CSV
    df = df.sort_values(by=['Task', 'Group', 'Variant'])
    df.to_csv(output_csv, index=False)
    print(f"Success! Merged {len(all_data)} files.")
    print(f"CSV saved to: {output_csv}")
    print(df.head())
else:
    print("No valid JSON files found.")
