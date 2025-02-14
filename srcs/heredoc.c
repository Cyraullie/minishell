/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:04:16 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/14 11:57:11 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	max(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}

int	new_len(char *line, char **env)
{
	int 	i;
	int 	len;
	char	*var_name;
	char	*var_value;
	
	len = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			var_name = get_var_name(line, i + 1);
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

char	*expand_heredoc(char *line, char *new_line, char **env)
{
	int index[2];
	
	index[0] = -1;
	index[1] = 0;

	while (line[++index[0]])
	{
		if (line[index[0]] == '$')
			replace_var(line, new_line, index, env);
		else
		{
			new_line[index[1]] =line[index[0]];
			index[1]++;
		}
	}
	return (new_line);
}

char	*heredoc_expansion(char *line, char **env)
{
	char	*new_line;
	int		len;
	
	if (!ft_strchr(line, '$'))
		return (line);
	len = new_len(line, env);
	new_line = ft_calloc(sizeof(char) , len + 1);
	if (!new_line)
		return (NULL);
	new_line = expand_heredoc(line, new_line, env);
	free(line);
	return (new_line);
	
}

void	heredoc(t_command *cmd, char **env)
{
	int		fdin;
	char	*line;
	int		len;
	char	*path;
	char	*home;
	
	home = get_userhome();
	path = ft_strjoin_and_free(home, HEREDOC_FILE);
	if (!access(path, F_OK))
		unlink(path);
	len = ft_strlen(cmd->read);
	fdin = open(path, O_CREAT | O_APPEND | O_WRONLY, 0666);
	free(path);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, cmd->read, max(len, ft_strlen(line) - 1)))
			break ;
		line = heredoc_expansion(line, env);
		ft_putstr_fd(line, fdin);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fdin);
}
