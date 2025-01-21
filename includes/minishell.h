/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/21 13:05:02 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

typedef struct s_command
{
	char				*read;
	mode_t				read_type;
	char				*write;
	mode_t				write_type;
	char				*cmd;
	char				*flags;
	char				**cmd_tab;
	char				**raw;
	struct s_command	*next;
} t_command;


// split_commands.c
char		**mini_split(char *s);
int 		ft_isspace(int c);
void		toggle_quotes(char *c, int i, int *in_d_quotes, int *in_s_quotes);

// parsing.c
int			parsing(char *line, t_command **cmd, char **env);
void		free_tab(char **tab);

// create_list.c
void 		create_list(char *line, t_command **cmd);

// list.c
t_command	*ft_listnew(char **content);
t_command	*ft_listlast(t_command *list);
void		ft_listadd_back(t_command **list, t_command *new);
void		ft_listdelete(t_command *list);


// signal.c
void	handle_sigint(int sig);
void	init_sig(void);
void	handle_eof(char *line);

#endif