/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:32:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/13 15:33:28 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_words(char const *s, char c, int *in_s_q, int *in_d_q)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			if (!*in_d_q && !*in_s_q)
				count++;
			while (s[i] && s[i] != c)
			{
				if (s[i] == '\'' && s[i - 1] != '\\')
					*in_s_q = !*in_s_q;
				else if (s[i] == '\"' && s[i - 1] != '\\')
					*in_d_q = !*in_d_q;
				i++;
			}	
		}
	}
	return (count);
}

static	char	*fill_words(char const *s, char c, int *i)
{
	int	len;
	int	in_s_quote;
	int	in_d_quote;

	len = 0;
	in_s_quote = 0;
	in_d_quote = 0;
	while (s[*i])
	{
		if (s[*i] == '\'')
			in_s_quote = !in_s_quote;
		else if (s[*i] == '\"')
			in_d_quote = !in_d_quote;
		if (s[*i] == c && !in_d_quote && ! in_s_quote)
			break ;
		len++;
		*i = *i + 1;
	}
	return (ft_substr(s, *i - len, len));
}

static	char	**ft_words(char const *s, char c, char **tab, size_t num_w)
{
	int		i;
	size_t	iword;

	i = 0;
	iword = 0;
	while (iword < num_w)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\\')
			i++;
		tab[iword] = fill_words(s, c, &i);
		iword++;
	}
	tab[iword] = 0;
	return (tab);
}

static	char	**clean_quote(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if ((tab[i][0] == '\'' || tab[i][0] == '\"') && ft_strlen(tab[i]) > 1)
			tab[i] = ft_strtrim(tab[i], "\'\"");
		i++;
	}
	return (tab);
}

char	**mini_split(char const *s, char c)
{
	char			**tab;
	unsigned int	num_words;
	int				in_s_quote;
	int				in_d_quote;

	if (!s)
		return (0);
	in_d_quote = 0;
	in_s_quote = 0;
	num_words = count_words(s, c, &in_s_quote, &in_d_quote);
	tab = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (tab == NULL)
		return (NULL);
	tab = ft_words(s, c, tab, num_words);
	tab = clean_quote(tab);
	return (tab);
}
