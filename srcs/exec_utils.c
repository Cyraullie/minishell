/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:40 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/13 14:05:20 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_single_builtin(t_command *cmd)
{
	int	fd;

	if (cmd->read)
	{
		fd = open(cmd->read, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->write)
	{
		fd = open(cmd->write, cmd->write_type, 0755);
		if (fd == -1)
		{
			perror("open");
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

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
	{
		perror(cmd->cmd);
		return ;
	}
	execve(path, cmd->cmd_tab, *env);
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
