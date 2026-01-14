NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Werror -Wextra
DEBUG_FLAGS = -g -DVERBOSE=1
ALLOC_FLAG =  -g -DDEBUG_ALLOC

LIBFT_DIR   = inc/libft
LIBFT       = $(LIBFT_DIR)/libft.a

INCLUDES    = -I inc -I $(LIBFT_DIR)
EXT_LIBS    = -lreadline

SRC_DIR     = src
OBJ_DIR     = obj

SRCS = \
	main.c \
	lexer/lexer.c \
	builtins/cd.c \
	utils/utils.c \
	builtins/pwd.c \
	builtins/env.c \
	utils/signals.c \
	utils/realloc.c \
	utils/verbose.c \
	parser/parser.c \
	builtins/echo.c \
	builtins/exit.c \
	utils/init_env.c \
	builtins/unset.c \
	builtins/export.c \
	executor/heredoc.c \
	lexer/lexer_list.c \
	parser/parser_cmd.c \
	lexer/lexer_utils.c \
	utils/main_cleanup.c \
	lexer/lexer_quotes.c \
	lexer/lexer_checks.c \
	parser/parser_redir.c \
	builtins/update_env.c \
	executor/multi_exec.c \
	lexer/lexer_content.c \
	lexer/lexer_cleanup.c \
	executor/single_exec.c \
	parser/parser_cleanup.c \
	executor/redirections.c \
	executor/landing_file.c \
	builtins/update_export.c \
	executor/child_cleanup.c \
	##executor/extract_path_list.c \

# baue aus z.B. "executor/landing_file.c" -> "obj/executor/landing_file.o"
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ==========================
# Build rules
# ==========================

all: $(LIBFT) $(NAME)

# Debug-Build: CFLAGS erweitern und komplett neu bauen
verbose: CFLAGS += $(DEBUG_FLAGS)
verbose: re

alloc: CFLAGS += $(ALLOC_FLAGS)
alloc: re

# Objektdateien
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/minishell.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(EXT_LIBS) -o $(NAME)

# Libft bauen
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

# ==========================
# Clean rules
# ==========================

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all debug clean fclean re
