/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:05:17 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 16:59:06 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO add in history the .ms_history file
//TODO 

/**
 * @brief function to handle what append with the history
 * 
 * @param line var get in readline
 */
void	handle_history(char *line)
{
	int		fd;
	char	*l_hist;

	if (line && *line)
	{
		add_history(line);
		fd = open(".ms_history", O_CREAT | O_WRONLY | O_APPEND, 0644);
		l_hist = ft_strjoin(line, "\n");
		if (!l_hist)
			return ;
		write(fd, l_hist, ft_strlen(l_hist));
		close(fd);
		free(l_hist);
	}
}

void	start_history(void)
{
	int		fd;
	char	*buf;
	char	**file;
	int		i;

	buf = ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
	if (!buf)
		return ;
	fd = open(".ms_history", O_CREAT | O_RDONLY, 0644);
	read(fd, buf, BUFFER_SIZE);
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
	close(fd);
}
