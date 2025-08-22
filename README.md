# O2 Forward Track Analysis

ROOT-C++ based analysis of forward-track matching in ALICE.  
Computes efficiency and purity metrics from AO2D Monte Carlo data and produces visual and optimization plots.


## Setup
```bash
git clone https://github.com/haidaara/ALICE-O2-forward-track-analysis.git
cd O2FwdTrackAnalysis

# download input ROOT file
./scripts/get_data.sh
````

## Usage

```bash
./scripts/compile.sh
./scripts/run.sh
```

Plots are written under `output/`.






