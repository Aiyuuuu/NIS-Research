#!/usr/bin/env python3
import os
import subprocess
import itertools
from pathlib import Path
import csv
# --- Configuration ---
# The base path to your output binaries, relative to the project root
OUTPUT_DIR = Path("../output")
OUTPUT_PATHS = sorted([p for p in OUTPUT_DIR.iterdir() if p.is_dir()])
# The groups you want to compare (must match your folder names)
GROUPS = ["human", "gemini", "gpt5"]
# --- NEW: List of variants to test automatically ---
# This list will drive the entire experiment.
VARIANT_SUFFIXES = [
    "_base",
    "O0",
    "_clang_O2",
    "_O3",
    "_cff",
    "_elit",
    "_stripped"
]
def run_command(command):
    """Helper function to run a shell command and return its output."""
    try:
        result = subprocess.run(command, shell=True, check=True, text=True, capture_output=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        # Return stderr if the command fails, which is useful for debugging
        # For sdhash, a non-zero exit can mean "no matches found", which is not an error
        if "sdhash" in command and e.returncode == 1:
            return "" # Return empty string for "no matches"
        return f"ERROR: {e.stderr.strip()}"
def analyze_ssdeep(files, results, task, variant, group):
    """Analyzes a list of files using ssdeep, with a robust comparison method."""
    print(" [ssdeep] Comparing all pairs:")
    if len(files) < 2:
        return
    # Use itertools.combinations to get all unique pairs
    for file1, file2 in itertools.combinations(files, 2):
        hash_file1 = "hash1.tmp"
        # Generate the hash of the first file
        run_command(f'ssdeep "{file1}" > {hash_file1}')
       
        # Compare the second file against the hash of the first file
        command = f'ssdeep -m {hash_file1} "{file2}"'
        output = run_command(command)
       
        score = 0 # Default to 0 if no match is found
        # The output format is: file2 matches file1 (score)
        if "matches" in output:
            try:
                # Find the score in parentheses, e.g., (63)
                score = int(output.split('(')[-1].replace(')', '').strip())
            except (ValueError, IndexError):
                score = "Parse Error"
        fname1 = Path(file1).name
        fname2 = Path(file2).name
        results.append({
            "Task": task,
            "Variant": variant,
            "Group": group,
            "Tool": "ssdeep",
            "File1": fname1,
            "File2": fname2,
            "Score": score
        })
   
    # Clean up the temporary hash file
    if os.path.exists("hash1.tmp"):
        os.remove("hash1.tmp")
def analyze_sdhash(files, results, task, variant, group):
    """Analyzes a list of files using sdhash."""
    print(" [sdhash] Comparing all pairs:")
    if len(files) < 2:
        return
       
    file_list_str = " ".join(f'"{f}"' for f in files)
   
    # Use sdhash's gen-compare mode
    comparison_output = run_command(f"sdhash -g -t 1 --separator csv {file_list_str}")
    if comparison_output:
        for line in comparison_output.splitlines():
            if line.strip():
                parts = line.split(',')
                if len(parts) == 3:
                    f1, f2, sc = parts
                    fname1 = Path(f1.strip()).name
                    fname2 = Path(f2.strip()).name
                    score = sc.strip()
                    results.append({
                        "Task": task,
                        "Variant": variant,
                        "Group": group,
                        "Tool": "sdhash",
                        "File1": fname1,
                        "File2": fname2,
                        "Score": score
                    })
    else:
        print(" No matches found with score >= 1.")
def analyze_radiff2(files, results, task, variant, group):
    """Analyzes pairs of files using radiff2."""
    print(" [radiff2] Comparing all pairs (calculating similarity):")
   
    # Use itertools.combinations to get all unique pairs
    for file1, file2 in itertools.combinations(files, 2):
        command = f'radiff2 -s "{file1}" "{file2}"'
        output = run_command(command)
       
        similarity = "N/A"
        # Parse the output to find the similarity score
        for line in output.split('\n'):
            if "similarity" in line:
                try:
                    similarity = float(line.split()[1])
                    break
                except (ValueError, IndexError):
                    similarity = "Parse Error"
        fname1 = Path(file1).name
        fname2 = Path(file2).name
        results.append({
            "Task": task,
            "Variant": variant,
            "Group": group,
            "Tool": "radiff2",
            "File1": fname1,
            "File2": fname2,
            "Score": similarity
        })
def main():
    """Main function to run the pilot study."""
    project_root = Path(__file__).parent.resolve()
    results = []
    for output_path in OUTPUT_PATHS:
        print("===========================================================")
        print(f" Pilot Study: Intra-Origin Similarity Analysis (Python)")
        print(f" Task: {output_path.name}")
        print("===========================================================")
       
        base_path = project_root / output_path
        # --- NEW: Loop over all the variants in our list ---
        for variant_suffix in VARIANT_SUFFIXES:
            print("\n" + "="*25)
            print(f" ANALYZING VARIANT: {variant_suffix}")
            print("="*25 + "\n")
            for group in GROUPS:
                print(f"--- Analyzing Group: {group} ---")
               
                group_dir = base_path / group
                if not group_dir.is_dir():
                    print(f" [Error] Directory not found: {group_dir}. Skipping.")
                    print()
                    continue
                # Find all files in the directory that end with the specified suffix
                files_to_analyze = sorted([str(p) for p in group_dir.glob(f"*{variant_suffix}")])
                if len(files_to_analyze) < 2:
                    print(f" [Warning] Found fewer than 2 files for group '{group}' with suffix '{variant_suffix}'. Skipping.")
                    print()
                    continue
                   
                print(f" Found {len(files_to_analyze)} files to compare.")
               
                analyze_ssdeep(files_to_analyze, results, output_path.name, variant_suffix, group)
                print()
               
                analyze_sdhash(files_to_analyze, results, output_path.name, variant_suffix, group)
                print()
                analyze_radiff2(files_to_analyze, results, output_path.name, variant_suffix, group)
                print("-------------------------------------")
                print()
    with open("analysis_results.csv", "w", newline="") as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=["Task", "Variant", "Group", "Tool", "File1", "File2", "Score"])
        writer.writeheader()
        writer.writerows(results)
    print("Pilot study complete.")
if __name__ == "__main__":
    main()
