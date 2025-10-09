# Minishell

A small, Bash-like shell implemented in **C** (42 project).  
It provides a prompt with history, command parsing, pipes & redirections, environment variable expansion, and the standard built-ins.

---

## Features

- **Prompt & history** (GNU Readline)
- **Lexer/Parser** with quotes, tokenization, and env expansion (`$VAR`, `$?`)
- **Pipes & redirections**: `|`, `<`, `>`, `>>`, **heredoc** `<<` (with quoted/unquoted delimiter rules)
- **PATH resolution** for external commands
- **Signals** tuned for interactive use:
  - `Ctrl-C` (SIGINT): returns to prompt, exit code `130`
  - `Ctrl-\` (SIGQUIT): ignored at prompt
  - `Ctrl-D`: clean exit on empty line
- **Built-ins** (in-process, affect shell state):
  - `echo` (supports `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## Build & Run

**Prerequisites**
- GNU Readline development headers (`libreadline-dev` / `readline`)
- `make` and a C compiler

```bash
git clone https://github.com/andrijajovanovic98/minishell
cd minishell
make
./minishell



![minishellscore](https://github.com/user-attachments/assets/9fdacdba-2303-4f95-84e7-2d91202bc27e)



Our result with tester: https://github.com/zstenger93/42_minishell_tester:

To test it, just compile it with the "make tester" command

![Screenshot from 2024-09-19 17-00-56](https://github.com/user-attachments/assets/e4c9834b-f1dd-494a-9209-2f498b7d9067)
