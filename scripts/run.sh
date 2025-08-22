#!/bin/bash
# Simple script to run the analysis

echo "Running analysis..."

# Create output directories if they don't exist
mkdir -p output/png_graph_class

# Run the main macro from the project root directory
root -l -b -q 'macros/O2fwdtrack.C+("")'

echo "Analysis complete. Check the 'output/' directory for results."