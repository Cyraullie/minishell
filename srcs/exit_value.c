/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:01 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/14 14:14:28 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_exitvalue(char **env)
{
	char	*content;
	int		eval;

	content = get_env_content("?", env);
	eval = ft_atoi(content);
	free(content);
	return (eval);
}

void	update_exitvalue(int eval, char ***env)
{
	char	*line;
	char	*content;
	int		i;

	line = NULL;
	i = get_envline((*env), "?");
	content = ft_itoa(eval);
	line = ft_strjoin("?=", content);
	free(content);
	free((*env)[i]);
	(*env)[i] = ft_strdup(line);
	free(line);
}
