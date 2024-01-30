# Overview

Minishell is a lightweight Unix shell interpreter that processes and executes command line instructions. This document provides an overview of the parsing and execution mechanisms implemented in MiniShell, focusing on the tokenization, expansion, and execution stages.


# Core Features

## Basic Features:

**Prompt Display:** MiniShell displays a prompt when waiting for a new command, enhancing user interaction.

**Command History:** It maintains a history of executed commands, allowing users to revisit previous commands.

**Executable Launching:** The shell can find and launch executables, either using the PATH variable or by specifying an absolute path.

**Quoting Mechanisms:** Minishell handles single (') and double (") quotes, similar to Bash, allowing for grouping of characters as a single argument or string.



### Built-in Commands:

**echo:** Print text to the terminal, with an -n option to omit the trailing newline.

**cd:** Change the current directory, supporting both relative and absolute paths.

**setenv and unsetenv:** Set or unset environment variables.

**env:** Display current environment variables, with no flags or arguments.

**exit:** Exit the shell, with no flags.


### Redirections:

**<:** Redirect input from a file to a command.

**>:** Redirect output of a command to a file, overwriting it.

**>>:** Redirect output to a file in append mode.

**<<:** Implement 'heredoc' functionality, without affecting command history.

**Pipes ( | ):** MiniShel supports piping, allowing the output of one command to serve as input to another.

**Environment Variables:** The shell handles environment variables, enabling users to retrieve or modify values within the shell session.

**Exit Status ($?):** MiniShell tracks and displays the exit status of the last executed command, similar to Bash.

### Signal Handling:

**CTRL-C:** Interrupts the current process.

**CTRL-D:** Exits the shell or sends EOF (End-Of-File) if no process is running.

**CTRL-\:** Quits the current process but doesn't exit the shell.
