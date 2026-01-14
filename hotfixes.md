
### COMMANDS THAT ARE NOT GIVING THE RIGHT OUTPUT OR NOT WORKING AS EXPECTED

$ cat Makefile >


MINISHELL: no error message! and exits minishell with exit code 0

BASH: Bash sends this error message
bash: syntax error near unexpected token `newline'

HOTFIX:
if there is a redirs token, make sure that filname is not NULL or empty
if filename ist NULL


############################# ARSI

REDIRS: Fix redirections, overall they dont work.
HEREDOC: They lead to segfault and dont get removed.