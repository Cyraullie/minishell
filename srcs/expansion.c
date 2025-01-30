/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:31:24 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/29 15:04:10 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_getenv(char *var_name, char **env)
{
	int ienv;
	int	i;

	ienv = get_envline(env, var_name);
	if (ienv == -1)
		return NULL;
	i = 0;
	while (env[ienv][i] != '=')
		i++;
	return (ft_substr(env[ienv], i + 1, ft_strlen(env[ienv])));
}

char	*get_var_name(char *str, int i)
{
	int		len;

	while (str[i] && !ft_isspace(str[i]))
	{
		i++;
		len++;
	}
	return (ft_substr(str, i - len, len));
}

int	get_new_len(char *str, char **env)
{
	int		len;
	char	*var_name;
	char	*var_value;

	len = 0;
	while (str[len] != '$')
		len++;
	var_name = get_var_name(str, len + 1);
	if (!var_name)
		return (0);
	while (str[len])
		len++;
	var_value = my_getenv(var_name, env);
	if (!var_value)
		return (len - 1  -ft_strlen(var_name));
	len = len - 1 - ft_strlen(var_name) + ft_strlen(var_value);
	free(var_value);
	return (len);
}

void	replace_var(char **token, int *i, int *j, char **env)
{
	char	*var_name;
	char	*var_value;
	int		len;

	var_name = get_var_name(*token, *i);
	if (!var_name)
		return ;
	len = ft_strlen(var_name);
	var_value = my_getenv(var_name, env);
	if (!var_value)
	{
		*j += len;
		return ;
	}
	len = 0;
	while (var_value[len])
	{
		*token[*i] = var_value[len];
		(*i)++;
		len++;
	}
}

char	*expand_env_var(char *token, char **env)
{
	int		i;
	int		j;
	char	*new_token;
	int		len;
	int		in_d_quotes;
	int		in_s_quotes;

	i = 0;
	j = 0;
	in_d_quotes = 0;
	in_s_quotes = 0;
	len = get_new_len(token, env);
	new_token = ft_calloc(len + 1, sizeof(char));
	while (token[j])
	{
		while (token[j] != '$')
		{
			if (token[j] == '\'' || token[j] == '\"')
				toggle_quotes(token, i, &in_d_quotes, &in_s_quotes);
			new_token[i] = token[j];
			i++;
			j++;
		}
		if (token[j] == '$' && !in_s_quotes)
			replace_var(&token, &i, &j, env);
		i++;
	}
	free(token);
	return (new_token);
}

//TO Move to utils
int get_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**expansion(char **tab, char **env)
{
	char	**new_tab;
	int		i;
	
	i = -1;
	new_tab = ft_calloc(get_tab_size(tab) + 1, sizeof(char *));
	while (tab[++i])
	{
		if (ft_strchr(tab[i], '$'))
		{
			new_tab[i] = expand_env_var(tab[i], env);
			while (ft_strchr(new_tab[i], '$'))
				new_tab[i] = expand_env_var(new_tab[i], env);
		}
		else
			new_tab[i] = ft_strdup(tab[i]);
		//TODO remove quotes
	}
	clean_tab(tab);
	return (new_tab);
}
