#!/bin/bash

echo "Compiling macros in 'macros/' directory..."

# Compile the macros using ROOT in batch mode
## The macros have cross-dependencies that need to be compiled in the right order
root -l -b  << EOF
.L ./macros/O2fwdtrackHelpers.C++
.L ./macros/O2fwdtrackEfficiency.C++
.L ./macros/O2fwdtrackGraphing.C++
.L ./macros/O2fwdtrack.C++

.q
EOF

