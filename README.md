# O2 Forward Track Analysis

ROOT-C++ based analysis of forward-track matching in ALICE.  
Computes efficiency and purity metrics from AO2D Monte Carlo data and produces visual and optimization plots.

## Requirements
- ROOT 6.36+ (via conda, see `environment.yml`)
- Bash shell (Linux/macOS or WSL2)


## Setup
```bash
git clone https://github.com/haidaara/ALICE-O2-forward-track-analysis.git
cd O2FwdTrackAnalysis

# download input ROOT file
./scripts/get_data.sh
````

## Usage

```bash
./scripts/run.sh
```

Plots are written under `output/`.

## Structure

```
O2FwdTrackAnalysis/
├── data/       # input data (git-ignored)
├── macros/     # analysis macros (.C/.h)
├── scripts/    # helpers (get_data.sh, run_analysis.sh)
├── output/     # generated results (git-ignored)
└── docs/       # optional docs
```






