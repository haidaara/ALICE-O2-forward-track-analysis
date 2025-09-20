>From table of content : 
>3. methodology and framework analysis
    |- file organisation
    |- fct hierarchy
    |- sepcific def of purity/effic 
    |- specific explanation of match and count process
    + Batoul mentioned in comment a possibility of Mc simulation ( i think it's better to mention it here in intro )

---

### 3.Analysis methodology and Software framework 

##### **3.1 File Organisation**

The analysis is built on a ROOT-based framework. The core class, `O2fwdtrack`, is automatically generated from the TTree structure.

*   **`O2fwdtrack.h`**: Contains the class definition, data structures, and function declarations.
*   **`O2fwdtrack.C`**: The main file containing the `Loop()` function. The core functionality is divided into two main parts:
    *   Plotting available branches by invoking basic helper functions for branch variables
    *   Invoking efficiency/purity calculation through the `CalculateEfficiencyPurity()` function
*   **`O2fwdtrackEfficiency.C`**: Contains the core logic for efficiency/purity calculation within `CalculateEfficiencyPurity()`. All other related functions are invoked from within this function.
*   **`O2fwdtrackGraphing.C`**: Handles all visualization and results extraction via the `ReportAndOptimize()` function.
*   **`O2fwdtrackHelpers.C`**: Provides utility functions for initializing, filling, and plotting basic histograms of track variables.

##### **3.2 Function Hierarchy and Workflow**

As mentioned in Section 3.1, the implementation consists of two main functional parts. The first part handles basic histogram operations for the `O2fwdtrack` branch different variable: initializing histograms, filling them with branch variable entries, and plotting the results. The second part, which is the focus of this analysis, deals with efficiency and purity calculations, primarily orchestrated by the `CalculateEfficiencyPurity()` function.

The efficiency/purity analysis follows a structured workflow consisting of several specialized functions:

0.  **Main Orchestration (`CalculateEfficiencyPurity()`)**:
    Coordinates the entire efficiency/purity calculation process through several specialized sub-functions called inside it.

1.  **Histogram Creation (`CreateEfficiencyPurityHistograms()`)**:
    Initializes 1D and 2D histograms for all defined analysis variables but does not fill them with data.

2.  **Candidate Collection (`CollectMatchCandidates()`)**:
    Iterates through all entries and filters matched tracks. Instead of filling histograms directly, matching entries are stored in a vector of `MatchCandidate` objects for subsequent processing.

3.  **Best Match Selection (`SelectBestMatches()`)**:
    For each MCH track, evaluates its candidate matches and selects the one with the smallest `fChi2MatchMCHMFT` value that falls below the defined threshold (`fChi2Threshold`). The selected candidates are stored in a `BestMatch` vector also.

4.  **Histogram Filling (`FillEfficiencyPurityCounts()`)**:
    Processes entries again to populate denominator and numerator histograms for both efficiency and purity calculations. This function considers track types and utilizes the `bestMatches` map while also maintaining four essential counters: `nTotalType3`, `nMatchedType3`, `nTotalType0`, and `nTrueType0`.

5.  **Result Calculation & Optimization (`ReportAndOptimize()`)**:
    Computes final efficiency and purity values from the accumulated counters. Performs a comprehensive scan of χ² thresholds to identify the optimal value that maximizes the product of efficiency and purity. Finally, invokes graphing functions to generate all output visualizations.

The latter two functions implement sophisticated filling and reporting methodologies based on the precise definitions of efficiency and purity ratios, which are elaborated in the following section.



#### **3.3 Def of efficiency and purity**

The analysis uses the following rigorous definitions, which directly dictate the histogram filling logic:
*   **Efficiency (ε):** The probability that a true standalone muon (MCH-MID) track is correctly matched to its true MFT counterpart.
    *   **Numerator:** True matched global muons (`nMatchedType3`). Filled from the `bestMatches` map for type 3 tracks where `fMcMask == 0`.
    *   **Denominator:** All MCH-MID tracks in acceptance (`nTotalType3`). Filled from all type 3 tracks within `-3.6 < η < -2.5`.
    *   **Formula:** $ε = \frac{N^{matched}_{true\ Type3}}{N^{total}_{Type3}}$

*   **Purity (P):** The probability that a selected global muon track is a true match, not a combinatorial fake.
    *   **Numerator:** True global muons (`nTrueType0`). Filled from type 0 tracks where `fMcMask == 0`.
    *   **Denominator:** All selected global muons (`nTotalType0`). Filled from all type 0 tracks .
    *   **Formula:** $P = \frac{N^{true}_{Type0}}{N^{total}_{Type0}}$

Based on these definitions, we carefully build the two numerators and two denominators needed for our calculations. As the code runs through different types of tracks in separate steps, it keeps track of four important numbers: `nTotalType3`, `nMatchedType3`, `nTotalType0`, and `nTrueType0`. 

The respective ratio of these variable - matched Type 3 over total Type 3 for efficiency, and true Type 0 over total Type 0 for purity - we get the final efficiency and purity values that you see reported. What's really useful is that these numbers match up with what we get when we look at the average values from our efficiency and purity plots, which helps confirm that the analysis methodology is internal consistent.

#### about the matching process how it was done, 
it's simply using the existed branch in the TTree, the mcmatch branch indicate by it's bool number "0" or "127" if the track is matched to the mcsimulation or not
{ good to show here a breif code description}

{it may be good also to mention the intervention of mc simulation at this stage}

Monte Carlo simulation is fundamental to this analysis. The `fMcMask` branch provides the ground truth required to define *"true"* matches.
*   A value of `fMcMask == 0` identifies a track that is correctly matched to a generated muon from the simulation, whereas a `fMCMask == 127` the opposite 
*   The use of MC enables the optimization of reconstruction criteria (like the χ² threshold) on simulated data before being applied to real data, and provides a benchmark for the maximum achievable performance of the matching algorithm.


#### **3.4 Matching Process Implementation**

The matching process utilizes the existing `fMcMask` branch from the TTree, which provides MC truth information:

```cpp
// As implemented in CollectMatchCandidates() and FillEfficiencyPurityCounts()
if (fMcMask == 0) {
    // Identifies true match to generated muon
    // Used to fill efficiency numerator and purity numerator
} else {
    // Indicates background or combinatorial match
}
```

The Monte Carlo simulation is fundamental to this analysis, with the `fMcMask` branch providing essential ground truth as mentionned in the above monte carlo section
- Value of `0`: Correct match to generated muon (true positive)
- Value of `127`: Background or combinatorial match (false positive)

This MC truth information enables:
1. Optimization of reconstruction criteria (χ² threshold) on simulated data
2. Establishment of performance benchmarks for the matching algorithm
3. Unambiguous definition of "true" matches for efficiency and purity calculations

The implementation follows the workflow in `CalculateEfficiencyPurity()` where candidate matching, selection, and validation are all based on this MC truth information.