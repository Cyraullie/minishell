/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 11:21:16 by lpittet          ###   ########.fr       */
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
		rvalue = exec_builtin(cmd, env, &cmd);
		clean_tab(*data->env);
		ft_listdelete(data->head);
		free(data->pids);
		close_pipes(data->pipes, data->cmd_count);
		exit(rvalue);
	}
	path = get_executable_path(cmd, env, data);
	if (!path || !cmd->cmd[0])
		create_error_msg(": command not found\n", cmd->cmd, data, path);
	if (execve(path, cmd->cmd_tab, *env) == -1)
	{
		perror("execve failed");
		exit(1);
	}
	exit(0);
}

/**
 * @brief loop through all the command of the linked list 
 * 		  and execute all commands
 * 
 * @param data t_exec_data struct
 * @param first_cmd the first element of the linked list
 * @return int 0 on success 1 on failure
 */
int	execute_commands(t_exec_data *data, t_command *first_cmd)
{
	int			i;
	t_command	*current_cmd;

	i = 0;
	setup_signals_parent();
	while (i < data->cmd_count)
	{
		current_cmd = get_cmd_at_index(first_cmd, i);
		data->cmd_tmp = current_cmd;
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (1);
		if (data->pids[i] == 0)
		{
			setup_signals_child(first_cmd);
			handle_child_process(current_cmd, data->pipes, i, data);
		}
		i++;
	}
	if (data->pipes)
		close_pipes(data->pipes, data->cmd_count);
	return (0);
}

/**
 * @brief manager for exec that need forks
 * 
 * @param cmd the commnand linked list
 * @param env env variable
 * @return int 
 */
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

/**
 * @brief check what type of exec is needed and call it
 * 
 * @param cmd t_command linkde list
 * @param env **env variable
 * @param status 
 */
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
			setup_signals_child(*cmd);
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
