/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:18:37 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 13:34:57 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief check if a pipe or redir symbol is need to be separated from
 * 		  alphanumeric character
 * 
 * @param line input strinf
 * @param i index in the line
 * @param in_d_quotes flag to check if inside double quotes
 * @param in_s_quotes flag to check if inside single quotes
 * @return int 1 if need to be separated, 0 otherwise
 */
int	check_sep(char *line, int i, int in_d_quotes, int in_s_quotes)
{
	if ((line[i] == '<' || line[i] == '>') && (line[i - 1] != line[i])
		&& line[i - 1] != ' ' && !in_d_quotes && !in_s_quotes)
		return (1);
	if (ft_isalnum(line[i]) && (line[i -1] == '<' || line[i -1] == '>')
		&& !in_d_quotes && !in_s_quotes)
		return (1);
	return (0);
}

/**
 * @brief count the space to be allocated in the new line
 * 
 * @param line string input
 * @return int the len after adding necessary spaces
 */
int	count_char(char *line)
{
	int	in_d_quotes;
	int	in_s_quotes;
	int	count;
	int	i;

	in_d_quotes = 0;
	in_s_quotes = 0;
	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			toggle_quotes(line, i, &in_d_quotes, &in_s_quotes);
		if (i > 0 && check_sep(line, i, in_d_quotes, in_s_quotes))
			count++;
		i++;
	}
	return (count + i);
}

/**
 * @brief add space to separate pipes and redir characters
 * 		  from alphanumeric characters
 * 
 * @param old_line input line
 * @param new_line line with added spaces
 * @return char* new_line
 */
char	*add_space(char *old_line, char *new_line)
{
	int	in_d_quotes;
	int	in_s_quotes;
	int	i_old;
	int	i_new;

	in_d_quotes = 0;
	in_s_quotes = 0;
	i_old = 0;
	i_new = 0;
	while (old_line[i_old])
	{
		if (old_line[i_old] == '\'' || old_line[i_old] == '\"')
			toggle_quotes(old_line, i_old, &in_d_quotes, &in_s_quotes);
		if (i_old > 0 && check_sep(old_line, i_old, in_d_quotes, in_s_quotes))
		{
			new_line[i_new] = ' ';
			i_new++;
			new_line[i_new] = old_line[i_old];
		}
		else
			new_line[i_new] = old_line[i_old];
		i_new++;
		i_old++;
	}
	return (new_line);
}

/**
 * @brief takes a line and add spaces next to redir character
 * 
 * @param line 
 * @return char* modified line with additional spaces
 */
char	*separate_tokens(char *line)
{
	int		count;
	char	*new_line;

	count = count_char(line);
	new_line = ft_calloc(sizeof(char), count + 1);
	if (!new_line)
		return (NULL);
	new_line = add_space(line, new_line);
	return (new_line);
}
