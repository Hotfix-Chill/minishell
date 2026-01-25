
*This project has been created as part of the 42 curriculumby pjelinek & abita.*

# 🐚 Minishell

## 📖 Description

**Minishell** is an educational project from the 42 curriculum. Its goal is to implement a minimal Unix shell in C, recreating the core behavior of Bash in a simplified but technically accurate way.

The project focuses on understanding how a shell works internally, including
process creation, file descriptor management, signal handling, and command
parsing.

Minishell provides an interactive command-line interface that allows users to:
- Execute external programs
- Manage environment variables
- Use pipes and redirections
- Interact safely with the operating system

Rather than copying Bash feature-by-feature, the objective is to deeply
understand low-level system programming concepts such as `fork`, `execve`,
`pipe`, `dup2`, signals, and terminal control — while maintaining strict
memory safety and robustness.

## ⚙️ Instructions


### 🔧 Compilation

The project is written in C and must be compiled using `cc` with
the required flags

This generates the executable: make

### 📜 Makefile Rules

| Command             | Description                         |
| ------------------- | ----------------------------------- |
| `make` / `make all` | Build the project                   |
| `make clean`        | Remove object files                 |
| `make fclean`       | Remove objects and executable       |
| `make re`           | Rebuild from scratch                |
| `make bonus`        | Build bonus features (if available) |

---

## ▶️ Execution

Run Minishell with:
$./minishell

The program will display a prompt and wait for user input.


### 🧠 Interactive Behavior

| Shortcut | Behavior             |
| -------- | -------------------- |
| `Ctrl-C` | Display a new prompt |
| `Ctrl-D` | Exit the shell       |
| `Ctrl-\` | No action            |



## 🧩 Features

* Interactive prompt with command history
* Execution of external commands via `PATH`, relative or absolute paths
* Environment variable expansion (`$VAR`, `$?`)
* Quote handling ('single' and "double")

* Redirections:
  * Input `<`
  * Output `>`
  * Append `>>`
  * Heredoc `<<`

* Pipes (`|`)
* Bash-like signal behavior

* Built-in commands:
  * `echo` (with `-n`)
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`


## 📚 Resources

### 🔬 Technical References

* GNU Bash Manual
  [https://www.gnu.org/software/bash/manual/]
* Linux Man Pages:

  * `man fork`
  * `man execve`
  * `man pipe`
  * `man dup2`
  * `man signal`
* GNU Readline Documentation

These sources were used to validate shell behavior, system call semantics, and
edge cases by comparing Minishell with Bash.


## 🤖 Use of AI Tools

AI tools were used responsibly during development in accordance with the **42 AI policy**.

AI assistance was applied for:

* Clarifying system call behavior and edge cases
* Explaining shell internals (word splitting, pipelines, signals)
* Reviewing parsing strategies and data-structure concepts

No AI-generated code was integrated without manual review and validation.
All **core logic, parsing, execution flow, and memory management** were designed
and implemented manually.

The author takes **full responsibility** for all code and design decisions.
Peer reviews and manual testing were the primary validation methods.
