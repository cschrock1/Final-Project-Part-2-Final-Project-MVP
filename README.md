# Final-Project-Part-2-Final-Project-MVP

# Log File Analyzer Optimization Project

## Overview
This project compares a baseline and optimized C implementation of a log file analyzer that processes server logs and computes:
- Total requests
- Error rate
- IP address frequency


## Baseline Approach
- Linked list data structure
- Linear search for IP lookup (O(n))
- Frequent dynamic memory allocation (malloc per node)
- Poor cache performance due to pointer chasing


## Optimized Approach
- Hash table with open addressing
- O(1) average lookup time
- Single contiguous memory allocation (calloc)
- Improved cache locality and reduced memory overhead


## Compile Instructions

### Baseline
gcc -Wall baseline.c -o baseline

### Optimized
gcc -Wall optimized.c -o optimized


## Run Instructions

./baseline logfile.txt
./optimized logfile.txt


## Benchmarking
Run both programs on identical log files:
- 10MB
- 50MB
- 100MB

Each test should be run 5 times and median execution time recorded.


## Expected Outcome
The optimized version demonstrates significantly faster execution due to:
- Improved cache locality
- Reduced time complexity
- Elimination of pointer-based traversal