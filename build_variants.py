import os
import sys
import subprocess
import shutil
import time
from pathlib import Path

# --- CONFIGURATION ---
CORPUS_DIR = "corpus"
OUTPUT_DIR = "output"

TASKS_TO_PROCESS = [
    "T1_WordCount",
    # "T2_BubbleSort",
    # "T3_RecursiveFactorial",
    # "T4_LinkedList",
    # "T5_Calculator",
]

# --- SCRIPT LOGIC ---

def cleanup():
    print("\n--- ERROR DETECTED: CLEANING UP ALL GENERATED FILES ---")
    output_path = Path(OUTPUT_DIR)
    if output_path.exists():
        try:
            shutil.rmtree(output_path)
            print(f"Successfully deleted output directory: {output_path}")
        except OSError as e:
            print(f"[CRITICAL] Failed to delete output directory {output_path}: {e}")
    else:
        print("Output directory not found. Nothing to clean.")

def run_command(command, description):
    print(f"    - {description}...")
    try:
        timeout = 300 
        subprocess.run(
            command,
            check=True,
            capture_output=True,
            text=True,
            shell=False,
            timeout=timeout
        )
    except Exception as e:
        cmd_str = " ".join(map(str, command))
        print(f"\n[FATAL ERROR] Command failed: {cmd_str}", file=sys.stderr)
        if isinstance(e, subprocess.CalledProcessError):
            print(f"  Exit Code: {e.returncode}", file=sys.stderr)
            if e.stdout and e.stdout.strip(): print(f"  STDOUT:\n{e.stdout.strip()}", file=sys.stderr)
            if e.stderr and e.stderr.strip(): print(f"  STDERR:\n{e.stderr.strip()}", file=sys.stderr)
        else:
            print(f"  Exception: {e}", file=sys.stderr)
        cleanup()
        sys.exit(1)

def main():
    if Path(OUTPUT_DIR).exists():
        print(f"--- Deleting existing '{OUTPUT_DIR}' directory for a clean build ---")
        shutil.rmtree(OUTPUT_DIR)

    print("--- Starting Binary Generation Pipeline ---")
    
    corpus_path = Path(CORPUS_DIR)
    if not corpus_path.is_dir():
        print(f"[FATAL ERROR] Corpus directory '{CORPUS_DIR}' not found.", file=sys.stderr)
        sys.exit(1)

    source_files_to_process = []
    for task_name in TASKS_TO_PROCESS:
        task_path = corpus_path / task_name
        if task_path.is_dir():
            source_files_to_process.extend(sorted(list(task_path.glob("**/*.c"))))

    if not source_files_to_process:
        print("[WARNING] No source files found to process. Exiting.")
        return

    for source_path in source_files_to_process:
        print(f"\n[+] Processing Source File: {source_path}")

        relative_path = source_path.relative_to(corpus_path)
        output_base_dir = Path(OUTPUT_DIR) / relative_path.parent
        base_name = source_path.stem
        output_base_dir.mkdir(parents=True, exist_ok=True)
        
        # --- Baseline Variant ---
        baseline_path = output_base_dir / f"{base_name}_base"
        run_command(["gcc", "-O2", "-pie", str(source_path), "-o", str(baseline_path)], "Building baseline")

        # --- Optimization Variants ---
        run_command(["gcc", "-O0", "-pie", str(source_path), "-o", str(output_base_dir / f"{base_name}_O0")], "Building opt-variant (O0)")
        run_command(["gcc", "-O3", "-pie", str(source_path), "-o", str(output_base_dir / f"{base_name}_O3")], "Building opt-variant (O3)")
        run_command(["clang", "-O2", "-pie", str(source_path), "-o", str(output_base_dir / f"{base_name}_clang_O2")], "Building opt-variant (clang O2)")

        # --- Stripped Variant ---
        stripped_path = output_base_dir / f"{base_name}_stripped"
        print("    - Building stripped...")
        shutil.copy2(baseline_path, stripped_path)
        run_command(["strip", str(stripped_path)], "Stripping binary")

        # --- Tigress Variants ---
        seed = str(int(time.time() * 1e9))
        
        # *** THE ONLY CHANGE IS HERE: The Tigress pre-processing step ***
        prepped_source_temp = None
        try:
            # Step 1: Create a temporary, pre-processed source file for Tigress
            print("    - Pre-processing source for Tigress...")
            original_code = source_path.read_text()
            prepped_code = "#include<stdlib.h>;\n"+"#include <time.h>;\n" + original_code
            prepped_source_temp = output_base_dir / f"{base_name}_prepped_temp.c"
            prepped_source_temp.write_text(prepped_code)

            # --- Control-Flow Flattening ---
            flat_source_temp = output_base_dir / f"{base_name}_flat_temp.c"
            flat_binary = output_base_dir / f"{base_name}_cff"
            cff_command = ["tigress", f"--Seed={seed}", "--Transform=Flatten", "--Functions=*", f"--out={flat_source_temp}", str(prepped_source_temp)]
            run_command(cff_command, "Transforming with CFF")
            run_command(["gcc", "-O2", "-pie", str(flat_source_temp), "-o", str(flat_binary)], "Building CFF binary")
            os.remove(flat_source_temp)

            # --- EncodeLiterals ---
            elit_source_temp = output_base_dir / f"{base_name}_elit_temp.c"
            elit_binary = output_base_dir / f"{base_name}_elit"
            elit_command = [
                "tigress", f"--Seed={seed}",
                "--Transform=InitOpaque", "--Functions=main", "--InitOpaqueStructs=list,array",
                "--Transform=InitEntropy",
                "--Transform=EncodeLiterals", "--Functions=*",
                f"--out={elit_source_temp}", str(prepped_source_temp)
            ]
            run_command(elit_command, "Transforming with InitOpaque+EncodeLiterals")
            run_command(["gcc", "-O2", "-pie", str(elit_source_temp), "-o", str(elit_binary)], "Building EncodeLiterals binary")
            os.remove(elit_source_temp)

        finally:
            # Ensure the pre-processed temp file is always deleted
            if prepped_source_temp and prepped_source_temp.exists():
                os.remove(prepped_source_temp)

    print("\n--- Build process completed successfully. ---")

if __name__ == "__main__":
    main()
