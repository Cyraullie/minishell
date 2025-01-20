/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:32:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/20 15:29:23 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <=  13));
}

void	toggle_quotes(char *c, int i, int *in_d_quotes, int *in_s_quotes)
{
	if (c[i] == '\"' && !*in_s_quotes)
	{
		while (c[++i])
		{
			if (c[i] == '\"' || *in_d_quotes)
			{
				*in_d_quotes = !*in_d_quotes;
				return ;
			}
		}
	}
	if (c[i] == '\'' && !*in_d_quotes)
	{
		while (c[++i])
		{
			if (c[i] == '\'' || *in_s_quotes)
			{
				*in_s_quotes = !*in_s_quotes;
				return ;
			}
				
		}
	}
}

unsigned int	count_cmds(char *s)
{
	int	i;
	int	num_cmds;
	int	in_d_quotes;
	int	in_s_quotes;

	i = 0;
	num_cmds = 1;
	in_d_quotes = 0;
	in_s_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			toggle_quotes(s, i, &in_d_quotes, &in_s_quotes);
		if (i != 0 && s[i] == '|' && !in_d_quotes && !in_s_quotes)
			num_cmds++;
		i++;
	}
	return (num_cmds);
}

void	split_commands(char *s, char **tab, int num_cmds)
{
	int	i;
	int	j;
	int start;
	int	in_d_quotes;
	int	in_s_quotes;

	i = 0;
	j = 0;
	in_d_quotes = 0;
	in_s_quotes = 0;
	while (j < num_cmds)
	{
		start = i;
		while (s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
				toggle_quotes(s, i, &in_d_quotes, &in_s_quotes);
			if (s[i] == '|' && !in_d_quotes && !in_s_quotes)
				break ;
			i++;
		}
		tab[j++] = ft_substr(s, start, i - start);
		while (s[i] == '|' || ft_isspace(s[i]))
			i++;
	}
}
//TODO clean if substr fail

char	**mini_split(char *s, t_command ***cmd)
{
	char			**tab;
	unsigned int	num_cmds;

	num_cmds = count_cmds(s);
	tab = malloc((1 + num_cmds) * sizeof(char *));
	if (!tab)
		return (NULL);
	*cmd = ft_calloc(sizeof(t_command *) , num_cmds + 1);
	if (!cmd)
		return (NULL);
	split_commands(s, tab, num_cmds);
	tab[num_cmds] = NULL;
	free(s);
	return (tab);
}
