/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:56:18 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/22 16:16:58 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief get the different redirection file or types
 * 
 * @param cmd an element of the chainde list
 * @return t_command* the cmd param modified
 */
t_command	*get_redir(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->raw[++i])
	{
		if (!ft_strncmp(cmd->raw[i], "<", 2)
			|| !ft_strncmp(cmd->raw[i], "<<", 3))
		{
			if (!ft_strncmp(cmd->raw[i], "<<", 3))
				cmd->heredoc = 1;
			cmd->read = cmd->raw[i + 1];
		}
		if (!ft_strncmp(cmd->raw[i], ">", 2)
			|| !ft_strncmp(cmd->raw[i], ">>", 3))
		{
			cmd->write = cmd->raw[i + 1];
			if (!ft_strncmp(cmd->raw[i], ">>", 3))
				cmd->write_type = O_APPEND | O_CREAT | O_WRONLY;
			else
				cmd->write_type = O_TRUNC | O_CREAT | O_WRONLY;
		}
	}
	return (cmd);
}

/**
 * @brief assign every token to it's function in each node
 
 * 
 * @param cmd address of the first element of the list
 */
void	assign_token(t_command **cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		*cmd = get_redir(*cmd);
		if (i > 0 && !(*cmd)->heredoc && !(*cmd)->read)
			(*cmd)->pipe_in = 1;
		if ((*cmd)->next && !(*cmd)->write)
			(*cmd)->pipe_out = 1;
		(*cmd) = (*cmd)->next;
		i++;
	}
}
