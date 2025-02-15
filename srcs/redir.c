/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:21:58 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/15 11:19:58 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*setup_redir_read(t_command *cmd, int i, char **env)
{
	int	fd;

	if (cmd->read)
	{
		if (cmd->heredoc)
		{
			is_child(1);
			heredoc(cmd, env);
			is_child(0);
			cmd->heredoc = 0;
		}
		else
		{
			fd = open(cmd->read, O_RDONLY);
			if (fd == -1)
				return (cmd);
			close(fd);
		}
	}
	if (!ft_strncmp(cmd->raw[i], "<<", 3))
		cmd->heredoc = 1;
	cmd->read = cmd->raw[i + 1];
	return (cmd);
}

int	heredoc_redir(t_command *cmd, char **env)
{
	int		heredocfd[2];
	char	*line;
	int		len;

	is_child(1);
	len = ft_strlen(cmd->read);
	pipe(heredocfd);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, cmd->read, max(len, ft_strlen(line) - 1)))
			break ;
		line = heredoc_expansion(line, env);
		ft_putstr_fd(line, heredocfd[1]);
		free(line);
		line = get_next_line(0);
	}
	is_child(0);
	free(line);
	close(heredocfd[1]);
	return (heredocfd[0]);
}

int setup_redir_in(t_command *cmd, char **env)
{
	int	fdin;
	
	if (cmd->heredoc)
		fdin = heredoc_redir(cmd, env);
	else
		fdin = open(cmd->read, O_RDONLY);
	if (fdin == -1)
	{
		perror(cmd->read);
		exit(1);	
	}
	return (fdin);
}
