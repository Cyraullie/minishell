/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/04 17:11:52 by lpittet          ###   ########.fr       */
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
	buf = ft_calloc(sizeof(char *) , BUFFER_SIZE);
	if (!buf)
		return ;
	getcwd(buf, BUFFER_SIZE);
	if (!buf)
		return ;
	printf("%s\n", buf);
	free(buf);
}
