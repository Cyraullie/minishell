/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:23:23 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/23 16:31:03 by cgoldens         ###   ########.fr       */
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

	i = 0;
	name = ft_calloc(sizeof(char *), size + 3);
	if (!name)
		return (NULL);
	while (i < size)
	{
		name[i] = ft_calloc(sizeof(char ), 20);
		if (!name[i++])
		{
			free(name);
			return (NULL);
		}
	}
	i = 0;
	while (tab[i] != -1)
	{
		name[i] = ft_split(env[tab[i]], '=')[0];
		name[++i] = NULL;
	}
	return (name);
}
