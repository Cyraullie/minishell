/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:02:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/20 16:01:58 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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

int parsing(char *line, t_command ***cmd, char **env)
{
	char	*line_next;
	char	**tab;
	int		i;

	line = ft_strtrim_and_free(line, " ");
	if (line[ft_strlen(line) - 1] == '|')
	{
		line_next = readline(">");
		line = ft_strjoin_and_free(line, line_next);
		free(line_next);
		parsing(line, cmd, env);
		return (0);
	}
	tab = mini_split(line, cmd);
	i = 0;
	while (tab[i])
	{
		*cmd[i] = ft_calloc(sizeof(t_command), 1);
		if (!*cmd[i])
			return (0);
		setup_command(tab[i], &(*cmd[i]));
		i++;
	}
	(*cmd[i]) = NULL;
	free_tab(tab);
	return (0);
}
