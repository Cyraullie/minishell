/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/23 16:44:59 by cgoldens         ###   ########.fr       */
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
void	add_envline(char **env, char **nenv, char *title, char **name);
void	dup_env(char **env, char **nenv, int i, int j);
char	**create_nenv(char **env, char **name);
int		check_normenv(char *n);
void	sort_env(char **env, int *tab);

//clean.c
void	clean_env(char **env);

//check.c
void	check_tabenv(char **env, int i);
int		is_order(int *pos, char **name);
int		get_maxlength_env(char **name);

//sort.c
void	sort_tab(char **env, int *tab, int size);
void	get_by_letter(char c, char **env, int *tab);
void	sort_env(char **env, int *tab);
void	get_pos(int *pos, char **name);
void	move_tab(char **name, int *tab, int *pos);

//alloc.c
char	**alloc_name(int size, char **env, int *tab);
int		*alloc_pos(int size);

#endif