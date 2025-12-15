#!/bin/bash

# --- Configuration ---
# UPDATE THIS PATH TO YOUR GHIDRA INSTALLATION:
GHIDRA_HOME="/home/ayan/ghidra/ghidra_11.4.2_PUBLIC_20250826/ghidra_11.4.2_PUBLIC"

# Paths relative to where this script is located (scripts/ghidra_scripts/)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
METRICS_ROOT="$SCRIPT_DIR/../metrics"
OUTPUT_DIR="$SCRIPT_DIR/../../output"

# Project Configuration
PROJECT_PARENT_DIR="/tmp/ghidra_projects"
PROJECT_NAME="MTD_Analysis"

# --- Setup Directories ---
mkdir -p "$METRICS_ROOT"
mkdir -p "$PROJECT_PARENT_DIR"

echo "------------------------------------------------"
echo "Ghidra Home:    $GHIDRA_HOME"
echo "Input Binaries: $OUTPUT_DIR"
echo "Output JSONs:   $METRICS_ROOT"
echo "------------------------------------------------"

if [ ! -f "$GHIDRA_HOME/support/analyzeHeadless" ]; then
    echo "Error: analyzeHeadless not found."
    exit 1
fi

# --- The Batch Loop ---
# Find all binaries. We use -relpath logic to mirror the structure.
cd "$OUTPUT_DIR"
find . -type f ! -name "*.c" | while read binary_rel_path; do
    # binary_rel_path is something like "./T1_WordCount/human/1_base"
    
    # 1. Determine the full path to the binary
    FULL_BINARY_PATH="$OUTPUT_DIR/${binary_rel_path#./}"
    
    # 2. Determine the subfolder structure (e.g., T1_WordCount/human)
    SUBDIR=$(dirname "${binary_rel_path#./}")
    
    # 3. Create the specific metrics directory
    TARGET_METRICS_DIR="$METRICS_ROOT/$SUBDIR"
    mkdir -p "$TARGET_METRICS_DIR"
    
    echo "Analyzing: ${binary_rel_path#./}"
    echo "  -> Saving to: metrics/$SUBDIR"
    
    # Run Ghidra Headless
    # We pass the SPECIFIC target folder to the python script
    "$GHIDRA_HOME/support/analyzeHeadless" \
        "$PROJECT_PARENT_DIR" "$PROJECT_NAME" \
        -import "$FULL_BINARY_PATH" \
        -scriptPath "$SCRIPT_DIR" \
        -postScript statistics.py "$TARGET_METRICS_DIR" \
        -deleteProject \
        -overwrite > /dev/null 2>&1 # Suppress massive log output, show only echo above
        
done

echo "Batch analysis complete."
