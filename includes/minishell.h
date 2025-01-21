/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/21 15:27:39 by cgoldens         ###   ########.fr       */
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
void	handle_eof(char *line, char **env);

//builtins.c
void	ft_echo(char **cmd);
int		ft_exit(char **cmd, char **env);
void	ft_env(char **cmd, char **env);
void	ft_pwd(char **cmd);
void	ft_cd(char **cmd);

//builtins2.c
char	**ft_unset(char **cmd, char **env);
char	**ft_export(char **cmd, char **env);

//builtins_utils.c
int		find_valid_flag(char *msg, char flag);
char	*get_userhome(void);
char	*get_path(void);
char	**del_line(char **env, char *title);
int		get_envline(char **env, char *title);
void	del_envline(char **env, char **nenv, char *title);

//builtins_utils2.c
void	write_env(char **env);

//clean.c
void	clean_env(char **env);

#endif