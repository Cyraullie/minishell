/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:31:24 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/10 15:50:08 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Get the variable name  after the $ symbol
 * 
 * @param str 
 * @param i the index where we start looking for the var name in str
 * @return char* the env variable name
 */
char	*get_var_name(char *str, int i)
{
	int		len;
	char	*var_name;

	len = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	var_name = ft_substr(str, i - len, len);
	if (!var_name)
		return (NULL);
	return (var_name);
}

/**
 * @brief Get the new len object after expansion
 * 
 * @param str 
 * @param env 
 * @param in_d_quotes a marker to know if where we are in a string is inside double quotes
 * @param in_s_quotes a marker to know if where we are in a string is inside single quotes
 * @return int the len after expansion
 */
int	get_new_len(char *str, char **env, int in_d_quotes, int in_s_quotes)
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
			toggle_quotes(str, i, &in_d_quotes, &in_s_quotes);
		if (str[i] == '$' && !in_s_quotes)
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
 * @brief get the value corresponding to an env variable and replace it in the new_token string
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
		return ;
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
 * @brief receive a string with one or more env variable and expand them to take their values
 * 
 * @param token 
 * @param env 
 * @param in_d_quotes a marker to know if where we are in a string is inside double quotes
 * @param in_s_quotes a marker to know if where we are in a string is inside single quotes
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
		if (token[index[0]] == '$' && !in_s_quotes)
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
//TODO make place and deal with $?