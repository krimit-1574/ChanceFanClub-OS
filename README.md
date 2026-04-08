# Operating Systems Final Project

## Objective
This project is a menu-driven modular system that demonstrates key Operating System concepts using C programming.

## Modules Implemented
1. **Logging System (IPC):** Centralized logging using `fork()` and `exec()`. Logs user actions and system states to `logs/logs.txt` with timestamps.
2. **Peterson's Solution (Synchronization):** Simulates mutual exclusion for two processes utilizing busy waiting (spinlocks) via standard variables and pthreads.
3. **File Management:** Basic operations to create, read, list, and delete files in the current working directory.
4. **Contiguous Memory Allocation:** Simulates first-fit memory allocation, deallocation, and compaction with initial state inputs.
5. **Amdahl's Law:** Calculates parallel speedup given parallel fraction and cores, and compares serial vs parallel execution times.
6. **Main Menu:** The driver program allowing users to navigate through the modules, utilizing `fork()`, `exec()`, and `wait()`.

## Installation & Setup
Run the `boot.sh` script to clean previous builds, create required directories, compile all C files, and automatically launch the program.

```bash
chmod +x boot.sh
./boot.sh
```

## Structure
- `/src` : Contains all `.c` and `.h` source files.
- `/bin` : Contains compiled binary executable files (after compilation).
- `/logs` : Contains `logs.txt` created dynamically to record system executions.
