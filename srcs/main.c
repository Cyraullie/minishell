/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/13 16:20:10 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief create a modifiable environment variable
 * @param envp , env variable
 * @return NULL on failure, char **env on success
 */
char	**get_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = envp[i];
		i++;
	}
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;

	env = av;     //TODO remove these lines placeholders to be able to compile
	if (ac < 0)
		return (1);
	env = get_env(envp);
	while (1)
	{
		line = readline("minishell> ");
		printf("%s\n", line);
	}
}
