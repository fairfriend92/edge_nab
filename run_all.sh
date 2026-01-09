#!/bin/bash

# Cmake flag
CMAKE_FIRST=false

# Parse arguements
while [[ $# -gt 0 ]]; do
    case $1 in
        --cmake)
            CMAKE_FIRST=true
            shift
            ;;
        *)
            echo "Usage: ./run_all.sh [--cmake]"
            echo "  --cmake: execute 'cmake ..' before build in build/"
            exit 1
            ;;
    esac
done

# Move to build folder
pushd build 

echo "=== Building ==="

# Execute cmake if flag is true
if [ "$CMAKE_FIRST" = "true" ]; then
    cmake ..
fi
cmake --build . -j

echo "=== Executing ==="

./edge_nab

# Move back to root
popd

echo "=== Plotting with Python ==="
python pyscripts/scores_plotter.py

echo "=== Finished ==="
