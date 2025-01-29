/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:01 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/29 10:47:58 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param cmd_tmp 
 * @param env 
 */
void	builtins(t_command *cmd_tmp, char ***env)
{
	if (cmd_tmp->cmd)
	{
		if (!ft_strncmp(cmd_tmp->cmd, "echo", 5))
			ft_echo(cmd_tmp->cmd_tab);
		else if (!ft_strncmp(cmd_tmp->cmd, "cd", 3))
			ft_cd(cmd_tmp->cmd_tab, env);
		else if (!ft_strncmp(cmd_tmp->cmd, "pwd", 4))
			ft_pwd(cmd_tmp->cmd_tab);
		else if (!ft_strncmp(cmd_tmp->cmd, "export", 7))
			*env = ft_export(cmd_tmp->cmd_tab, *env);
		else if (!ft_strncmp(cmd_tmp->cmd, "unset", 6))
			*env = ft_unset(cmd_tmp->cmd_tab, *env);
		else if (!ft_strncmp(cmd_tmp->cmd, "env", 4))
			ft_env(cmd_tmp->cmd_tab, *env);
		else if (!ft_strncmp(cmd_tmp->cmd, "exit", 5))
			ft_exit(cmd_tmp->cmd_tab, *env);
	}
}

/**
 * @brief 
 * 
 * @param cmd_tmp 
 * @param env 
 */
void	handle_redir(t_command *cmd_tmp)
{
	int	fd;

	if (cmd_tmp->write)
	{
		fd = open(cmd_tmp->write, cmd_tmp->write_type, 0755);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_pipe(t_command *cmd_tmp, char ***env)
{
	int		pipefd[2];
	pid_t	pid;

	if (cmd_tmp->next)
	{
		pipe(pipefd);
		pid = fork();
	}
	if (pid == 0)
	{
		if (cmd_tmp->pipe_out)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		builtins(cmd_tmp, env);
		exit(EXIT_SUCCESS);
	}
	if (cmd_tmp->next)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	exec_built(t_command **cmd, char ***env)
{
	t_command	*cmd_tmp;
	int			out_cpy;

	cmd_tmp = *cmd;
	while (cmd_tmp)
	{
		out_cpy = dup(STDOUT_FILENO);
		if (cmd_tmp->write)
			handle_redir(cmd_tmp);
		else
			handle_pipe(cmd_tmp, env);

		builtins(cmd_tmp, env);

		dup2(out_cpy, STDOUT_FILENO);
		close(out_cpy);
		cmd_tmp = cmd_tmp->next;
	}
}
