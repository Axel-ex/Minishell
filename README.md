# About
Minishell is a UNIX-like shell implemented in C, aiming to provide a basic replica of a bash-like shell. It supports a variety of features including command execution, I/O redirection, pipelines, variable expansion, command history, tab completion, signal handling, and exit status handling. Find a detailed list of requirements for this project here: [subject.pdf](https://github.com/Axel-ex/Minishell/blob/main/subject.pdf).

# Usage
`git clone` this project `cd` into it and `make`.
the program is executed as so:

```shell
./minishell
```
The program will then prompt you for input. It is used exactly as a bash shell as such:

```shell
ls -l
echo "Hello world"
cat file.txt
```
<img src="demo.gif" width="100%"/>

# Key features
- Command execution
- I/O redirection
- Pipelines
- Variable expension
- Command history
- Tab completion
- Signal handling
- exit status handling

# Implementation
The program uses the readline library to prompt input to the user and can be divided into four main parts.
<br/>

1. **Lexer (Tokenizer)**:
- The lexer tokenizes the input command line string into individual tokens using `get_token()` function.
- It skips over leading spaces and identifies various types of tokens, including commands, arguments, and redirection operators.
- Special characters like quotes are handled to ensure correct tokenization.

2. **Expander**:
- The expander is responsible for expanding variables in the command line.
- It identifies variables prefixed with `$` and replaces them with their corresponding values.
- Special variables like `$?` for exit status are supported.

3. **AST (Abstract Syntax Tree) Generator**:
- The AST generator constructs a tree structure representing the syntax of the command line input.
- It parses commands, arguments, and redirections and organizes them into a hierarchical tree.
- Commands separated by pipes (`|`) are connected as nodes in the tree.

4. **Executor**:
- The executor executes the commands represented by the AST.
- It matches commands with built-in functions or external executables and executes them accordingly.
- I/O redirection, command execution in child processes, and handling of exit statuses are managed within the executor.

# Testing
`cd` into the test/ directory and run `./tester`. The tester was developed by Lucas Kuhn ([minishell tester](https://github.com/LucasKuhn/minishell_tester)) and was really usefull to rigouresly test for errors. Tests can be added in the "test/extras" file to cover more aspects of the shell.


# Norme

All 42 projects must be written following the **Norme**.

	- No for, do while, switch, case or goto are allowed
	- No more than 25 lines per function and 5 functions per file
	- No assigns and declarations in the same line (unless static)
 	- Each line must be at most 80 columns wide, comments included
	- A function can take 4 named parameters maximum
	- No more than 5 variables in 1 function
