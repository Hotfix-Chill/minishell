
### COMMANDS THAT ARE NOT GIVING THE RIGHT OUTPUT OR NOT WORKING AS EXPECTED


$ exit ""
minishell: parsing error


exit ""
    Output: bash: exit: : numeric argument required
    Behavior: An empty string is treated as non-numeric. The shell exits with status 2.







#########################################


$ cat Makefile >


MINISHELL: no error message! and exits minishell with exit code 0

BASH: Bash sends this error message
bash: syntax error near unexpected token `newline'

HOTFIX:
if there is a redirs token, make sure that filname is not NULL or empty
if filename ist NULL


