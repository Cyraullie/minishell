/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:08:14 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/24 10:08:50 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief create a new node for a linked list initializing the
 * 		  raw data only
 * 
 * @param content 
 * @return t_command* 
 */
t_command	*ft_listnew(char **content)
{
	t_command	*new;

	new = calloc(sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->raw = content;
	new->cmd = NULL;
	new->cmd_tab = NULL;
	new->run = 1;
	new->read = NULL;
	new->heredoc = 0;
	new->pipe_in = 0;
	new->pipe_out = 0;
	new->write = NULL;
	new->write_type = 0;
	new->next = NULL;
	return (new);
}

/**
 * @brief get the last element of a linked list
 * 
 * @param list 
 * @return t_command* 
 */
t_command	*ft_listlast(t_command *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

/**
 * @brief add the new element at the end of the list
 * 
 * @param list 
 * @param new 
 */
void	ft_listadd_back(t_command **list, t_command *new)
{
	if (*list)
		ft_listlast(*list)->next = new;
	else
		*list = new;
}

/**
 * @brief goes through a list to delete and free everything
 * 
 * @param list 
 */
void	ft_listdelete(t_command *list)
{
	t_command	*temp;

	temp = NULL;
	if (list->next)
		temp = list->next;
	clean_tab(list->raw);
	if (list->cmd_tab)
		clean_tab(list->cmd_tab);
	free(list);
	if (temp)
		ft_listdelete(temp);
}
