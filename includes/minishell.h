/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 13:34:29 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif
# ifndef HISTORY_FILE
#  define HISTORY_FILE "/.ms_history"
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
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

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

typedef struct s_exec_data
{
	int			cmd_count;
	t_command	*cmd_tmp;
	int			**pipes;
	pid_t		*pids;
	char		***env;
	t_command	*head;
}	t_exec_data;

// split_commands.c
char		**mini_split(char *s);
int			ft_isspace(int c);
void		toggle_quotes(char *s, int i, int *in_d_quotes, int *in_s_quotes);

// parsing.c
int			parsing(char *line, t_command **cmd, char ***env);
char		*ft_strjoin_and_free(char *s1, char *s2);

// create_list.c
void		create_list(char *line, t_command **cmd);

//echo.c
int			ft_echo(char **cmd);
int			find_valid_flag(char *msg, char flag);

//exit.c
int			ft_exit(char **cmd, char ***env, t_command **og_cmd);
void		free_all(char ***env, t_command **list);
void		exit_and_free(char ***env, t_command **list, int value);

//env.c
int			ft_env(char **cmd, char **env);
int			contain_equal(char *str);
char		*get_var_name(char *str, int i);

//pwd.c
int			ft_pwd(void);

//cd.c
int			ft_cd(char **cmd, char ***env);
char		*get_path(void);
char		*get_userhome(char **env);
int			ft_chdir(char *path, char ***env, char *userhome);
int			check_dir(char *path);

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
char		**split_equal(char *str);
char		*ft_strdup_and_free(char *s);

//clean.c
void		clean_tab(char **env);
void		interrupt_exit(t_exec_data *data);

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
void		init_exec_data(t_exec_data *data, t_command *cmd);
int			**create_pipes(int cmd_count);

// list.c
t_command	*ft_listnew(char **content);
t_command	*ft_listlast(t_command *list);
void		ft_listadd_back(t_command **list, t_command *new);
void		ft_listdelete(t_command *list);

// signal.c
void		handle_sigint(int sig);
void		handle_eof(char *line, char **env);
int			is_child(int status);
void		setup_signals_parent(void);
void		handle_sigquit(int sig);

// init.c
void		init_sig(void);
void		increment_shlvl(char ***env);
void		init_minishell(char ***env, char **envp);

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
int			check_syntax(char *line, char ***env);

// expansion.c
char		**expansion(char **tab, char **env);
int			get_new_len(char *str, char **env, int in_d_quotes, \
			int in_s_quotes);
char		*get_var_name(char *str, int i);
void		replace_var(char *token, char *new_token, int *index, char **env);

// remove_quotes.c
char		*remove_quotes(char *token);

//exec_builtins
void		exec_bash(t_command *cmd_tmp, char ***env);
void		update_exitvalue(int eval, char ***env);
int			get_exitvalue(char **env);
int			exec_builtin(t_command *cmd_tmp, char ***env, t_command **cmd);

// heredoc_sig.c
void		setup_signals_heredoc(void);

//heredoc.c
int			heredoc_redir(t_command *cmd, char **env);
int			max(int first, int second);
char		*heredoc_expansion(char *line, char **env);

// exec_main.c
void		execute(t_command *cmd, char ***env, t_exec_data *data);
int			execute_commands(t_exec_data *data, t_command *first_cmd);
void		exec_main(t_command **cmd, char ***env, int status);
int			standard_exec(t_command **cmd, char ***env);

// exec_path.c
char		*get_executable_path(t_command *cmd, char ***env,
				t_exec_data *data);
char		*find_path(char *cmd, char ***env);
char		*search_env(char **env);
char		*get_full_path(char *path, char *cmd);
int			check_slash(char *path);

// exec_utils.c
void		create_error_msg(char *msg, char *string, t_exec_data *data,
				char *path);
void		wait_pid(pid_t pid, int *status, t_command *cmd);
void		no_command_exit(t_exec_data *data, int **pipes);
t_command	*get_cmd_at_index(t_command *start, int target_index);
void		close_pipes(int **pipes, int count);

// redir.c
t_command	*setup_redir_read(t_command *cmd, int i, char **env);
int			redir_single_builtin(t_command *cmd, char **env);
void		setup_input_redirection(t_command *cmd, char **env,
				t_exec_data *data);
void		setup_output_redirection(t_command *cmd, t_exec_data *data);

// child.c
int			handle_child_process(t_command *cmd, int **pipes, int i,
				t_exec_data *data);
void		close_child_pipes(int **pipes, int cmd_count);
void		setup_child_pipes(int **pipes, int i, int cmd_count,
				t_command *cmd);
int			wait_for_processes(pid_t *pids, int cmd_count, t_command *cmd);
void		setup_signals_child(t_command *cmd);

// single_builtin.c
int			exec_single_builtins(t_command **cmd, char ***env);
int			exec_builtin(t_command *cmd_tmp, char ***env, t_command **cmd);

extern volatile sig_atomic_t	g_heredoc_interrupted;

#endif