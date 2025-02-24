/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:40 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/24 09:54:03 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Create an error msg object print it and exit the child process with 
 * 		  the correct value
 * 
 * @param msg the message to be printed
 * @param string the command or redir file that failed
 * @param data t_exec_data struct
 * @param path path or NULL to be freed
 */
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
	if ((!ft_strncmp(": P", msg, 3) || !ft_strncmp(": I", msg, 3)) && !error)
		error = 126;
	if (!error)
		error = 127;
	string = ft_strjoin(string, msg);
	if (path)
		free(path);
	ft_putstr_fd(string, 2);
	free(string);
	ft_listdelete(data->head);
	if (data->pipes)
		close_pipes(data->pipes, data->cmd_count);
	clean_tab(*data->env);
	free(data->pids);
	exit(error);
}

/**
 * @brief wait for proceess and update it's return value
 * 
 * @param pid the process to be waited
 * @param status the status it returns
 * @param cmd command being run
 */
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

/**
 * @brief clear everything if the command given is empty
 * 
 * @param data t_exec_data struct
 * @param pipes pipe table
 */
void	no_command_exit(t_exec_data *data, int **pipes)
{
	ft_listdelete(data->head);
	clean_tab(*data->env);
	close_pipes(pipes, data->cmd_count);
	free(data->pids);
	exit (0);
}

/**
 * @brief Go to the right command
 * 
 * @param start the first element in linked list
 * @param target_index the target index in the linked list
 * @return t_command* the command at the correct index
 */
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

/**
 * @brief close all pipes read and write end
 * 
 * @param pipes pipes table
 * @param count the number of element in pipes
 */
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
