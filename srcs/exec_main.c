/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/17 14:09:26 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief execute the command given as argument
 * 
 * @param cmd the command to be executed
 * @param env the environnement variable
 */
void	execute(t_command *cmd, char ***env, t_exec_data *data)
{
	char	*path;
	int		rvalue;

	if (is_builtin(cmd->cmd))
	{
		rvalue = exec_builtin(cmd, env, &cmd); //TODO free what need be
		clean_tab(*data->env);
		ft_listdelete(data->head);
		free(data->pids);
		close_pipes(data->pipes, data->cmd_count);
		exit(rvalue);
	}
	path = get_executable_path(cmd, env, data);
	if (!path)
		create_error_msg(": command not found\n", cmd->cmd, 127, data);
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
	setup_signals_parent();
	while (i >= 0)
	{
		current_cmd = get_cmd_at_index(first_cmd, i);
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (1);
		if (data->pids[i] == 0)
		{
			setup_signals_child();
			handle_child_process(current_cmd, data->pipes, i, data);
		}
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
	status = wait_for_processes(data.pids, data.cmd_count, *cmd);
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
		setup_signals_parent();
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			setup_signals_child();
			status = standard_exec(cmd, env);
			ft_listdelete(*cmd);
			clean_tab(*env);
			exit(WEXITSTATUS(status));
		}
		else
			wait_pid(pid, &status, *cmd);
		update_exitvalue(WEXITSTATUS(status), env);
	}
}

//TODO child leaks if builtins in standard exec