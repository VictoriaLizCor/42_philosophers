# Philosophers (42)

Implementation of the classic **Dining Philosophers** concurrency problem (42 school project style).  
Multiple philosophers alternate between **thinking**, **eating**, and **sleeping** while competing for shared forks (mutex-protected resources). The program prints timestamped state changes and stops when a philosopher dies or when all philosophers have eaten enough times (optional).

---

## Table of contents
- [Project overview](#project-overview)
- [Rules / constraints (42)](#rules--constraints-42)
- [Build](#build)
- [Makefile targets (repo-specific)](#makefile-targets-repo-specific)
- [Run](#run)
- [Arguments](#arguments)
- [Output](#output)
- [Testing](#testing)
- [Troubleshooting](#troubleshooting)

---

## Project overview
This program simulates `N` philosophers sitting at a round table with `N` forks:

- Each philosopher needs **two forks** to eat.
- Philosophers repeat a loop: **take forks → eat → sleep → think**.
- The simulation ends when:
  - one philosopher **dies** (doesn’t eat within `time_to_die`), or
  - (optional) all philosophers have eaten `must_eat` times.

---

## Rules / constraints (42)
- **Language:** C
- **Threading model:** POSIX threads (`pthread`)
- **Synchronization:** mutexes (forks + shared state like printing/death/completion)
- **Time unit (input):** milliseconds (ms)
- **Compilation flags (project style):** `-Wall -Wextra -Werror`

---

## Build
From the repository root:

```sh
make
```

Common targets:

```sh
make        # build
make clean  # remove object files / build directory
make fclean # remove objects + binary
make re     # rebuild from scratch
```

The default output binary is:

- `./philo`

---

## Makefile targets (repo-specific)

### Core
- `make` / `make all`  
  Builds `NAME := philo`.

- `make clean`  
  Removes build artifacts (and `.dSYM` on macOS if present).

- `make fclean`  
  `clean` + removes the executable.

- `make re`  
  Full rebuild.

### Debug / sanitizers (variables)
Your Makefile supports these switches:

- `D=<level>`  
  Adds debug flags and defines `D_PHI=<level>` (used by debug output in the code).
  Example:
  ```sh
  make re D=1
  ```

- `S=<mode>`  
  Sanitizer mode:
  - `S=-1` (default): normal build
  - `S=0`: AddressSanitizer + UndefinedBehaviorSanitizer
  - `S=1`: ThreadSanitizer + UndefinedBehaviorSanitizer
  Examples:
  ```sh
  make re S=0
  make re S=1
  make re D=2 S=1
  ```

### Run / analysis helpers
These rules take `arg="..."` (the program arguments):

- Run:
  ```sh
  make start arg="5 800 200 200"
  ```

- Valgrind leak check:
  ```sh
  make val arg="5 800 200 200"
  ```

- Helgrind (thread/race tool):
  ```sh
  make hel arg="5 800 200 200"
  ```

- macOS leaks:
  ```sh
  make leaks arg="5 800 200 200"
  ```

### Test scripts
- `make eval_test` runs:
  - `test/eval_cases.sh`

- `make own_test` runs:
  - `test/own_cases.sh`

Example:
```sh
make own_test p=2 c="D=0 S=1 start"
```

### Extra
- `make norm` runs norminette on `./src` and `./include`.

---

## Run
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]
```

---

## Arguments
All values must be positive integers.

1. `number_of_philosophers`  
   Number of philosopher threads to create.

2. `time_to_die` (ms)  
   If a philosopher does not start eating within this time since their last meal, they die.

3. `time_to_eat` (ms)  
   Duration of the eating action.

4. `time_to_sleep` (ms)  
   Duration of the sleeping action.

5. `must_eat` *(optional)*  
   If provided, the simulation stops once every philosopher has eaten at least this many times.

### Examples
```sh
./philo 5 400 200 100
./philo 5 400 200 100 4
```

---

## Output
The program prints state transitions in a format similar to:

- `<timestamp_ms> <philosopher_id> has taken a fork`
- `<timestamp_ms> <philosopher_id> is eating`
- `<timestamp_ms> <philosopher_id> is sleeping`
- `<timestamp_ms> <philosopher_id> is thinking`
- `<timestamp_ms> <philosopher_id> died`

Timestamps are relative to the simulation start.

> Depending on debug configuration (`D`), output may include colors or extra diagnostic lines.

---

## Testing

### Quick sanity
```sh
./philo 1 800 200 200
./philo 2 800 200 200
```

### Typical runs
```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

### Stress / stability
```sh
./philo 100 310 200 100
```

### Useful Makefile shortcuts
```sh
make start arg="5 800 200 200"
make val   arg="5 800 200 200"
make hel   arg="5 800 200 200"
make leaks arg="5 800 200 200"
```

---
