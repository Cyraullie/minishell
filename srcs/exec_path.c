/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:58:22 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 11:43:49 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief check if the command start with ./ or /
 * 
 * @param path the command to be checked
 * @return int 1 if it starts with ./ or / 0 otherwise
 */
int	check_slash(char *path)
{
	if (!path)
		return (0);
	if (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "/", 1))
		return (1);
	return (0);
}

/**
 * @brief Get the executable path object
 * 
 * @param cmd the actual command in the linked list
 * @param env env variable
 * @param data t_exec data struct
 * @return char* a path that can be executed or NULL if it does not exist
 */
char	*get_executable_path(t_command *cmd, char ***env, t_exec_data *data)
{
	char		*path;
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(struct stat));
	path = find_path(cmd->cmd, env);
	if (path)
		if (!access(path, X_OK))
			return (path);
	if (!access(cmd->cmd, F_OK) && check_slash(cmd->cmd))
	{
		if (lstat(cmd->cmd, &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
				create_error_msg(": Is a directory\n", cmd->cmd, data, NULL);
			if (!access(cmd->cmd, X_OK))
				return (cmd->cmd);
			else
				create_error_msg(": Permission denied\n", cmd->cmd, data, NULL);
		}
		else
			exit (1);
	}
	if (!S_ISDIR(buf.st_mode) && check_slash(cmd->cmd))
		create_error_msg(": No such file or directory\n", cmd->cmd, data, NULL);
	return (NULL);
}

/**
 * @brief iterate through all path in PATH var to find the correct dir
 * 
 * @param cmd the actual command in the linked list
 * @param env env variable
 * @return char* the complete path after adding the correct the correct dir
 */
char	*find_path(char *cmd, char ***env)
{
	char	*path_list;
	char	**src;
	int		i;
	char	*path;

	path_list = search_env(*env);
	if (!path_list)
		return (NULL);
	src = ft_split(path_list, ':');
	i = 0;
	while (src[i])
	{
		path = get_full_path(src[i], cmd);
		if (!access(path, F_OK))
		{
			clean_tab(src);
			return (path);
		}
		free(path);
		i++;
	}
	clean_tab(src);
	return (NULL);
}

/**
 * @brief search for the PATH variable in env
 * 
 * @param env environnement
 * @return char* the PATH var in env
 */
char	*search_env(char **env)
{
	int		i;
	char	*path_list;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_list = env[i];
			return (path_list + 5);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief join the PATH part of the full path with the command 
 * 		  with the input command
 * 
 * @param path the path in PATH
 * @param cmd the input command 
 * @return char* 
 */
char	*get_full_path(char *path, char *cmd)
{
	path = ft_strjoin(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin_and_free(path, cmd);
	if (!path)
		return (NULL);
	return (path);
}
