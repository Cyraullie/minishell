/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:10:47 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 10:09:46 by cgoldens         ###   ########.fr       */
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
 * @brief Get the path object
 * 
 * @return char* path
 */
char	*get_path(void)
{
	char	*p;

	p = malloc(sizeof(char *) * BUFFER_SIZE);
	if (!p)
		return (NULL);
	getcwd(p, BUFFER_SIZE);
	if (!p)
		return (NULL);
	return (p);
}

/**
 * @brief Get the userhome object
 * 
 * @return char* userhome path
 */
char	*get_userhome(void)
{
	char	*p;
	char	**p_a;
	char	*u_p;

	u_p = malloc(sizeof(char) * 6);
	if (!u_p)
		return (NULL);
	u_p = "/home/";
	p = get_path();
	p_a = ft_split(p, '/');
	if (!p_a)
		return (NULL);
	u_p = ft_strjoin(u_p, p_a[1]);
	if (!u_p)
		return (NULL);
	return (u_p);
}

/**
 * @brief Get the line in env
 * 
 * @param env environment variable
 * @param title name of the variable
 * @return int state if the line are find
 */
int	get_envline(char **env, char *title)
{
	int	i;
	int	id;

	i = 0;
	id = -1;
	title = ft_strjoin(title, "=");
	if (!title)
		return (-1);
	while (env[i])
	{
		if ((!ft_strncmp(env[i], title, ft_strlen(title))))
			id = i;
		i++;
	}
	free(title);
	return (id);
}

/**
 * @brief function to delete the choosen line in env var
 * 
 * @param env environment variable
 * @param nenv new environment variable
 * @param title name of the variable 
 */
void	del_envline(char **env, char **nenv, char *title)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	j = 0;
	line = get_envline(env, title);
	while (env[i])
	{
		if (line != i)
		{
			nenv[j] = ft_strdup(env[i]);
			if (!nenv[j])
			{
				clean_tab(nenv);
				return ;
			}
			j++;
		}
		i++;
	}
	nenv[i] = NULL;
}
