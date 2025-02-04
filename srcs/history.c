/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:05:17 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/04 15:54:55 by cgoldens         ###   ########.fr       */
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
	char	*shell_content;

	if (line && *line)
	{
		add_history(line);
		shell_content = get_env_content("SHLVL", env);
		path = ft_strjoin(HISTORY_FILE, shell_content);
		free(shell_content);
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
	char	*shell_content;

	buf = ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	shell_content = get_env_content("SHLVL", env);
	path = ft_strjoin(HISTORY_FILE, shell_content);
	free(shell_content);
	if (!path)
		return (free(buf), NULL);
	fd = open(path, O_CREAT | O_RDONLY, 0644);
	free(path);
	read(fd, buf, BUFFER_SIZE);
	close(fd);
	if (!buf)
		return (free(buf), NULL);
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
