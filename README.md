# Programming Assignment 1 – Matching and Verifying

## Course & Authors
* **Course:** COP 4533 – Algorithm Abstraction and Design (University of Florida)
* **Team Members:**
    * Hung Hong (UFID: 56253262)
    * Thyssen Nicholas (UFID: 19705329)

**Contributions**
- Part A (Matcher): Hung Hong  
- Part B (Verifier): Thyssen Nicholas  



## Overview
This project implements the **Hospital-Proposing Gale–Shapley algorithm** for the stable matching problem. It consists of two primary components:
1.  **Matcher:** A hospital-proposing engine that produces a stable matching.
2.  **Verifier:** A separate tool that checks if a matching is **valid** (one-to-one) and **stable** (no blocking pairs)

---

## Project Structure
```text
.
├── bin/                # Compiled executables
├── data/               # Input data
├── result/             # Output files
├── src/                # Source code
├── tests/              # Unit tests
├── Makefile            # Build system
└── README.md           # Documentation
```
---

## Build & run Instructions
## 1. Build
To compile the matcher, verifier, and input generator into the bin/ directory:
```bash
make
```
## 2. Run the Matcher (Task A)
To run the matching engine on the provided example input:
```bash
make example
```
This targets the data/example.in file and saves the result to result/match.out.

## 3. Run the Verifier (Task B)
To check the validity and stability of the current matching result:

```bash
make check
```
The verifier pipes the preference data and the matcher's output together to evaluate stability.

## 4. Scalability Testing (Task C)
To generate random inputs and collect timing data for $n = \{1, 2, 4, \dots, 512\}$:
```bash
make scale-matcher
make scale-verifier
```
----
# Task C: Scalability Analysis

We analyzed the performance of the Matcher and Verifier by measuring execution time against the number of participants ($n$).

---
![Time VS Data Graph For Matcher Function](read_me_files/image.png)

![Time VS Data Graph For Verifier Function](read_me_files/image2.png)

From the graphs above, we can see that as the number of hospitals and students increases, the running time of the algorithm seems to grow quadratically. This means that the functions we wrote for both the matcher and verifier run in $O(n^2)$ time complexity. By looking at the algorithm this makes sense as we have 2 different for-loops, that at worst check every single element in both preference lists which would be $O(n \cdot n)=O(n^2)$. Overall, the graphs are a great representation of the time complexity of our algorithms. 

