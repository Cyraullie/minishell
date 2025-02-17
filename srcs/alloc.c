/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:23:23 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/17 15:59:41 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief alloc memory for the position array and set it to -1
 * 
 * @param size size of the array
 * @return int* return the array alloc
 */
int	*alloc_pos(int size)
{
	int	*pos;
	int	i;

	pos = ft_calloc(sizeof(int *), size);
	if (!pos)
		return (NULL);
	i = 0;
	while (i < (size))
		pos[i++] = -1;
	return (pos);
}

/**
 * @brief alloc memory for the name array and include name in it
 * 
 * @param size size of the array
 * @param env array with the env elements
 * @param tab array contain the env id for each element
 * @return char** return an array with the name of each element
 */
char	**alloc_name(int size, char **env, int *tab)
{
	char	**name;
	int		i;
	char	**tmp;

	name = ft_calloc(sizeof(char *), size + 3);
	if (!name)
		return (NULL);
	i = 0;
	while (tab[i] != -1)
	{
		tmp = ft_split(env[tab[i]], '=');
		name[i] = ft_strdup(tmp[0]);
		if (!name[i])
			return (clean_tab(name), NULL);
		name[++i] = NULL;
		clean_tab(tmp);
	}
	return (name);
}

void	init_exec_data(t_exec_data *data, t_command *cmd)
{
	data->cmd_count = 0;
	data->cmd_tmp = cmd;
	data->head = cmd;
	while (data->cmd_tmp)
	{
		data->cmd_count++;
		data->cmd_tmp = data->cmd_tmp->next;
	}
	data->pipes = create_pipes(data->cmd_count);
	data->pids = ft_calloc(sizeof(pid_t), data->cmd_count);
}

int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = ft_calloc(sizeof(int *), (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = ft_calloc(sizeof(int), 2);
		if (pipe(pipes[i]) == -1)
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	interrupt_exit(t_exec_data *data)
{
	clean_tab(*data->env);
	ft_listdelete(data->head);
	free(data->pids);
	close_pipes(data->pipes, data->cmd_count);
	exit (0);
}
