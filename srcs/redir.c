/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:21:58 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/14 12:07:04 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*setup_redir_read(t_command *cmd, int i, char **env)
{
	int fd;
	
	if (cmd->read)
	{
		if (cmd->heredoc)
		{
			heredoc(cmd, env);
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
