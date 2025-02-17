/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:44:49 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/17 14:03:27 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_child_process(t_command *cmd, int **pipes, int i,
	t_exec_data *data)
{
	setup_child_pipes(pipes, i, data->cmd_count, cmd);
	close_child_pipes(pipes, data->cmd_count);
	setup_input_redirection(cmd, *(data->env));
	setup_output_redirection(cmd);
	if (!cmd->cmd)
		no_command_exit(data, pipes);
	execute(cmd, data->env);
	return (1);
}

void	close_child_pipes(int **pipes, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	setup_child_pipes(int **pipes, int i, int cmd_count, t_command *cmd)
{
	if (i < cmd_count - 1 && cmd->pipe_out)
		dup2(pipes[i][1], STDOUT_FILENO);
	if (i > 0 && cmd->pipe_in)
		dup2(pipes[i - 1][0], STDIN_FILENO);
}

int	wait_for_processes(pid_t *pids, int cmd_count, t_command *cmd)
{
	int			i;
	int			status[100];
	t_command	*actual_cmd;

	i = cmd_count - 1;
	while (i >= 0)
	{
		actual_cmd = get_cmd_at_index(cmd, i);
		wait_pid(pids[i], &status[i], actual_cmd);
		i--;
	}
	free(pids);
	return (status[cmd_count - 1]);
}
