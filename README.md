# Student Record and Result Management System
### PRC1001 – Programming in C | UPES, Sem I (2026-27)

**Student:** Aryan Gangwar  
**SAP ID:** 590042393  
**Program:** B.Tech Computer Science & Engineering  
**University:** University of Petroleum and Energy Studies (UPES), Dehradun

---

## Project Overview

This is a console-based **Student Academic & Result Management System** developed in C as part of the PRC1001 course project. The system stores and manages student records with an integrated AI-assisted advisory module.

## Features Implemented

| Feature | Description |
|---------|-------------|
| Register Student | Add new student record with SAP ID, roll number, contact, SGPA data |
| Search Record | Lookup any student by their SAP ID |
| CGPA Inquiry | Compute and display CGPA from semester-wise SGPA entries |
| Year-wise CGPA | Show average CGPA grouped by academic year (cohort analysis) |
| View Directory | Display all enrolled student profiles |
| Delete Record | Remove a student by SAP ID with confirmation prompt |
| Sort by SAP ID | Sort records using **Insertion Sort** algorithm |
| Sort by Name | Sort records alphabetically using **Bubble Sort** with pointer-based swap |
| AI Advisor | Performance-tier based academic advisory using if-else logic |
| Sample Data | Auto-load 5 diverse test profiles for demonstration |

## Project Structure

```
590042393/
├── Part1_Initial_Program.c       # Initial skeleton: struct, menu, flushInput
├── Part2_Student_Record.c        # Adds: register, find, display, remove
├── Part3_CGPA_Sorting.c          # Adds: computeCGPA, sorting, year-wise CGPA
├── Part4_AI_Advisor_Complete.c   # Final: AI advisor + complete system
├── 590042393.c                   # Submission file (same as Part4)
├── README.md
├── AI_USAGE_LOG.md
└── tests/
    ├── sample_input.txt
    └── sample_output.txt
```

## How to Compile & Run

```bash
gcc 590042393.c -o student_system -Wall
./student_system
```

**On Windows (MinGW):**
```bash
gcc 590042393.c -o student_system.exe -Wall
student_system.exe
```

## Data Structure Used

```c
typedef struct {
    long long sap_id;
    char roll_number[18];
    char student_name[60];
    char contact_no[16];
    char email_address[60];
    int academic_year;
    int current_sem;
    float sem_sgpa[8];
} StudentRecord;
```

## Sorting Algorithms

- **Insertion Sort** – Used for sorting by SAP ID (ascending)  
- **Bubble Sort** – Used for sorting by student name (alphabetical), implemented with a `swapRecords()` pointer-based helper function

## AI Advisory Tiers

| Tier | CGPA Range | Classification |
|------|-----------|----------------|
| Tier 1 | ≥ 9.0 | Outstanding Merit |
| Tier 2 | 7.5 – 8.9 | Meritorious Achievement |
| Tier 3 | 6.0 – 7.4 | Satisfactory / Growth Focus |
| Tier 4 | < 6.0 | Academic Warning Notice |

## Development Approach

The project was built incrementally across 4 commits, each adding a distinct layer of functionality — from the basic struct skeleton to the full AI advisor integration. AI tools were used for concept clarification and validation (see `AI_USAGE_LOG.md`).

---
*Submitted in partial fulfillment of PRC1001 – Programming in C, UPES Semester I, 2026-27*
