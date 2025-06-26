# DISCRETE STRUCTURE - ASSIGNMENT ON TRAVELING SALESMAN PROBLEM AND APPLYING BELLMAN-FORD

## Introduction
**Author:** Mai Hong Phuoc
**University:** HCMUT


This repository is part of my study on 2 algorithms to solve the Traveling Salesman Problem and generate the <kbd>DiscreteStructure_ReportOnTSM.pdf</kbd>


These are two main approaches to solve the TSM Problem:
- Held-Karp Algorithm
- Simulated Annealing Algorithm
## File Structure
| File | Description |
|------|-------------|
|`main.cpp`| Contain the `main` function where process the input file `.txt` and process the program|
|`bellman.cpp`| Implementing `Bellman Ford algorithm`|
|`tsm.cpp`| Implementing 2 algorithms|

## How to run on Windows ##
Enter this code in the terminal tab:
1. `cls`
2. `g++ -o main main.cpp tsm.cpp bellman.cpp -I . -std=c++11`
3. `.\main`


## How to config input file ##
1. Create a `.txt` file
2. Fill the blank with config `a b c`
   - `a` starting city
   - `b` ending city
   - `c` traveling cost between 2 cities
    ![Sample input]()
