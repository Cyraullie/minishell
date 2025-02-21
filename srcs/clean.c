/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:40:24 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/21 09:44:33 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to free env
 * 
 * @param tab 2D malloc array
 */
void	clean_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	interrupt_exit(t_exec_data *data)
{
	clean_tab(*data->env);
	ft_listdelete(data->head);
	free(data->pids);
	close_pipes(data->pipes, data->cmd_count);
	exit (0);
}