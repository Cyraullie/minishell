/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:08:14 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/21 13:09:59 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief create a new node for a chained list initializing the
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
	new->flags = NULL;
	new->read = NULL;
	new->read_type = 0;
	new->write = NULL;
	new->write_type = 0;
	new->next = NULL;
	return (new);
}

/**
 * @brief get the last element of a chained list
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
	free_tab(list->raw);
	if (list->cmd_tab)
		free_tab(list->cmd_tab);
	free(list);
	if (temp)
		ft_listdelete(temp);
}