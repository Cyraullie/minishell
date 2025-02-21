/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:31:24 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 11:34:53 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//TODO brief
int	check_solo_dollar(char *str, int in_d_quotes, int in_s_quotes)
{
	if (!str[1])
		return (1);
	if (!in_d_quotes && !in_s_quotes && ft_isspace(str[1]))
		return (1);
	if (in_d_quotes && str[1] == '\"')
		return (1);
	if (in_s_quotes && str[1] == '\'')
		return (1);
	return (0);
}

/**
 * @brief Get the new len object after expansion
 * 
 * @param str 
 * @param env 
 * @param in_d_quotes a marker to know if we are inside double quotes
 * @param in_s_quotes a marker to know if we are inside single quotes
 * @return int the len after expansion
 */
int	get_new_len(char *str, char **env, int dq, int sq)
{
	int		len;
	char	*var_name;
	char	*var_value;
	int		i;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			toggle_quotes(str, i, &dq, &sq);
		if (str[i] == '$' && !sq && !check_solo_dollar(&str[i], dq, sq))
		{
			var_name = get_var_name(str, i + 1);
			if (!var_name)
				return (0);
			var_value = get_env_content(var_name, env);
			len += (int)ft_strlen(var_value) - (int)ft_strlen(var_name);
			free(var_name);
			free(var_value);
		}
		else
			len++;
	}
	return (len);
}

/**
 * @brief get the value corresponding to an env variable 
 * 		  and replace it in the new_token string
 * 
 * @param token a string
 * @param new_token a string (modified from tokne)
 * @param index the index at which we start the expansion after the $ symbol
 * @param env 
 */
void	replace_var(char *token, char *new_token, int *index, char **env)
{
	char	*var_name;
	char	*var_value;
	int		len;

	var_name = get_var_name(token, index[0] + 1);
	if (!var_name)
		return ;
	len = ft_strlen(var_name);
	index[0] += len;
	var_value = get_env_content(var_name, env);
	if (!var_value)
	{
		free(var_name);
		return ;
	}
	len = 0;
	while (var_value[len])
	{
		new_token[index[1]] = var_value[len];
		index[1]++;
		len++;
	}
	free(var_value);
	free(var_name);
}

/**
 * @brief receive a string with one or more env variable and
 * 		  expand them to take their values
 * 
 * @param token 
 * @param env 
 * @param in_d_quotes a marker to know if we are inside double quotes
 * @param in_s_quotes a marker to know if we are inside single quotes
 * @return char* the token input with env variables expanded
 */
char	*expand_var(char *token, char **env, int in_d_quotes, int in_s_quotes)
{
	int		index[2];
	int		len;
	char	*new_token;

	index[0] = -1;
	index[1] = 0;
	len = get_new_len(token, env, 0, 0);
	new_token = ft_calloc(len + 1, sizeof(char));
	if (!new_token)
		return (NULL);
	while (token[++index[0]])
	{
		if (token[index[0]] == '\'' || token[index[0]] == '\"')
			toggle_quotes(token, index[0], &in_d_quotes, &in_s_quotes);
		if (token[index[0]] == '$' && !in_s_quotes
			&& !check_solo_dollar(&token[index[0]], in_d_quotes, in_s_quotes))
			replace_var(token, new_token, index, env);
		else
		{
			new_token[index[1]] = token[index[0]];
			index[1]++;
		}
	}
	return (new_token);
}

/**
 * @brief expand the environnement variables
 * 
 * @param tab the command tab as created in every t_command node
 * @param env 
 * @return char** the updated tab with env variable expanded if needed
 */
char	**expansion(char **tab, char **env)
{
	char	**new_tab;
	int		i;

	i = -1;
	new_tab = ft_calloc(get_tab_size(tab) + 1, sizeof(char *));
	while (tab[++i])
	{
		if (!ft_strncmp(tab[i], "$?", 3))
			new_tab[i] = ft_itoa(get_exitvalue(env));
		else if (ft_strchr(tab[i], '$'))
			new_tab[i] = expand_var(tab[i], env, 0, 0);
		else
			new_tab[i] = ft_strdup(tab[i]);
		new_tab[i] = remove_quotes(new_tab[i]);
	}
	clean_tab(tab);
	return (new_tab);
}
