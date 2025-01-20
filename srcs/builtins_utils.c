/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:10:47 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/20 16:06:48 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_valid_flag(char *msg, char flag)
{
	int	i;

	i = 1;
	if (msg[0] == '-')
	{
		while (msg[i])
		{
			if (msg[i] != flag)
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

char	*get_path(void)
{
	char	*p;

	p = malloc(sizeof(char *) * BUFFER_SIZE);
	getcwd(p, BUFFER_SIZE);
	return (p);
}

char	*get_userhome(void)
{
	char	*p;
	char	**p_a;
	char	*u_p;

	u_p = malloc(sizeof(char) * 6);
	u_p = "/home/";
	p = get_path();
	p_a = ft_split(p, '/');
	u_p = ft_strjoin(u_p, p_a[1]);
	return (u_p);
}
