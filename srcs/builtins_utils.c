/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:10:47 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/17 17:34:45 by cgoldens         ###   ########.fr       */
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
