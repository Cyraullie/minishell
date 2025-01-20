/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:30:34 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/20 13:03:51 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to write a text and handle -n option
 * 
 * @param cmd get command line array
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
 * @brief function to exit the program
 * 
 * @param cmd get command line array
 * @return int return error state
 */
int	ft_exit(char **cmd)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (cmd[1][i] != '\0')
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd[1]);
			exit(2);
		}
		i++;
	}
	if (cmd[2])
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (cmd[1])
		exit(ft_atoi(cmd[1]));
	exit(0);
}

/**
 * @brief 
 * 
 * @param env 
 */
/*void	env(char **env)
{

}*/
