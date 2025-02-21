/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:32:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 13:38:21 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief check the string from an index i and toggle the corresponding
 * 		  quotes marker, if need be (i.e. already toggled, or closed later)
 * 
 * @param s string
 * @param i index in the string
 * @param in_d_quotes 
 * @param in_s_quotes 
 */
void	toggle_quotes(char *s, int i, int *in_d_quotes, int *in_s_quotes)
{
	if (s[i] == '\"' && !*in_s_quotes)
	{
		while (s[++i])
		{
			if (s[i] == '\"' || *in_d_quotes)
			{
				*in_d_quotes = !*in_d_quotes;
				return ;
			}
		}
	}
	if (s[i] == '\'' && !*in_d_quotes)
	{
		while (s[++i])
		{
			if (s[i] == '\'' || *in_s_quotes)
			{
				*in_s_quotes = !*in_s_quotes;
				return ;
			}
		}
	}
}

/**
 * @brief count the number of commands in the string 
 * 		   = number of pipes + 1
 * 
 * @param s input string
 * @return unsigned int the number of command  found 
 */
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

/**
 * @brief create a substring of the string containing only one command
 * 
 * @param s string input 
 * @param i index in the string
 * @return char* 
 */
char	*get_substr(char *s, int *i)
{
	int		start;
	int		in_d_quotes;
	int		in_s_quotes;
	char	*result;

	in_d_quotes = 0;
	in_s_quotes = 0;
	start = *i;
	while (s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			toggle_quotes(s, *i, &in_d_quotes, &in_s_quotes);
		if (s[*i] == '|' && !in_d_quotes && !in_s_quotes)
			break ;
		*i = *i + 1;
	}
	result = ft_substr(s, start, *i - start);
	return (result);
}

/**
 * @brief fill the comand table with the corresponding command
 * 
 * @param s string input 
 * @param tab the command table that is filled
 * @param num_cmds the number of commands
 */
void	split_commands(char *s, char **tab, int num_cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < num_cmds)
	{
		tab[j] = get_substr(s, &i);
		if (!tab[j++])
		{
			clean_tab(tab);
			return ;
		}
		while (s[i] == '|' || ft_isspace(s[i]))
			i++;
	}
}

/**
 * @brief takes a string as a parameter and returns a char** based on
 * 		  | character, taking into account quotes
 * 
 * @param s 
 * @return char** 
 */
char	**mini_split(char *s)
{
	char			**tab;
	unsigned int	num_cmds;

	num_cmds = count_cmds(s);
	tab = ft_calloc((1 + num_cmds), sizeof(char *));
	if (!tab)
		return (NULL);
	split_commands(s, tab, num_cmds);
	tab[num_cmds] = NULL;
	free(s);
	return (tab);
}
