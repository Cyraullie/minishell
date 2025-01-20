NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra  -g

SRCDIR = srcs/
OBJDIR = objs/

SRCS =  $(addprefix $(SRCDIR), main.c signal.c builtins.c builtins_utils.c)# parsing.c parsing_utils.c)

LIBFT_PATH = libft

LIBFT = $(LIBFT_PATH)/libft.a

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

GREEN = \033[1;32m

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

.PHONY: all clean fclean re
