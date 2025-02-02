/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:10:12 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/02 11:27:35 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*delete_quotes(char *token, char *new_token)
{
	int		i;
	int		j;
	int		in_quotes[2];
	char	quote;

	in_quotes[0] = 0;
	in_quotes[1] = 0;
	i = -1;
	j = 0;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			toggle_quotes(token, i, &in_quotes[0], &in_quotes[1]);
			if (in_quotes[0] || in_quotes[1])
			{
				quote = token[i];
				while (token[++i] != quote)
					new_token[j++] = token[i];
			}
		}
		else
			new_token[j++] = token[i];
	}
	return (new_token);
}

int	quotes_new_len(char *token)
{
	int	i;
	int	old_len;
	int	in_d_quotes;
	int	in_s_quotes;

	old_len = ft_strlen(token);
	in_d_quotes = 0;
	in_s_quotes = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			toggle_quotes(token, i, &in_d_quotes, &in_s_quotes);
		if (in_d_quotes || in_s_quotes)
			return (old_len - 2);
	}
	return (old_len);
}

char	*remove_quotes(char *token)
{
	char	*new_token;
	int		new_len;
	int		old_len;

	new_len = quotes_new_len(token);
	old_len = ft_strlen(token);
	if (new_len == old_len)
		return (token);
	new_token = ft_calloc(new_len + 1, sizeof(char));
	if (!new_token)
		return (NULL);
	delete_quotes(token, new_token);
	free(token);
	return (new_token);
}
