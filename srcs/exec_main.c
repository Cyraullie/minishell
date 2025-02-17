/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/17 10:10:17 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	execute_commands(t_exec_data *data, t_command *first_cmd)
{
	int			i;
	t_command	*current_cmd;

	i = data->cmd_count - 1;
	while (i >= 0)
	{
		current_cmd = get_cmd_at_index(first_cmd, i);
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (1);
		if (data->pids[i] == 0)
			handle_child_process(current_cmd, data->pipes, i, data);
		i--;
	}
	if (data->pipes)
		close_pipes(data->pipes, data->cmd_count);
	return (0);
}

int	standard_exec(t_command **cmd, char ***env)
{
	t_exec_data	data;
	int			status;

	data.env = env;
	init_exec_data(&data, *cmd);
	if (!data.pids)
	{
		if (data.pipes)
			close_pipes(data.pipes, data.cmd_count);
		return (1);
	}
	if (execute_commands(&data, *cmd))
	{
		free(data.pids);
		return (1);
	}
	status = wait_for_processes(data.pids, data.cmd_count);
	return (status);
}

void	exec_main(t_command **cmd, char ***env, int status)
{
	pid_t	pid;

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
			ft_listdelete(*cmd);
			clean_tab(*env);
			exit(WEXITSTATUS(status));
		}
		else
			wait_pid(pid, &status);
		update_exitvalue(WEXITSTATUS(status), env);
	}
}

//TODO child leaks on command not found
//TODO child leaks if builtins in standard exec
//TODO permission denied leaks