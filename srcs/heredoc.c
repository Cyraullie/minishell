/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:04:16 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/12 15:36:21 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	max(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}



void	heredoc(t_command *cmd)
{
	int		fdin;
	char	*line;
	int		len;
	char	*path;
	char	*home;

	home = get_userhome();
	path = ft_strjoin_and_free(home, HEREDOC_FILE);
	if (!access(path, F_OK))
		unlink(path);
	len = ft_strlen(cmd->read);
	fdin = open(path, O_CREAT | O_APPEND | O_WRONLY, 0666);
	free(path);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, cmd->read, max(len, ft_strlen(line) - 1)))
			break ;
		ft_putstr_fd(line, fdin);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fdin);
}
