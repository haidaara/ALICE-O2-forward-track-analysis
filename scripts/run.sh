#!/bin/bash
# Script to run the analysis using pre-compiled shared libraries

echo "Running analysis..."

# Get the project root directory
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
echo "Project root: $PROJECT_ROOT"

# Create output directories if they don't exist
mkdir -p $PROJECT_ROOT/output/png_graph_class

# Run the analysis from the project root directory
cd $PROJECT_ROOT

# Run the analysis using pre-compiled shared libraries
root -l -b << 'EOF'
// Load the pre-compiled shared libraries
.L ./macros/O2fwdtrackHelpers_C.so
.L ./macros/O2fwdtrackEfficiency_C.so
.L ./macros/O2fwdtrackGraphing_C.so
.L ./macros/O2fwdtrack_C.so

// Create instance and run analysis
O2fwdtrack fwd;
fwd.Loop();

.q
EOF

