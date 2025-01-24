/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:12:29 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 11:57:15 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param cmd 
 * @param env 
 */
void	ft_chdir(char **cmd, char ***env)
{
	(void)env;
	if (cmd[1] && ft_strncmp(cmd[1], "~", 1))
	{
		if (!access(cmd[1], X_OK))
		{
			update_oldpwd(get_path(), env);
			chdir(cmd[1]);
			update_pwd(get_path(), env);
		}
		else if (access(cmd[1], F_OK))
			perror(cmd[1]);
		else
			perror(cmd[1]);
		return ;
	}
	update_oldpwd(get_path(), env);
	chdir(get_userhome());
	update_pwd(get_path(), env);
}

void	update_pwd(char *path, char ***env)
{
	int		line;
	char	*cmd[3];
	char	*pwd;

	pwd = ft_strjoin("PWD=", path);
	cmd[0] = "export";
	cmd[1] = pwd;
	cmd[2] = NULL;
	line = get_envline(*env, "PWD");
	if (line != -1)
		*env = ft_export(cmd, *env);
	free(pwd);
}


void	update_oldpwd(char *path , char ***env)
{
	int		line;
	char	*cmd[3];
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", path);
	cmd[0] = "export";
	cmd[1] = pwd;
	cmd[2] = NULL;
	line = get_envline(*env, "OLDPWD");
	if (line != -1)
		*env = ft_export(cmd, *env);
	free(pwd);
}
