/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/18 11:43:54 by lpittet          ###   ########.fr       */
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

	(void)cmd;
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
