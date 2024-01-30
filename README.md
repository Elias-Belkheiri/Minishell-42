# Overview

Minishell is a lightweight Unix shell interpreter that processes and executes command-line instructions. This document provides an overview of the parsing and execution mechanisms implemented in Minishell, focusing on the tokenization, expansion, and execution stages.


# Core Features

- Display a prompt while waiting for a new command.
- Have a working history.
- Find and launch executables (using the `PATH` variable or an absolute path).
- Handle `'` (single) and `"` (double) **quotes** like in bash.
- Implement **redirections** such as:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` heredoc (doesn't affect history).
  - `>>` redirect output in append mode.
- Implement `|` (**pipes**).
- Handle **environment variables**.
- Handle **Wildcards**.
- Handle `$?`.
- `ctrl-C`, `ctrl-D`, and `ctrl-\` should behave like in bash.
- Recreate the following **builtins**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` (no flags).
  - `export` (no flags).
  - `unset` (no flags).
  - `env` (no flags or arguments).
  - `exit` (no flags).

# Implementation

### Lexer and Tokenization

The lexer plays a crucial role in parsing commands entered into Minishell. It breaks down the input into manageable tokens based on their type. Each token is represented by the ***t_token structure***, which includes the token's content, type, an expansion flag, and a pointer to the next token:

```C
typedef struct t_token
{
    char            *content;
    int             type;
    int             expanded;
    struct t_token  *next;
}   t_token;
```
The Types are defined as follows:
```
SPACES: Represents space characters.

PIPE: Symbolizes the pipe character (|) used for piping commands.

OPERATOR: Includes operators like &&, ||.

DOUBLE: Indicates double quotes (").

SINGLE: Indicates single quotes (').

HYPHEN: Represents a hyphen character (-).

WORD: General word or command.

SINGLE_EXPAND: Single quotes that allow expansion.
```

### Expansion

After tokenization, the lexer expands environment variables and wildcards. It also removes unnecessary spaces, preparing the tokens for further processing.


### Command Separation

Using a linked list structure, Minishell separates the commands and their corresponding types. The t_cmd structure represents each command:
```C
typedef struct t_cmd
{
    char            **cmd;
    t_redirection    *in;
    t_redirection    *out;
    int              pipe;
    int              err;
    struct t_cmd     *next;
}   t_cmd;
```

### Execution

Once the parsing is complete, Minishell loops through the linked list of commands ***(t_cmd)***. Each command is executed according to its type and the specified redirections or piping. The shell handles errors and ensures the correct sequence and combination of commands.


### Conclusion

Minishell provides a comprehensive suite of features that closely emulate the functionality of conventional Unix shells. Its built-in commands, advanced redirection and piping capabilities, environment variable handling, and signal processing make it a versatile tool for users familiar with the Unix command line. The incorporation of a user-friendly command history and the ability to handle different quoting mechanisms further enhance its usability.
