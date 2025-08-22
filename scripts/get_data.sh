#!/usr/bin/env bash
set -euo pipefail

# Script to download the large AO2D MC file from Google Drive
# Usage: ./scripts/get_data.sh

# Create data directory if it doesn't exist
mkdir -p data

# File details
FILE_NAME="AO2D_MC_promptJpsi_anch24_merged.root"
FILE_ID="1RVJx9ERosOMWxJU09zPRCHhBwwQ8dUBp"
DESTINATION="data/${FILE_NAME}"

# Check if file already exists
if [ -f "$DESTINATION" ]; then
    echo "Data file already exists at $DESTINATION"
    exit 0
fi

echo "Downloading data file from Google Drive..."

# Determine available download tool
if  command -v wget &> /dev/null; then
    DOWNLOAD_CMD="wget"
else
    echo "Error:  wget is not available. Please install one of them."
    exit 1
fi

# Download from Google Drive
    wget --no-check-certificate -O "$DESTINATION" "https://drive.google.com/uc?export=download&id=${FILE_ID}"

# Check if download was successful
if [ $? -eq 0 ] && [ -f "$DESTINATION" ]; then
    echo "Successfully downloaded data to $DESTINATION"
else
    echo "Error: Download failed. Please check the file ID and your internet connection."
    rm -f "$DESTINATION"  # Clean up partial download
    exit 1
fi