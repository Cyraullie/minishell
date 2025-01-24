/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:56:18 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/24 16:40:01 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief get the different redirection file or types
 * 
 * @param cmd an element of the linked list
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
			if (!open_previous_file(cmd))
				return (cmd);
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
 * @brief find the command token
 * 
 * @param cmd a element of the linked list t_command
 * @return cmd arg, with the cmd attribute correctly set
 */
t_command	*get_cmd(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->raw[++i])
	{
		if (!ft_isredir(cmd->raw[i][0]))
		{
			cmd->cmd = cmd->raw[i];
			break ;
		}
		else
			i++;
	}
	return (cmd);
}

/**
 * @brief count the number of arguments that will be used in get_cmd_args
 * 
 * @param cmd a element of the linked list t_command
 * @return the number of argument that need to fit in a table
 */
int	count_arg_number(t_command *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (cmd->raw[++i])
	{
		if (!ft_isredir(cmd->raw[i][0]))
			count++;
		else
			i++;
	}
	return (count);
}

/**
 * @brief create a table of strings that can be used later by execve
 * 
 * @param cmd a element of the linked listb t_command
 * @return the cmd arg, with the table added
 */
t_command	*get_cmd_args(t_command *cmd)
{
	int	count;
	int	i;
	int	j;

	if (!cmd->cmd)
		return (cmd);
	count = count_arg_number(cmd);
	cmd->cmd_tab = ft_calloc(count + 1, sizeof(char *));
	if (!cmd->cmd_tab)
		return (NULL);
	i = -1;
	j = 0;
	while (cmd->raw[++i])
	{
		if (!ft_isredir(cmd->raw[i][0]))
		{
			cmd->cmd_tab[j] = cmd->raw[i];
			j++;
		}
		else
			i++;
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
		*cmd = get_cmd(*cmd);
		*cmd = get_cmd_args(*cmd);
		if (i > 0 && !(*cmd)->heredoc && !(*cmd)->read)
			(*cmd)->pipe_in = 1;
		if ((*cmd)->next && !(*cmd)->write)
			(*cmd)->pipe_out = 1;
		(*cmd) = (*cmd)->next;
		i++;
	}
}
