/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:54:59 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/06 11:23:06 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to display env data
 * 
 * @param cmd get command line array
 * @param env get env data
 * @return int return success or failed
 */
int	ft_env(char **cmd, char **env)
{
	int	i;

	i = -1;
	if (cmd && *cmd)
	{
		if (cmd[1])
		{
			ft_putstr_fd("env: too many arguments\n", 2);
			return (1);
		}
		while (env[++i])
		{
			if (contain_equal(env[i]))
				printf("%s\n", env[i]);
		}
	}
	return (0);
}

/**
 * @brief function to check if line in env contain '='
 * 
 * @param str line in env
 * @return int return true or false
 */
int	contain_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=' && str[0] != '?')
			return (1);
	}
	return (0);
}
