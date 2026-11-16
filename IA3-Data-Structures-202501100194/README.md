# IA-3 Data Structures Assignment

**Student:** Utkarsh Kapre  
**PRN:** 202501100194  
**Institute:** MIT Academy of Engineering  
**Language:** C++

## Personalization

- Seed (last four digits of PRN): `194`
- Dataset size: `12`
- Search key: `(194 % 89) + 3 = 19`
- Hash table size: smallest prime at least `(194 % 23) + 11 = 21`, so `m = 23`
- Sorting order: ascending (even PRN)
- Dataset formula: `a[i] = (194 * (i + 3) + 7) % 97`, for `i = 0..11`
- Duplicate correction: increment repeated values until unique (modulo 97); for this PRN all raw values are 7 and no wraparound occurs.

```text
7 8 9 10 11 12 13 14 15 16 17 18
```

## Programs

| File | Method | Hash / probe formula |
| --- | --- | --- |
| `linear.cpp` | Linear probing without replacement | `(key % 23 + i) % 23` |
| `chaining.cpp` | Separate chaining using linked lists | `key % 23` |
| `quadratic.cpp` | Quadratic probing without replacement (optional extension) | `(key % 23 + i*i) % 23` |

Each program generates the personalized dataset, inserts each key in order, displays the entire hash table after each insertion, and prints the final table and collision count. All indices are zero-based.

## Compiler and execution

Use a C++17-compatible compiler (e.g. g++). Run each program separately from the repository directory:

```bash
g++ -std=c++17 linear.cpp -o linear
./linear

g++ -std=c++17 chaining.cpp -o chaining
./chaining

g++ -std=c++17 quadratic.cpp -o quadratic
./quadratic
```

## Results for the personalized dataset

All keys are distinct and smaller than 23, so each key hashes directly to its own value. All three programs insert 12 keys with zero collisions. Slots 7–18 are occupied; slots 0–6 and 19–22 are empty. Linear and quadratic probing use 12 slot checks each. Separate chaining has a maximum chain length of 1. The load factor is 12/23 (approximately 0.522).

## Scope

Linear probing and separate chaining reproduce the hashing section of the 12-value trace portfolio. Quadratic probing is an additional demonstration, not required by that PDF. This repository layout covers those three hashing programs; the PDF's sorting and searching traces are separate. The official IA-3 Question 2 is a separate 20-value C++ student-marks hash-table project and requires genuine incremental development commits and process evidence.
