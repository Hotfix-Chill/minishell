NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I inc -I $(LIBFT_DIR)  # include dirs
EXT_LIBS = -lreadline

LIBFT_DIR = inc/libft/
LIBFT = $(LIBFT_DIR)libft.a

SRCS = src/cleanup.c src/init_env.c src/main.c src/utils.c src/verbose.c
OBJDIR = obj/
OBJS = $(patsubst src/%.c,$(OBJDIR)%.o,$(SRCS))

# ==========================
# Build rules
# ==========================
all: $(LIBFT) $(NAME)

# Object files
$(OBJDIR)%.o: src/%.c inc/minishell.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(EXT_LIBS) -o $(NAME)

# Build libft
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
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re clean fclean