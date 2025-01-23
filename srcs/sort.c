/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:21:19 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/23 16:36:25 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to sort env
 * 
 * @param env array of environment variable
 * @param tab array of env id
 * @param size size of the array
 */
void	sort_tab(char **env, int *tab, int size)
{
	char	**name;
	int		*pos;

	name = alloc_name(size, env, tab);
	pos = alloc_pos(size);
	get_pos(pos, name);
	while (!is_order(pos, name))
		move_tab(name, tab, pos);
	clean_env(name);
	free(pos);
}

/**
 * @brief function to add in tab each element of env by letter
 * 
 * @param c contain a letter
 * @param env array of environment variable
 * @param tab array of env id
 */
void	get_by_letter(char c, char **env, int *tab)
{
	int			i;
	static int	j;

	i = 0;
	if (c == 'A')
		j = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], &c, 1))
			tab[j++] = i;
		i++;
	}
	tab[j] = -1;
}

/**
 * @brief function to handle each letter
 * 
 * @param env array of environment variable
 * @param tab array of env id
 */
void	sort_env(char **env, int *tab)
{
	char	c;
	int		i;

	c = 'A';
	i = 0;
	while (c != 123)
	{
		get_by_letter(c, env, tab);
		if (c == 'Z')
			c = 'a';
		else
			c++;
	}
	while (env[i])
		i++;
	sort_tab(env, tab, i);
}

/**
 * @brief Get the position of each element in name
 * 
 * @param pos array of position
 * @param name array of name
 */
void	get_pos(int *pos, char **name)
{
	int	i;
	int	p;
	int	x;
	int	max_len;

	i = -1;
	max_len = get_maxlength_env(name) + 10;
	while (name[++i] != NULL)
	{
		p = 0;
		x = -1;
		while (name[++x] != NULL)
		{
			if (ft_strncmp(name[i], name[x], max_len) > 0)
				p++;
		}
		if (i != p)
			pos[i] = p;
		else
			pos[i] = -1;
	}
}

/**
 * @brief function to move the position of two element in array
 * 
 * @param name array of name
 * @param tab array of env id
 * @param pos array of position
 */
void	move_tab(char **name, int *tab, int *pos)
{
	int		tmp;
	char	*tn;
	int		i;

	tmp = 0;
	i = 0;
	while (name[i])
	{
		if (pos[i] != -1)
		{
			tmp = tab[i];
			tab[i] = tab[pos[i]];
			tab[pos[i]] = tmp;
			tn = name[i];
			name[i] = name[pos[i]];
			name[pos[i]] = tn;
			get_pos(pos, name);
		}
		i++;
	}
}
