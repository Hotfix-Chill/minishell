
### COMMANDS THAT ARE NOT GIVING THE RIGHT OUTPUT OR NOT WORKING AS EXPECTED


$ exit ""

Minshell Output: minishell: parsing error


Bash Output: bash: exit: : numeric argument required
Behavior is handled in builtin exit. The shell exits with status 2.




#########################################


$ cat Makefile >


MINISHELL: no error message! and exits minishell with exit code 0

BASH: Bash sends this error message
bash: syntax error near unexpected token `newline'

HOTFIX:
if there is a redirs token, make sure that filname is not NULL or empty
if filename ist NULL


