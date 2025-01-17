/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:11:23 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/17 17:48:24 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words(char *line, int in_d_quotes, int in_s_quotes)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
		{
			if (!in_d_quotes && !in_s_quotes)
				count++;
			while (line[i] && !ft_isspace(line[i]))
			{
				if (line[i] == '\"' || line[i] == '\'')
					toggle_quotes(line, i, &in_d_quotes, &in_s_quotes);
				i++;
			}
		}
	}
	return (count);
}

char	**fill_words(char *line, int *i)
{
	int 	len;
	int		in_s_quotes;
	int		in_d_quotes;
	char	word;

	len = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			toggle_quotes(line, i, &in_d_quotes, &in_s_quotes);
		if (ft_isspace(line[*i]) && !in_d_quotes && !in_s_quotes)
			break ;
		len++;
		*i = *i + 1;
	}
	word = ft_substr(line, *i - len, len);
	if (!word)
		return (NULL);
	return (word);
}

char	**fill_tab(char *line, char **tab, size_t num_words)
{
	int		i;
	size_t	iword;

	i  = 0;
	iword = 0;
	while (iword < num_words)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		tab[iword] = fill_words(line, &i);
	}
}

char	**split_quotes(char *line)
{
	char	**tab;
	int		num_words;

	if (!line)
		return (NULL);
	num_words = count_words(line, 0, 0);
	tab = malloc(sizeof(char *) * (num_words + 1));
	if (!tab)
		return (NULL);
	tab = fill_tab(line, tab, num_words);
}

void	setup_command(char *line, t_command *cmd, char *env)
{
	char	**words_tab;

	words_tab = env;
	words_tab = split_quotes(line);
}