/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:52:39 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 15:52:59 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to exit the program
 * 
 * @param cmd get command line array
 * @param env get environment var
 * @return int return error state
 */
int	ft_exit(char **cmd, char **env)
{
	int	i;

	printf("exit\n");
	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i] != '\0')
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				printf("exit: %s: numeric argument required\n", cmd[1]);
				exit(2);
			}
			i++;
		}
		if (cmd[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		clean_tab(env);
		exit(ft_atoi(cmd[1]));
	}
	exit(0);
}
