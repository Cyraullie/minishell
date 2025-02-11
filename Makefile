NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra  -g

SRCDIR = srcs/
OBJDIR = objs/

SRCS =  $(addprefix $(SRCDIR), main.c parsing.c split_commands.c create_list.c list.c parsing_utils.c signal.c token.c \
								separate_token.c check.c sort.c alloc.c exec_main.c \
								clean.c history.c echo.c exec_builtins.c \
								syntax.c expansion.c remove_quotes.c \
								exit.c env.c pwd.c cd.c unset.c env_utils.c update_pwd.c export.c concat.c export_utils.c)

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
	@rm  ~/.ms_history*
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

debug: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=ignore_readline_leaks.supp --log-file="leaks.log" ./minishell

.PHONY: all clean fclean re debug
