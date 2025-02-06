/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/06 11:53:29 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif
# ifndef HISTORY_FILE
#  define HISTORY_FILE ".ms_history"
# endif
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include <sys/wait.h>

typedef struct s_command
{
	char				*read;
	int					heredoc;
	int					pipe_in;
	char				*write;
	int					write_type;
	int					pipe_out;
	char				*cmd;
	char				**cmd_tab;
	char				**raw;
	struct s_command	*next;
}	t_command;

// split_commands.c
char		**mini_split(char *s);
int			ft_isspace(int c);
void		toggle_quotes(char *s, int i, int *in_d_quotes, int *in_s_quotes);

// parsing.c
int			parsing(char *line, t_command **cmd, char **env);
char		*ft_strjoin_and_free(char *s1, char *s2);

// create_list.c
void		create_list(char *line, t_command **cmd);

// signal.c
void		handle_sigint(int sig);
void		init_sig(void);
void		handle_eof(char *line, char **env);

//echo.c
void		ft_echo(char **cmd);
int			find_valid_flag(char *msg, char flag);

//exit.c
int			ft_exit(char **cmd, char ***env, t_command **og_cmd);
void		free_all(char ***env, t_command **list);
void		exit_and_free(char ***env, t_command **list, int value);

//env.c
int			ft_env(char **cmd, char **env);
int			contain_equal(char *str);

//pwd.c
void		ft_pwd(char **cmd);

//cd.c
int			ft_cd(char **cmd, char ***env);
char		*get_path(void);
char		*get_userhome(void);
void		ft_chdir(char **cmd, char ***env);

//update_pwd.c
void		update_pwd(char *path, char ***env);
void		update_oldpwd(char *path, char ***env);

//unset.c
char		**ft_unset(char **cmd, char **env);
void		del_envline(char **env, char **nenv, char *title);

//env_utils.c
int			get_envline(char **env, char *title);
char		*get_env_content(char *var_name, char **env);
char		**create_env_array(char **envp);

//export.c
int			ft_export(char **cmd, char ***env);
void		write_env(char **env);
char		**handle_export(char *arg, char **env, char ***nenv);
char		**create_nenv(char **env, char **name);
void		dup_env(char **env, char **nenv, int i, int j);

//concat.c
void		handle_concat(char **env, char ***nenv, char **name);
void		concat_existvar(char *env, char ***nenv, char **name, int j);
void		concat_nexistvar(char ***nenv, char **name, int j);

//export_utils.c
void		add_envline(char **env, char **nenv, char *title, char **name);
void		add_envline_without_content(char **env, char **nenv, char **name);
char		*multiple_equal(char **a_str);
char		*my_getenv(char *var_name, char **env);
char		**split_equal(char *str);

//clean.c
void		clean_tab(char **env);

//check.c
void		check_tabenv(char **env, int i);
int			is_order(int *pos, char **name);
int			get_maxlength_env(char **name);
int			is_builtin(char *cmd);
int			check_normenv(char *n);

//sort.c
void		sort_tab(char **env, int *tab, int size);
void		get_by_letter(char *c, char **env, int *tab);
void		sort_env(char **env, int *tab);
void		get_pos(int *pos, char **name);
void		move_tab(char **name, int *tab, int *pos);

//alloc.c
char		**alloc_name(int size, char **env, int *tab);
int			*alloc_pos(int size);

// list.c
t_command	*ft_listnew(char **content);
t_command	*ft_listlast(t_command *list);
void		ft_listadd_back(t_command **list, t_command *new);
void		ft_listdelete(t_command *list);

// signal.c
void		handle_sigint(int sig);
void		init_sig(void);
void		handle_eof(char *line, char **env);

// token.c
void		assign_token(t_command **cmd, char **env);

// separate_token.c
char		*separate_tokens(char *line);

//history.c
void		handle_history(char *line, char **env);
void		start_history(char **env);

// parsing_utils.c
int			ft_isredir(int c);
int			open_previous_file(t_command *cmd);
int			get_tab_size(char **tab);

// exec_builtins.c
void		exec_built(t_command **cmd, char ***env);

// syntax.c
int			check_syntax(char *line);

// expansion.c
char		**expansion(char **tab, char **env);

// remove_quotes.c
char		*remove_quotes(char *token);

void		exec_bash(t_command *cmd_tmp, char ***env);

#endif