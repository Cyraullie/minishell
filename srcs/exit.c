/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:52:39 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/05 15:12:32 by cgoldens         ###   ########.fr       */
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
int	ft_exit(char **cmd, char ***env, t_command **og_cmd)
{
	int	i;
	int	value;

	printf("exit\n");
	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i] != '\0')
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				ft_putstr_fd("exit: numeric argument required\n", 2);
				return (exit_and_free(env, og_cmd, 2), 2);
			}
			i++;
		}
		if (cmd[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		value = ft_atoi(cmd[1]);
		return (exit_and_free(env, og_cmd, value), value);
	}
	return (exit_and_free(env, og_cmd, 0), 0);
}

void	free_all(char ***env, t_command **list)
{
	clean_tab(*env);
	ft_listdelete(*list);
}

void	exit_and_free(char ***env, t_command **list, int value)
{
	free_all(env, list);
	exit(value);
}
