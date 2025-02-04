/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:02:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/29 11:10:25 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief delete all character at the start and end of s1 that are in set
 * 		  and frees s1
 * 
 * @param s1 
 * @param set 
 * @return char* 
 */
char	*ft_strtrim_and_free(char *s1, char *set)
{
	char	*trimmed;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (end == -1)
		return (ft_calloc(1, 1));
	while (ft_strchr(set, s1[start]))
		start++;
	if (start > end)
		return (ft_calloc(1, 1));
	while (ft_strchr(set, s1[end]))
		end--;
	trimmed = ft_substr(s1, start, end - start + 1);
	free(s1);
	return (trimmed);
}

/**
 * @brief join 2 strings and frees the first one
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*join;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(sizeof(char) * len);
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, len);
	free(s1);
	return (join);
}

/**
 * @brief parse the input at each iterations and format it
 * 		  so that it can be executed easily and put every command in a linked list
 * @param line the input written in the prompt
 * @param cmd the address of the first element of a linked list
 * @param env environnement variables table
 * @return int 
 */
int	parsing(char *line, t_command **cmd, char **env)
{
	char		**tab;
	t_command	*head;
	int			i;

	if (!check_syntax(line))
	{
		free(line);
		return (1);
	}
	line = ft_strtrim_and_free(line, " ");
	(void)env;
	tab = mini_split(line);
	i = 0;
	while (tab[i])
	{
		create_list(tab[i], cmd);
		i++;
	}
	head = *cmd;
	assign_token(cmd, env);
	*cmd = head;
	clean_tab(tab);
	return (0);
}
