/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:28:07 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 16:28:33 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to update PWD with the new position
 * 
 * @param path new postition
 * @param env array of environment variable
 */
void	update_pwd(char *path, char ***env)
{
	int		line;
	char	*cmd[3];
	char	*pwd;

	pwd = ft_strjoin("PWD=", path);
	free(path);
	cmd[0] = "export";
	cmd[1] = pwd;
	cmd[2] = NULL;
	line = get_envline(*env, "PWD");
	if (line != -1)
		*env = ft_export(cmd, *env);
	free(pwd);
}

/**
 * @brief function to update OLDPWD with the old position
 * 
 * @param path old positon
 * @param env array of environment variable
 */
void	update_oldpwd(char *path, char ***env)
{
	int		line;
	char	*cmd[3];
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", path);
	free(path);
	cmd[0] = "export";
	cmd[1] = pwd;
	cmd[2] = NULL;
	line = get_envline(*env, "OLDPWD");
	if (line != -1)
		*env = ft_export(cmd, *env);
	free(pwd);
}
