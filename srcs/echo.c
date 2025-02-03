/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:49:45 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 15:50:42 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to check if the flag are present in msg
 * 
 * @param msg string
 * @param flag character
 * @return int 
 */
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

/**
 * @brief function to write a text and handle -n option
 * 
 * @param cmd get command line array
 */
void	ft_echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	if (cmd[i])
	{
		n = find_valid_flag(cmd[i], 'n');
		while (cmd[i] && find_valid_flag(cmd[i], 'n'))
			i++;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
		if (!n)
			printf("\n");
	}
	else
		printf("\n");
}
