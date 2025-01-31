/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/30 14:18:56 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_tabenv(char **env, int i)
{
	if (!env[i])
	{
		clean_tab(env);
		return ;
	}
}

/**
 * @brief check if all env tab is sorted
 * 
 * @param pos position for each element in env
 * @param name name for each element in env
 * @return int 0 if it isnt sorted 1 if it's sorted
 */
int	is_order(int *pos, char **name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (pos[i] != -1)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Get the maxlength env name
 * 
 * @param name array of all name form env
 * @return int return size of most length name
 */
int	get_maxlength_env(char **name)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (name[++i])
	{
		if ((int)ft_strlen(name[i]) > len)
			len = ft_strlen(name[i]);
	}
	return (len);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}