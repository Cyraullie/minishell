/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 16:09:41 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to check if an array is right
 * 
 * @param env array of environment variable
 * @param i index in array
 */
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

/**
 * @brief check if command is a builtins
 * 
 * @param cmd text of command
 * @return int return true or false
 */
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

/**
 * @brief check if the name of the env contain special char or digit
 * 
 * @param n name of the env var
 * @return int return state 0 if contain forbiden char and 1 if it's ok
 */
int	check_normenv(char *n)
{
	int			i;
	int			j;
	const char	*sc = "!@#-$\%^&+* (){}[]<>?/~`|\\.,:;\"";

	i = 0;
	if (ft_isdigit(n[i]))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		return (0);
	}
	while (n[i])
	{
		j = 0;
		while (sc[j])
		{
			if (n[i] == sc[j])
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
