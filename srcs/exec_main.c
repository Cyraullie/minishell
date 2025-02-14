/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/14 16:54:10 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pipe(t_command *cmd, char ***env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_signals_child();
		exec_redir(cmd, pipefd);
		execute(cmd, env);
	}
	wait_pid(pid, &status, cmd);
	if (cmd->next)
		if (cmd->next->pipe_in)
			dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	return (status);
}

int	standard_exec(t_command **cmd, char ***env)
{
	t_command	*cmd_tmp;
	int			status;

	cmd_tmp = *cmd;
	while (cmd_tmp)
	{
		status = exec_pipe(cmd_tmp, env);
		cmd_tmp = cmd_tmp->next;
	}
	return (status);
}

/**
 * @brief execute the correct builtin we created
 * 
 * @param cmd the linked list of commands
 * @param env 
 */
int	exec_builtin(t_command *cmd_tmp, char ***env, t_command **cmd)
{
	int	rvalue;

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
		rvalue = ft_exit(cmd_tmp->cmd_tab, env, cmd);
	return (rvalue);
}

int	exec_single_builtins(t_command **cmd, char ***env)
{
	int	fdin_cpy;
	int	fdout_cpy;
	int	rvalue;

	fdin_cpy = dup(STDIN_FILENO);
	fdout_cpy = dup(STDOUT_FILENO);
	redir_single_builtin(*cmd);
	rvalue = exec_builtin(*cmd, env, cmd);
	dup2(fdin_cpy, STDIN_FILENO);
	dup2(fdout_cpy, STDOUT_FILENO);
	close(fdin_cpy);
	close(fdout_cpy);
	return (rvalue);
}

/**
 * @brief chooses if we use the standard way of doing the builtins with a child
 * 		  process for every command or if we just stay in the same process
 * 		  (when there is only one command we needed to recreate)
 * 
 * @param cmd the linked list of commands
 * @param env 
 */
void	exec_main(t_command **cmd, char ***env)
{
	pid_t	pid;
	int		status;

	if (!(*cmd)->cmd)
		return ;
	if (!(*cmd)->next && is_builtin((*cmd)->cmd))
	{
		status = exec_single_builtins(cmd, env);
		update_exitvalue(status, env);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			status = standard_exec(cmd, env);
			exit(WEXITSTATUS(status));
		}
		else
			wait_pid(pid, &status, *cmd);
		update_exitvalue(WEXITSTATUS(status), env);
	}
}
