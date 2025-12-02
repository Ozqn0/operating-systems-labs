# Operating Systems Laboratory Exercises

![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux-FCC624?style=flat-square&logo=linux&logoColor=black)
![Course](https://img.shields.io/badge/Course-Operating_Systems-red?style=flat-square)

This repository serves as a comprehensive collection of laboratory exercises for the *Operating Systems* course. It focuses on low-level system programming, process management, file I/O operations, and inter-process communication (IPC) within the Linux environment.

All implementations utilize the *C programming language* and standard *POSIX system calls*.

---

## 📚 Table of Contents
- [Project Overview](#project-overview)
- [Repository Structure](#repository-structure)
- [Exercise List & Topics](#exercise-list--topics)
- [Compilation & Execution](#compilation--execution)
- [System Requirements](#system-requirements)

---

## Project Overview
The primary objective of this project is to provide practical implementations of core Operating System concepts. Each module is designed to demonstrate specific system calls and their behaviors in a Linux kernel environment.

*Key concepts covered:*
* *Process Management:* fork(), wait(), exec() family, Zombie and Orphan processes.
* *File Management:* Low-level I/O using open(), read(), write(), lseek().
* *IPC (Inter-Process Communication):* Implementation of anonymous pipe().

---

## Repository Structure

The project strictly follows the required directory hierarchy. Each exercise is encapsulated in its own directory containing the source code, documentation, and binary.

```text
operating-systems-labs/
│
├── README.md               # Project documentation (This file)
│
├── example-01/             # Process Creation
│   ├── main.c              # Source code
│   ├── explanation.md      # Technical explanation
│   └── app                 # Compiled binary
│
├── example-02/             # Process Synchronization
│   ├── main.c
│   ├── explanation.md
│   └── app
│
├── ... (examples 03 to 09)
│
└── example-10/             # Inter-Process Communication
    ├── main.c
    ├── explanation.md
    └── app
```

## Exercise List & Topics
The following table details the specific topics and system calls implemented in each exercise (based on the DexTutor curriculum).

| ID | Module Name | Key Concepts & System Calls | Status |
| :---: | :--- | :--- | :---: |
| *01* | Process Creation | fork(), getpid(), getppid() | ✅ |
| *02* | Synchronization | wait(), Process State Management | ✅ |
| *03* | Orphan Process | Parent termination, init adoption | ✅ |
| *04* | Zombie Process | Defunct processes, Process Table | ✅ |
| *05* | Image Replacement | execl(), Memory Overlay | ✅ |
| *06* | Execution Methods | system() vs exec() family | ✅ |
| *07* | File I/O | open(), read(), write(), close() | ✅ |
| *08* | Random Access | lseek(), File Offsets | ✅ |
| *09* | I/O Redirection | dup(), dup2(), STDOUT redirection | ✅ |
| *10* | Communication | pipe(), Unidirectional Data Flow | ✅ |
## Compilation & Execution
Each module is independent. You must compile the source code within its respective directory using the GCC compiler.

### Standard Build Command
Per the course requirements, the output binary must be named app.

Bash
gcc main.c -o app
Step-by-Step Guide
Navigate to the specific exercise folder (e.g., Example 01):


Bash
cd example-01
Compile the C source code:


Bash
gcc main.c -o app
Run the application:


Bash
./app
Note: Ensure you have execution permissions if strictly required, though gcc typically handles this. If permission is denied: chmod +x app.


### System Requirements
Operating System: Linux (Ubuntu/Debian recommended) or WSL (Windows Subsystem for Linux).
Compiler: GCC (GNU Compiler Collection).
Editor: VS Code, Vim, or Nano.
