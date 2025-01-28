/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:12:51 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/28 11:52:45 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief print the error
 * 
 * @param end the specified character that cause de syntax error
 */
void	print_syntax_error(char end)
{
	ft_putstr_fd("syntax error near unexpeted token ", STDERR_FILENO);
	if (end == '|')
		ft_putstr_fd("`|\'", STDERR_FILENO);
	if (end == '>')
		ft_putstr_fd("`>\'", STDERR_FILENO);
	if (end == '<')
		ft_putstr_fd("`<\'", STDERR_FILENO);
	if (end == 'n')
		ft_putstr_fd("`newline\'", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

/**
 * @brief check the synax for every redir 
 * 
 * @param line the input on minishell prompt
 * @param i the index in the line
 * @return int 0 if syntax errror, 1 otherwise
 */
int	check_redir_syntax(char *line, int *i)
{
	int	count;

	count = 0;
	if (ft_isredir(line[*i + 1]) && line[*i] != line [*i + 1])
		return (print_syntax_error(line[*i + 1]), 0);
	while (ft_isredir(line[++(*i)]))
		count++;
	if (count > 1)
	{
		print_syntax_error(line[*i - 1]);
		return (0);
	}
	while (ft_isspace(line[*i]))
		(*i)++;
	if (*i == (int)ft_strlen(line))
	{
		print_syntax_error('n');
		return (0);
	}
	if (ft_isredir(line[*i]) || line[*i] == '|')
	{
		print_syntax_error(line[*i]);
		return (0);
	}
	return (1);
}

/**
 * @brief check the syntax for every pipe character
 * 
 * @param line the input on minishell prompt
 * @param i the index in the line
 * @return int 0 if syntax errror, 1 otherwise
 */
int	check_pipe_syntax(char *line, int *i)
{
	(*i)++;
	if (line[*i] == '|')
	{
		print_syntax_error('|');
		return (0);
	}
	while (ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == '|')
	{
		print_syntax_error('|');
		return (0);
	}
	if (*i == (int)ft_strlen(line))
	{
		print_syntax_error('|');
		return (0);
	}
	return (1);
}

/**
 * @brief check for all the syntax that are not valid
 * 
 * @param line the input on minishell prompt
 * @return int 0 if syntax error detected, 1 otherwise
 */
int	check_syntax(char *line)
{
	int	i;
	int	in_d_quotes;
	int	in_s_quotes;

	if (line[0] == '|')
	{
		print_syntax_error('|');
		return (0);
	}
	in_d_quotes = 0;
	in_s_quotes = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			toggle_quotes(line, i, &in_d_quotes, &in_s_quotes);
		if (ft_isredir(line[i]) && !in_d_quotes && !in_s_quotes)
			if (!check_redir_syntax(line, &i))
				return (0);
		if (line[i] == '|' && !in_d_quotes && !in_s_quotes)
			if (!check_pipe_syntax(line, &i))
				return (0);
	}
	return (1);
}
