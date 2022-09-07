# minishell
## Description
This is a School 21 (École 42) group project which I did with [Marina Yudina](https://github.com/marinayudina).  
The goal of this project was to write your own simple bash-like shell.
## Features
Minishell supports following functions:
- working history on arrow keys or `Ctrl` + `R`
- absolute or relative execatable search based on PATH variable
- single quote `'` for prevent the shell from interpreting the metacharacters in the quoted sequence
- double quote `"` for prevent the shell from interpreting the metacharacters in the quoted sequence except for `$` (dollar sign).
- redirections `<`, `>`, `<< EOF`, `>>` which work like in bash 
- pipes `|`
- enviroment variables (`$` followed by a sequence of characters) which
  expand to their values
- `$?` which expands to the exit status of the most recently executed
  foreground pipeline
- `Ctrl`+`C`, `Ctrl`+`D` and `Ctrl`+`Z` which behave like in bash
- builtins:
    - `echo`
    - `cd`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`
## Install and usage
You need [The GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html#Distributions) 
to be installed on you computer to launch minishell.
If are using macOS you should install it via Brew with `brew install readline` command.
On Debian/Ubuntu you can use `sudo apt install libreadline-dev`.  
After installation just clone the project and compile it with make:
```shell
git clone https://github.com/fedor-postnikov/minishell.git
cd minishell
make
```
Then run the shell:
```shell
./minishell
```
