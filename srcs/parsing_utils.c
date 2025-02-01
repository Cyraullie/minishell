/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:51:33 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/01 14:25:18 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief tries to open the files when multiples redirection in a single command
 * 
 * @param cmd a element of the linked list t_command
 * @return int 0 on failure, 1 on success
 */
int	open_previous_file(t_command *cmd)
{
	if (!cmd->write || !cmd->write_type)
		return (1);
	if (open(cmd->write, cmd->write_type, 755) == -1)
	{
		cmd->run = 0;
		perror(cmd->write);
		return (0);
	}
	return (1);
}
//TODO add heredoc to this

int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int	ft_isredir(int c)
{
	return (c == '<' || c == '>');
}

/**
 * @brief Get the number of elements in a table
 * 
 * @param tab 
 * @return int, the number of elements in the table
 */
int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}
