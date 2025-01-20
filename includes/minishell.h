/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/20 13:54:45 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

typedef struct s_command
{
	char	*cmd;
	char	*flags;
	char	**cmd_tab;
}		t_command;

// parsing_utils.c
char	**mini_split(char const *s, char c);

// parsing.c
int		parsing(char *line, t_command *cmd);

// signal.c
void	handle_sigint(int sig);
void	init_sig(void);
void	handle_eof(char *line);

//builtins.c
void	echo(char **cmd);
int		ft_exit(char **cmd);
void	ft_env(char **cmd, char **env);
void	ft_pwd(char **cmd);

//builtins_utils.c
int		find_valid_flag(char *msg, char flag);

#endif