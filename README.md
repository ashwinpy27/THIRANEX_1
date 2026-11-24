# Student Management System (C++)

A console-based, menu-driven Student Management System using C++ file handling.

## Features
- Add a student
- Display all saved students
- Update a student's details using their ID
- Delete a student after confirmation
- Store records persistently in `students.txt`
- Basic input validation and duplicate-ID checking

## Student fields
- Student ID (unique)
- Name
- Age
- Course
- Marks (0–100)

## Requirements
- A C++ compiler (GCC / MinGW / Clang)
- C++11 or later

## Compile and run (Windows – MinGW)
Open a terminal in this folder and run:

```bash
g++ main.cpp -o StudentManagementSystem
.\StudentManagementSystem.exe
```

## Compile and run (Linux / macOS)
```bash
g++ main.cpp -o StudentManagementSystem
./StudentManagementSystem
```

## Data storage
The program automatically creates `students.txt` in the current working directory when the first record is saved.
Each record is stored as:

`ID|Name|Age|Course|Marks`

Keep `students.txt` in the same folder from which you run the program. Back up this file if you want to preserve your records.

## Notes
- Use a unique ID for every student.
- Names and course names must not contain the `|` character.
- This is a beginner-friendly console project intended for learning C++ structures, vectors, functions, menus, and file handling.
