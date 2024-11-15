# Minishell

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Contact](#contact)

## Overview

**Minishell** is 42-cursus project that mimics bash shell. This project is designed to help us understand the problems encountered before when windows did not exists yet. It is ideal for students to learn how it works and to have a great foundation of coding. The program runs in a loop and waits for a prompt from the user. Parse the line and build an abstract syntax tree (AST). Run the command using the AST.

## Features

- History: Store command history and allow users to cycle through it using arrow keys.
- Pipes and Redirection: Support pipes `|` and input/output redirection (`<`, `>`, `<<`, `>>`) including heredoc.
- Signal Handling: Handle signals such as Ctrl+C (SIGINT) and Ctrl+D (SIGQUIT).
- Environment Variables: Enable setting, modifying, and using environment variables.

- The following builtins are implemented
	- `echo` with option `-n`
	- `cd` with only a relative or absolute path
	- `pwd` with no options
	- `export` with no options
	- `unset` with no options
	- `env` with no options or arguments
	- `exit` with no options

## Installation

1. **Clone the repository:**

   ```bash
   git clone git@github.com:janrau9/minishell.git
   cd minishell
   ```

2. **Install dependencies:** 
install readline package using 
`brew install readline` on MacOS, or `sudo apt-get update` and `sudo apt-get install libreadline-dev` on Ubuntu/Debian.


3. **Compile:**

```bash
make
```

### Run the application

```bash
./minishell
```

## Contact

**Your Name**  
[Email](janraup356@gmail.com)  
[LinkedIn](https://linkedin.com/in/janrau-beray)
