# DISCRETE STRUCTURE - ASSIGNMENT ON TRAVELING SALESMAN PROBLEM AND APPLYING BELLMAN-FORD
>**Coure Project - Faculty of Computer Science - HCMUT**

---
## ✍️ Introduction

| Field | Information |
|---------|---------------|
| **Name**| Mai Hong Phuoc |
|**Email**| mhp230306@gmail.com|

---
##📚  Overview
This repository is part of my study on 3 algorithms to solve the Traveling Salesman Problem, Finding The Shortest Path and generate the `DiscreteStructure_ReportOnTSM.pdf`

Algorithms implemented:

|#|Algorithm|Purpose|
|--|--------|-------|
|1| Held-Karp|Exact solution for graph with less than 20 vertices|
|2| Simulated Anneadling | Heuristic approach to get the near-optimal solution for larger TSP|
|3| Bellman Ford| Shortest Path between two different vertices|

## 📂 Project Layout
|#| File | Description |
|-|----|-------------|
|1|`main.cpp`| Contains the `main` function which process the input file `.txt` prints result|
|2|`bellman.cpp`| Implementing `Bellman Ford algorithm`|
|3|`tsm.cpp`| Implementation of Held–Karp & Simulated Annealing|

## ⚙️ Build and run 
###  Windows (PowerShell / Cmd)
   ``` Powershell
cls; g++ -o main main.cpp tsm.cpp bellman.cpp -I . -std=c++11;.\main
```


### MacOS
``` Powershell
clear &&\
 g++ -std=c++17 -O2 -Wall -I. -o main main.cpp tsm.cpp bellman.cpp &&\
 ./main
```
## Input format
1. Create a `.txt` file
2. Fill the blank with config `a b c`
   - `a` starting city
   - `b` ending city
   - `c` traveling cost between 2 cities
     ``` Powershell
         65 66 10
         65 67 15
         65 68 20
     ```
