# Overview

Minishell is a lightweight Unix shell interpreter that processes and executes command line instructions. This document provides an overview of the parsing and execution mechanisms implemented in Minishell, focusing on the tokenization, expansion, and execution stages.


# Core Features

***Prompt Display:*** Minishell displays a prompt when waiting for a new command, enhancing user interaction.

***Command History:*** It maintains a history of executed commands, allowing users to revisit previous commands.

***Executable Launching:*** The shell can find and launch executables, either using the PATH variable or by specifying an absolute path.

**Quoting Mechanisms:*** Minishell handles single (') and double (") quotes, similar to Bash, allowing for grouping of characters as a single argument or string.


### Built-in Commands:

***echo:*** Print text to the terminal, with an -n option to omit the trailing newline.

***cd:*** Change the current directory, supporting both relative and absolute paths.

***setenv and unsetenv:*** Set or unset environment variables.

***env:*** Display current environment variables, with no flags or arguments.

***exit:*** Exit the shell, with no flags.


### Redirections:

***<:*** Redirect input from a file to a command.

***>:*** Redirect output of a command to a file, overwriting it.

***>>:*** Redirect output to a file in append mode.

***<<:*** Implement 'heredoc' functionality, without affecting command history.

***Pipes ( | ):*** MiniShel supports piping, allowing the output of one command to serve as input to another.

***Environment Variables:*** The shell handles environment variables, enabling users to retrieve or modify values within the shell session.

***Exit Status ($?):*** Minishell tracks and displays the exit status of the last executed command, similar to Bash.

### Signal Handling:

***CTRL-C:*** Interrupts the current process.

***CTRL-D:*** Exits the shell or sends EOF (End-Of-File) if no process is running.

***CTRL-\:*** Quits the current process but doesn't exit the shell.

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
The Types are definded as folllows:
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
