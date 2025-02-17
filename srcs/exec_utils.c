/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:40 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/17 10:39:03 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
