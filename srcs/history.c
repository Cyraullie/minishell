/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:05:17 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 16:24:06 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to handle what append with the history
 * 
 * @param line var get in readline
 * @param env 
 */
void	handle_history(char *line, char **env)
{
	int		fd;
	char	*l_hist;
	char	*path;

	if (line && *line)
	{
		add_history(line);
		path = ft_strjoin(HISTORY_FILE, get_env_content("SHLVL", env));
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
		free(path);
		l_hist = ft_strjoin(line, "\n");
		if (!l_hist)
			return ;
		write(fd, l_hist, ft_strlen(l_hist));
		close(fd);
		free(l_hist);
	}
}

char	*read_start_history(char **env)
{
	int		fd;
	char	*buf;
	char	*path;

	buf = ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	path = ft_strjoin(HISTORY_FILE, get_env_content("SHLVL", env));
	if (!path)
	{
		free(buf);
		return (NULL);
	}
	fd = open(path, O_CREAT | O_RDONLY, 0644);
	free(path);
	read(fd, buf, BUFFER_SIZE);
	close(fd);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

/**
 * @brief function to get all old history in .ms_history
 * 
 */
void	start_history(char **env)
{
	char	**file;
	int		i;
	char	*buf;

	buf = read_start_history(env);
	if (!buf)
		return ;
	file = ft_split(buf, '\n');
	if (!file)
	{
		free(buf);
		return ;
	}
	free(buf);
	i = -1;
	while (file[++i])
		add_history(file[i]);
	clean_tab(file);
}
