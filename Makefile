NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra  -g

SRCDIR = srcs/
OBJDIR = objs/

SRCS =  $(addprefix $(SRCDIR), main.c)

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) 

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
