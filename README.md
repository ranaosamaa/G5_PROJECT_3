# 🔢 BigInt — Arbitrary Precision Integer Library in C++

A **pure C++ implementation** of an arbitrary-precision integer (`BigInt`) class that supports arithmetic, comparison, and increment/decrement operations on integers of **unlimited size** — far beyond the limits of built-in types like `int` or `long long`.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [How It Works](#how-it-works)
- [Supported Operations](#supported-operations)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build with Visual Studio](#build-with-visual-studio)
  - [Build with VSCode + GCC (MSYS2)](#build-with-vscode--gcc-msys2)
  - [Build with g++ directly](#build-with-g-directly)
- [Example Output](#example-output)
- [Edge Cases Handled](#edge-cases-handled)

---

## Overview

Built-in C++ integer types overflow at fixed limits (e.g. `int64_t` maxes out at ~9.2 × 10¹⁸). `BigInt` solves this by storing numbers as **digit strings** and implementing all arithmetic from scratch using grade-school algorithms — addition with carry, subtraction with borrow, long multiplication, and long division.

---

## ✨ Features

- ✅ Store integers of **any size** — limited only by memory
- ✅ Full **sign handling** (positive and negative)
- ✅ All standard **arithmetic operators**: `+`, `-`, `*`, `/`, `%`
- ✅ All **comparison operators**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- ✅ **Increment / decrement**: `++x`, `x++`, `--x`, `x--`
- ✅ **Unary** `+` and `-`
- ✅ `cin` / `cout` support via stream operators
- ✅ **Division by zero** throws `runtime_error`
- ✅ No external libraries — pure C++ Standard Library only

---

## 🧠 How It Works

### Internal Representation

```cpp
class BigInt {
    string number;   // Digits stored as a string (e.g. "12345678901234567890")
    bool isNegative; // Sign flag
};
```

### Core Helper Methods

| Method | Description |
|---|---|
| `removeLeadingZeros()` | Strips leading `'0'` characters and normalizes zero's sign |
| `compareMagnitude()` | Compares absolute values: returns `1`, `0`, or `-1` |
| `addStrings()` | Grade-school addition with carry, digit by digit |
| `subtractStrings()` | Grade-school subtraction with borrow, digit by digit |

### Arithmetic Approach

- **Addition / Subtraction:** Sign-aware — delegates to `addStrings` or `subtractStrings` based on sign combination
- **Multiplication:** Long multiplication (like manual long multiplication on paper), digit by digit with carry and positional offset
- **Division:** Long division by repeatedly subtracting the divisor from successive prefixes of the dividend
- **Modulus:** Same long-division approach, returns the leftover remainder with the original sign

---

## ⚙️ Supported Operations

### Constructors

```cpp
BigInt a;                      // Default → 0
BigInt b(12345);               // From int64_t
BigInt c("-67890");            // From string (supports negative)
BigInt d = c;                  // Copy constructor
```

### Arithmetic

```cpp
BigInt r1 = a + b;
BigInt r2 = a - b;
BigInt r3 = a * b;
BigInt r4 = a / b;   // throws runtime_error if b == 0
BigInt r5 = a % b;
a += b;  a -= b;  a *= b;  a /= b;  a %= b;
```

### Comparison

```cpp
a == b;   a != b;
a <  b;   a <= b;
a >  b;   a >= b;
```

### Increment / Decrement

```cpp
++a;   a++;
--a;   a--;
```

### I/O

```cpp
cout << a;         // Prints "-12345" or "12345"
cin  >> a;         // Reads a BigInt from standard input
a.toString();      // Returns string representation
```

---

## 📁 Project Structure

```
G5_PROJECT_3/
│
├── G5_PROJECT_3.cpp          # All source code — BigInt class + test main()
│
├── G5_PROJECT_3.slnx         # Visual Studio solution file
├── G5_PROJECT_3.vcxproj      # Visual Studio project file
├── G5_PROJECT_3.vcxproj.filters  # VS filter definitions
│
├── .idea/                    # CLion / JetBrains IDE settings
│   ├── G5_PROJECT_3.iml
│   ├── material_theme_project_new.xml
│   ├── modules.xml
│   └── vcs.xml
│
├── .vscode/                  # VSCode build settings
│   ├── settings.json         # Compiler path (MSYS2 GCC)
│   └── tasks.json            # Build task using gcc.exe
│
└── .gitignore
```

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting **C++11 or later**
- One of: **Visual Studio 2022+**, **VSCode + MSYS2**, or any `g++` installation

---

### Build with Visual Studio

1. Open `G5_PROJECT_3.slnx` in **Visual Studio 2022** or later
2. Select **Debug** or **Release** configuration
3. Press `Ctrl+Shift+B` to build
4. Run with `Ctrl+F5`

---

### Build with VSCode + GCC (MSYS2)

The `.vscode/tasks.json` is pre-configured with the MSYS2 GCC compiler path:

```
C:\msys64\ucrt64\bin\gcc.exe
```

If your MSYS2 is installed at a different path, update `settings.json` accordingly.

To build and run:
1. Open the project folder in VSCode
2. Press `Ctrl+Shift+B` to run the default build task
3. Run the generated `.exe` from the terminal

---

### Build with g++ directly

**Linux / macOS:**
```bash
g++ -std=c++11 -o BigInt G5_PROJECT_3.cpp
./BigInt
```

**Windows (MinGW / MSYS2):**
```bash
g++ -std=c++11 -o BigInt.exe G5_PROJECT_3.cpp
BigInt.exe
```

---

## 💡 Example Output

```
=== BigInt Class Test Program ===

1. Constructors and output:
a (from int): 12345
b (from string): -67890
c (zero): 0
d (copy of a): 12345

2. Arithmetic operations:
a + b = -55545
a - b = 80235
a * b = -838102050
b / a = -5
a % 100 = 45

3. Relational operators:
a == d: 1
a != b: 1
a < b: 0
a > b: 1
c == 0: 1

4. Unary operators and increments:
-a: -12345
++a: 12346
a--: 12346
a after decrement: 12345

5. Large number operations:
Very large addition: 111111111011111111100
Very large multiplication: 1219326311370217952237463801111263526900

6. Edge cases:
Division by zero correctly threw error: Division by zero
Multiplication by zero: 0
Negative multiplication: -15
Negative division: -3
Negative modulus: -1
```

---

## 🛡️ Edge Cases Handled

| Case | Behavior |
|---|---|
| Division by zero | Throws `std::runtime_error("Division by zero")` |
| Multiply by zero | Returns `0` with no sign |
| Negative × Negative | Returns positive result |
| Leading zeros in string input | Stripped automatically |
| `-0` | Normalized to `0` (no negative zero) |
| Very large numbers | Handled correctly — no overflow |

---

## 👥 Authors

**Group 5** — G5_PROJECT_3
