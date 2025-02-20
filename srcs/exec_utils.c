/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:40 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/20 10:14:41 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_error_msg(char *msg, char *string, t_exec_data *data, char *path)
{
	int	error;

	error = 0;
	if (data->cmd_tmp->read)
		if (!ft_strncmp(string, data->cmd_tmp->read, ft_strlen(string) + 1))
			error = 1;
	if (data->cmd_tmp->write)
		if (!ft_strncmp(string, data->cmd_tmp->write, ft_strlen(string) + 1))
			error = 1;
	if ((!ft_strncmp(": N", msg, 3) || !ft_strncmp(": I", msg, 3)) && !error)
		error = 126;
	if (!error)
		error = 127;
	string = ft_strjoin(string, msg);
	if (path)
		free(path);
	ft_putstr_fd(string, 2);
	free(string);
	ft_listdelete(data->head);
	clean_tab(*data->env);
	free(data->pids);
	exit(error);
}

void	wait_pid(pid_t pid, int *status, t_command *cmd)
{
	int	signal;

	is_child(1);
	if (cmd->cmd)
		if (!ft_strncmp(cmd->cmd, "./minishell", 12))
			is_child(2);
	waitpid(pid, status, 0);
	is_child(0);
	if (WIFSIGNALED(*status))
	{
		signal = WTERMSIG(*status);
		if (signal == SIGINT)
			write(1, "\n", 1);
	}
}

void	no_command_exit(t_exec_data *data, int **pipes)
{
	ft_listdelete(data->head);
	clean_tab(*data->env);
	close_pipes(pipes, data->cmd_count);
	free(data->pids);
	exit (0);
}

t_command	*get_cmd_at_index(t_command *start, int target_index)
{
	t_command	*current;
	int			i;

	current = start;
	i = 0;
	while (i < target_index && current)
	{
		current = current->next;
		i++;
	}
	return (current);
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
