/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:10:12 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/04 13:41:09 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief get a token (char *) and return a new one without mathing quotes
 * 
 * @param token 
 * @param new_token token without matching quotes
 * @param i index in token
 * @param j index in new_token
 * @return char* the new_token
 */
char	*delete_quotes(char *token, char *new_token, int i, int j)
{
	int		in_quotes[2];
	char	quote;

	in_quotes[0] = 0;
	in_quotes[1] = 0;
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
				in_quotes[0] = 0;
				in_quotes[1] = 0;
			}
			else
				new_token[j++] = token[i];
		}
		else
			new_token[j++] = token[i];
	}
	return (new_token);
}


/**
 * @brief calculate the len of a string after removing quotes
 * 
 * @param token 
 * @return int the len of the token after removing mathching quotes
 */
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

/**
 * @brief takes a sring and returns it wihout quotes that were closed inside
 * 
 * @param token a string
 * @return char* a new string with removed quotes if necessary or the input string if no quotes to remove
 */
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
	delete_quotes(token, new_token, -1, 0);
	free(token);
	return (new_token);
}
