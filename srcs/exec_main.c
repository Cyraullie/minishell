/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/11 10:44:00 by lpittet          ###   ########.fr       */
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
		fdout = pipefd[1];
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

void	execute(t_command *cmd, char ***env)
{
	char	*path;

	if (is_builtin(cmd->cmd))
	{
		exec_single_builtin(cmd, env, &cmd);
		return ;
	}
	path = get_executable_path(cmd, env);
	if(!path)
	{
		perror(cmd->cmd);
		return ;
	}
	execve(path, cmd->cmd_tab, *env);
}

void	exec_pipe(t_command *cmd, char ***env)
{
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
		exec_redir(cmd, pipefd);
		execute(cmd, env);
	}
	wait (NULL);
	if (cmd->pipe_in)
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	standard_exec(t_command **cmd, char ***env)
{
	t_command	*cmd_tmp;
	
	cmd_tmp = *cmd;
	
	while (cmd_tmp)
	{
		exec_pipe(cmd_tmp, env);
		cmd_tmp = cmd_tmp->next;
	}
}

/**
 * @brief execute the correct builtin we created
 * 
 * @param cmd the linked list of commands
 * @param env 
 */
void	exec_single_builtin(t_command *cmd_tmp, char ***env, t_command **cmd)
{
	int	rvalue;

	rvalue = get_exitvalue(*env);
	if (!ft_strncmp(cmd_tmp->cmd, "echo", 5))
		rvalue = ft_echo(cmd_tmp->cmd_tab);
	else if (!ft_strncmp(cmd_tmp->cmd, "cd", 3))
		rvalue = ft_cd(cmd_tmp->cmd_tab, env);
	else if (!ft_strncmp(cmd_tmp->cmd, "pwd", 4))
		rvalue = ft_pwd(cmd_tmp->cmd_tab);
	else if (!ft_strncmp(cmd_tmp->cmd, "export", 7))
		rvalue = ft_export(cmd_tmp->cmd_tab, env);
	else if (!ft_strncmp(cmd_tmp->cmd, "unset", 6))
	{
		*env = ft_unset(cmd_tmp->cmd_tab, *env);
		rvalue = 0;
	}
	else if (!ft_strncmp(cmd_tmp->cmd, "env", 4))
		rvalue = ft_env(cmd_tmp->cmd_tab, *env);
	else if (!ft_strncmp(cmd_tmp->cmd, "exit", 5))
		ft_exit(cmd_tmp->cmd_tab, env, cmd);
	update_exitvalue(rvalue, env);
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
	pid_t	pid;
	int status;
	
	if (!(*cmd)->cmd)
		return ;
	if (!(*cmd)->next && is_builtin((*cmd)->cmd))
		exec_single_builtin(*cmd, env, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
			standard_exec(cmd, env);
		waitpid(pid, &status, 0);
		wait(NULL);
	}
	update_exitvalue(WEXITSTATUS(status), env);	
}
