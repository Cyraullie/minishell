/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:12:51 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/27 16:15:36 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redir_syntax(char *line, int *i)
{
	int	count;

	count = 0;
	while (ft_isredir(line[++(*i)]))
		count++;
	if (count > 1)
	{
		ft_putstr_fd("syntax error near unexpeted token ", STDERR_FILENO);
		ft_putchar_fd(line[*i - 1], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (0);
	}
	while (ft_isspace(line[*i]))
		(*i)++;
	if (*i == (int)ft_strlen(line))
	{
		ft_putstr_fd("syntax error near unexpeted token newline\n", STDERR_FILENO);
		return (0);
	}
	if (ft_isredir(line[*i]) || line[*i] == '|')
	{
		ft_putstr_fd("syntax error near unexpeted token ", STDERR_FILENO);
		ft_putchar_fd(line[*i], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	check_pipe_syntax(char *line, int *i)
{
	char	*str;

	(*i)++;
	if (line[*i] == '|')
	{
		str = "syntax error near unexpected token |\n";
		ft_putstr_fd(str, STDERR_FILENO);
		return (0);
	}
	while (ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == '|')
	{
		str = "syntax error near unexpected token |\n";
		ft_putstr_fd(str, STDERR_FILENO);
		return (0);
	}
	if (*i == (int)ft_strlen(line))
	{
		str = "syntax error near unexpected token newline\n";
		ft_putstr_fd(str, STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	check_syntax(char *line)
{
	int	i;
	int	in_d_quotes;
	int	in_s_quotes;

	if (line[0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token |\n", STDERR_FILENO);
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
