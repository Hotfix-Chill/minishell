
### COMMANDS THAT ARE NOT GIVING THE RIGHT OUTPUT OR NOT WORKING AS EXPECTED



#### DONE

$ export HEHE=hehe$HEHE$HEHE
$ $HOME$BULLSHIT$USER
	--> /home/pj   '\0'(empty)    pjelinek



#### still not clear, but env with flags are not supposed to work

in minishell command: env -i ./minishell
not starting a new minishell with ignored environment but printing env
instead of starting the shell

-----> nessecary ??


### DONE

$ exit ""

Minshell Output: minishell: parsing error


Bash Output: bash: exit: : numeric argument required
Behavior is handled in builtin exit. The shell exits with status 2.


### DONE


$ cat Makefile >


MINISHELL: no error message! and exits minishell with exit code 0

BASH: Bash sends this error message
bash: syntax error near unexpected token `newline'

HOTFIX:
if there is a redirs token, make sure that filname is not NULL or empty
if filename ist NULL





############################# ARSI DONE

REDIRS: Fix redirections, overall they dont work.
HEREDOC: They lead to segfault and dont get removed.


############################### ARSI / JAN 18 19:32

❯ minishell ▸ $ $ export B=42

should be an: ->>>   error : $: command not found
FOR US it leaves the program, it goes out of it!!
