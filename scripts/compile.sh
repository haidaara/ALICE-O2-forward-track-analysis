#!/bin/bash
# Simple script to compile all ROOT macros

echo "Compiling macros in 'macros/' directory..."

# Change to the macros directory
cd macros

# Compile the macros using ROOT in batch mode
root -l -b << EOF
.L O2fwdtrack.C+
.L O2fwdtrackHelpers.C+
.L O2fwdtrackEfficiency.C+
.L O2fwdtrackGraphing.C+
.q
EOF

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
else
    echo "Compilation failed. Please check for errors."
    exit 1
fi