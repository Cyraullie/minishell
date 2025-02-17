/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:54:59 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/17 15:01:35 by lpittet          ###   ########.fr       */
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

/**
 * @brief Get the variable name  after the $ symbol
 * 
 * @param str 
 * @param i the index where we start looking for the var name in str
 * @return char* the env variable name
 */
char	*get_var_name(char *str, int i)
{
	int		len;
	char	*var_name;

	len = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	var_name = ft_substr(str, i - len, len);
	if (!var_name)
		return (NULL);
	return (var_name);
}
