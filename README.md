# Programming Assignment 1 – Matching and Verifying

## Course
COP 4533 – Algorithm Abstraction and Design 

University of Florida

## Authors
- Hung Hong (UFID: 56253262)
- Thyssen Nicholas (UFID: 19705329)

**Contributions**
- Part A (Matcher): Hung Hong  
- Part B (Verifier): Thyssen Nicholas  

---

## Overview
This project implements the Gale–Shapley stable matching algorithm for the hospital–student matching problem, along with a saperate verifier that checks whether a given matching is valid and stable.

Hospitals propose to students, and students always keep their most preferred offer so far. The algorithm terminates when no hospital can improve its match.

---

## Build Instructions
To compile all programs:
```bash
make
```
this will produce
matcher, verifier, gen inside bin/

----
Part A

```bash
make example
```
This will compile matcher with example.in that provided


----
we also include other useful target for testing such as for part C
```bash
scale-verifier
```
and 
```bash
scale-matcher
```


----







---
![Time VS Data Graph For Matcher Function](read_me_files/image.png)
