/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:44:49 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/19 14:45:59 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_child_process(t_command *cmd, int **pipes, int i,
	t_exec_data *data)
{
	setup_child_pipes(pipes, i, data->cmd_count, cmd);
	if (!is_builtin(cmd->cmd))
		close_child_pipes(pipes, data->cmd_count);
	setup_input_redirection(cmd, *(data->env), data);
	setup_output_redirection(cmd, data);
	if (!cmd->cmd)
		no_command_exit(data, pipes);
	execute(cmd, data->env, data);
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
	int			status;
	int			return_status;
	t_command	*actual_cmd;

	i = cmd_count - 1;
	while (i >= 0)
	{
		actual_cmd = get_cmd_at_index(cmd, i);
		wait_pid(pids[i], &status, actual_cmd);
		if (i == cmd_count -1)
			return_status = status;
		i--;
	}
	free(pids);
	return (return_status);
}

/**
 * @brief Set the up signals child object
 * 
 */
void	setup_signals_child(t_command *cmd)
{
	struct sigaction	sa;
	struct sigaction	sq;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	if (!(!ft_strncmp(cmd->cmd, "./minishell", 12)))
	{
		ft_bzero(&sq, sizeof(sq));
		sq.sa_handler = handle_sigquit;
		sq.sa_flags = 0;
		sigemptyset(&sq.sa_mask);
		sigaction(SIGQUIT, &sq, NULL);
	}
}
