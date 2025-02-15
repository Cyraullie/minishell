/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:40 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/15 11:19:53 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief setup the correct redirection in case of a single builtin
 * 
 * @param cmd 
 * @return int 0 on succes, 126 on failure (UNIX permission denied)
 */
int	redir_single_builtin(t_command *cmd, char **env)
{
	int	fd;

	if (cmd->read)
	{
		if (cmd->heredoc)
			fd = heredoc_redir(cmd, env);
		else
			fd = open(cmd->read, O_RDONLY);
		if (fd == -1)
			return (perror(cmd->read), 126);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->write)
	{
		fd = open(cmd->write, cmd->write_type, 0755);
		if (fd == -1)
			return (perror(cmd->write), 126);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

/**
 * @brief execute the command given as argument
 * 
 * @param cmd the command to be executed
 * @param env the environnement variable
 */
void	execute(t_command *cmd, char ***env)
{
	char	*path;
	int		rvalue;

	if (is_builtin(cmd->cmd))
	{
		rvalue = exec_builtin(cmd, env, &cmd);
		exit(rvalue);
	}
	path = get_executable_path(cmd, env);
	if (!path)
		create_error_msg(": command not found\n", cmd->cmd, 127);
	if (execve(path, cmd->cmd_tab, *env) == -1)
	{
		perror("execve failed");
		exit(1);
	}
	exit(0);
}

/**
 * @brief setup redirections for the given command
 * 
 * @param cmd a command in the linked list
 * @param pipefd the 2 fds from a pipe
 * @param env the environnement variable
 */
void	exec_redir(t_command *cmd, int pipefd[2], char **env)
{
	int	fdin;
	int	fdout;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	if (cmd->pipe_out)
		fdout = pipefd[1];
	if (cmd->read)
		fdin = setup_redir_in(cmd, env);
	if (cmd->write)
		fdout = open(cmd->write, cmd->write_type, 0755);
	if (fdout == -1)
	{
		perror(cmd->write);
		exit(1);
	}
	if (!cmd->pipe_in)
		dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	if (fdin != STDIN_FILENO)
		close(fdin);
	if ((fdout != STDOUT_FILENO))
		close(fdout);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	create_error_msg(char *msg, char *string, int error_status)
{
	string = ft_strjoin_and_free(string, msg);
	ft_putstr_fd(string, 2);
	exit(error_status);
}

void	wait_pid(pid_t pid, int *status)
{
	is_child(1);
	waitpid(pid, status, 0);
	is_child(0);
}
