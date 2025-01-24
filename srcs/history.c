/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:05:17 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 16:42:24 by cgoldens         ###   ########.fr       */
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
	int	fd;

	if (line && *line)
	{
		add_history(line);
		fd = open(".ms_history", O_CREAT | O_WRONLY | O_APPEND, 0644);
		line = ft_strjoin(line, "\n");
		write(fd, line, ft_strlen(line));
		close(fd);
	}
}

void	start_history(void)
{
	int		fd;
	char	*buf;
	char	**file;
	int		i;

	buf = malloc(sizeof(char *) * BUFFER_SIZE + 1);
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
