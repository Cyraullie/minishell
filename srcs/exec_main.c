/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/07 11:24:53 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*get_full_path(char *path, char *cmd)
{
	path = ft_strjoin(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin(path, cmd);
	if (!path)
		return (NULL);
	return (path);
}

static	char	*search_env(char **env)
{
	int		i;
	char	*path_list;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_list = env[i];
			return (path_list + 5);
		}
		i++;
	}
	ft_putendl_fd("PATH not found", 2);
	return (NULL);
}

char	*find_path(char *cmd, char ***env)
{
	char	*path_list;
	char	**src;
	int		i;
	char	*path;

	path_list = search_env(*env);
	if (!path_list)
		exit(1);
	src = ft_split(path_list, ':');
	i = 0;
	while (src[i])
	{
		path = get_full_path(src[i], cmd);
		if (!access(path, F_OK))
		{
			clean_tab(src);
			return (path);
		}
		free(path);
		i++;
	}
	free(src);
	return (NULL);
}

char	*get_executable_path(t_command *cmd, char ***env)
{
	char	*path;
	
	//TODO check directory
	path = find_path(cmd->cmd, env);
	if (!access(path, X_OK))
		return (path);
	if (!access(cmd->cmd, F_OK))
	{
		if (!access(cmd->cmd, X_OK))
			return (cmd->cmd);
	}
	return (NULL);
}

void	exec_redir(t_command *cmd, int pipefd[2])
{
	int	fdin;
	int	fdout;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	if (cmd->pipe_out)
		fdout = dup(pipefd[1]);
	if (cmd->read)
		fdin = open(cmd->read, O_RDONLY);
	if (cmd->write)
		fdout = open(cmd->write, cmd->write_type, 0755);
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	if (fdin != STDIN_FILENO)
		close(fdin);
	if ((fdout != STDOUT_FILENO))
		close(fdout);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	exec_pipe(t_command *cmd, char ***env)
{
	char	*path;
	int 	pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		path = get_executable_path(cmd, env);
		if (!path)
		{
			perror(cmd->cmd);
			return ;
		}
		exec_redir(cmd, pipefd);
		//TODO check if builtins or not new function exectute I guess
		execve(path, cmd->cmd_tab, *env);
	}
	if (cmd->pipe_in)
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
}

void	standard_exec(t_command **cmd, char ***env)
{
	t_command	*cmd_tmp;
	int			cpy_in;
	int			cpy_out;
	
	cmd_tmp = *cmd;
	while (cmd_tmp)
	{
		cpy_in = STDIN_FILENO;
		cpy_out = STDOUT_FILENO;
		exec_pipe(cmd_tmp, env);
		dup2(STDIN_FILENO, cpy_in);
		dup2(STDOUT_FILENO, cpy_out);
		cmd_tmp = cmd_tmp->next;
	}
}

/**
 * @brief execute the correct builtin we created
 * 
 * @param cmd the linked list of commands
 * @param env 
 */
void	exec_single_builtin(t_command **cmd, char ***env)
{

	if (!ft_strncmp((*cmd)->cmd, "echo", 5))
		ft_echo((*cmd)->cmd_tab);
	else if (!ft_strncmp((*cmd)->cmd, "cd", 3))
		ft_cd((*cmd)->cmd_tab, env);
	else if (!ft_strncmp((*cmd)->cmd, "pwd", 4))
		ft_pwd((*cmd)->cmd_tab);
	else if (!ft_strncmp((*cmd)->cmd, "export", 7))
		*env = ft_export((*cmd)->cmd_tab, *env);
	else if (!ft_strncmp((*cmd)->cmd, "unset", 6))
		*env = ft_unset((*cmd)->cmd_tab, *env);
	else if (!ft_strncmp((*cmd)->cmd, "env", 4))
		ft_env((*cmd)->cmd_tab, *env);
	else if (!ft_strncmp((*cmd)->cmd, "exit", 5))
		ft_exit((*cmd)->cmd_tab, *env);
	
	//TODO change the $ value (idk where/how yet)
}

/**
 * @brief chooses if we use the standard way of doing the builtins with a child
 * 		  process for every command or if we just stay in the same process
 * 		  (when there is only one command that we needed to recreate)
 * 
 * @param cmd the linked list of commands
 * @param env 
 */
void	exec_main(t_command **cmd, char ***env)
{
	if (!(*cmd)->cmd)
		return ;
	if (!(*cmd)->next && is_builtin((*cmd)->cmd))
		exec_single_builtin(cmd, env);
	else
		standard_exec(cmd, env);
}
