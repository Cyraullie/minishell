NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra  -g

SRCDIR = srcs/
OBJDIR = objs/

SRCS =  $(addprefix $(SRCDIR), main.c parsing.c split_commands.c create_list.c list.c parsing_utils.c signal.c token.c separate_token.c check.c sort.c alloc.c builtins.c builtins2.c clean.c builtins_utils.c builtins_utils2.c builtins_utils3.c)
LIBFT_PATH = libft

LIBFT = $(LIBFT_PATH)/libft.a

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

GREEN = \033[1;32m
RESET = \033[0m

all: header $(NAME)

header:
	@echo "$(GREEN)"
	@echo "              _       _      __         ____"
	@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
	@echo "  / __ \`__ \/ / __ \/ / ___/ __ \/ _ \/ / / "
	@echo " / / / / / / / / / / (__  ) / / /  __/ / /  "
	@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/   "
	@echo "                                            "
	@echo "$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)


$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

debug: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp ./minishell

.PHONY: all clean fclean re
