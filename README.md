# Minishell

Minishell is A lightweight Bash alternative in pure C, prioritizing simplicity, stability, and performance.

## Features

- Command execution
- Environment variable handling
- Basic error handling
- pipes
- I/O redirection
- heredocs
- signal handlingand

## Getting Started

### Prerequisites

- A Unix-like operating system
- GCC (GNU Compiler Collection)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/s888n/minishell.git
   cd minishell
   ```

2. Compile the project:
   ```bash
   make
   ```

### Usage

Run the shell:
```bash
./minishell
```

You can now enter commands as you would in a regular shell.

### Examples

```sh
$ ls -l
$ echo "Hello, World!"
$ export MY_VAR=42
$ echo $MY_VAR
```