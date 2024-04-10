Minishell
Minishell is a simple Unix shell implementation written in C. It provides a basic command-line interface similar to other Unix shells like Bash,
allowing users to execute commands, navigate the file system, and manage processes.

Features
Command Execution: Execute commands entered by the user.
Built-in Commands: Supports built-in shell commands such as cd, echo, exit, pwd, and more.
Redirection: Supports input/output redirection using <, >, and >> operators.
Piping: Supports command piping using the | operator.
Environment Variables: Supports environment variables and variable expansion.
Error Handling: Provides informative error messages and proper handling of errors.
Signal Handling: Handles signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+) gracefully.
Getting Started
To get started with the Minishell project, follow these steps:

Clone the repository to your local machine:
install readline at brew
git clone https://github.com/your-username/minishell.git
Navigate to the project directory:

cd minishell
Build the Minishell executable:

make
Run Minishell:

./minishell
Usage
Once Minishell is running, you can use it like any other Unix shell. Here are some basic usage examples:

Execute a command:
ls -l

Change directory:
cd /path/to/directory

Print the current working directory:
pwd

Exit Minishell:
exit

For more information on supported commands and usage, refer to the Minishell documentation.

Contributing
Contributions to the Minishell project are welcome! If you find any bugs or have suggestions for new features, please open an issue on the GitHub repository.
