/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 15:57:47 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to display actual location in directory
 * 
 * @param cmd command line array
 */
void	ft_pwd(char **cmd)
{
	char	*buf;

	if (cmd[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	buf = malloc(sizeof(char *) * BUFFER_SIZE);
	if (!buf)
		return ;
	getcwd(buf, BUFFER_SIZE);
	if (!buf)
		return ;
	printf("%s\n", buf);
	free(buf);
}
