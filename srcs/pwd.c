/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/06 15:21:44 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to display actual location in directory
 * 
 * @param cmd command line array
 * @return char** the state of the actual environment variable
 */
int	ft_pwd(char **cmd)
{
	char	*buf;

	if (cmd[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	buf = ft_calloc(sizeof(char *), BUFFER_SIZE);
	if (!buf)
		return (1);
	getcwd(buf, BUFFER_SIZE);
	if (!buf)
		return (1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
