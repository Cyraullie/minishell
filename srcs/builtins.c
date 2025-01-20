/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:30:34 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/20 11:03:48 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param msg 
 * @param n 
 */
void	echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	n = find_valid_flag(cmd[i], 'n');
	while (find_valid_flag(cmd[i], 'n'))
	{
		i++;
	}
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			printf(" ");
	}
	if (!n)
		printf("\n");
}

/**
 * @brief 
 * 
 * @param env 
 */
/*void	env(char **env)
{

}*/
