/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:21:58 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/17 14:46:29 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*setup_redir_read(t_command *cmd, int i, char **env)
{
	int	fd;

	if (cmd->read)
	{
		if (cmd->heredoc)
		{
			is_child(1);
			fd = heredoc_redir(cmd, env);
			is_child(0);
			cmd->heredoc = 0;
			if (fd != -1)
				close (fd);
		}
		else
		{
			fd = open(cmd->read, O_RDONLY);
			if (fd == -1)
				return (cmd);
			close(fd);
		}
	}
	if (!ft_strncmp(cmd->raw[i], "<<", 3))
		cmd->heredoc = 1;
	cmd->read = cmd->raw[i + 1];
	return (cmd);
}

int	heredoc_redir(t_command *cmd, char **env)
{
	int		heredocfd[2];
	char	*line;
	int		len;

	pipe(heredocfd);
	g_heredoc_interrupted = 0;
	setup_signals_heredoc();
	len = ft_strlen(cmd->read);
	line = readline("> ");
	while (line && !g_heredoc_interrupted)
	{
		if (!ft_strncmp(line, cmd->read, max(len, ft_strlen(line) - 1)))
			break ;
		line = heredoc_expansion(line, env);
		ft_putendl_fd(line, heredocfd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(heredocfd[1]);
	if (g_heredoc_interrupted)
		return (close(heredocfd[0]), -1);
	return (heredocfd[0]);
}

int	redir_singleout_builtin(t_command *cmd)
{
	int	fd;

	fd = open(cmd->write, cmd->write_type, 0755);
	if (fd == -1)
		return (perror(cmd->write), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/**
 * @brief setup the correct redirection in case of a single builtin
 * 
 * @param cmd 
 * @return int 0 on succes, 126 on failure (UNIX permission denied)
 */
int	redir_single_builtin(t_command *cmd, char **env)
{
	int	fd;

	if (cmd->read)
	{
		if (cmd->heredoc)
		{
			fd = heredoc_redir(cmd, env);
			if (fd == -1)
				return (1);
		}
		else
			fd = open(cmd->read, O_RDONLY);
		if (fd == -1)
			return (perror(cmd->read), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->write)
		if (redir_singleout_builtin(cmd))
			return (1);
	return (0);
}

void	setup_input_redirection(t_command *cmd, char **env, t_exec_data *data)
{
	int	fd;

	if (cmd->read)
	{
		if (cmd->heredoc)
		{
			fd = heredoc_redir(cmd, env);
			if (fd == -1)
				interrupt_exit(data);
		}
		else
			fd = open(cmd->read, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->read);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	setup_output_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->write)
	{
		fd = open(cmd->write, cmd->write_type, 0644);
		if (fd == -1)
		{
			perror(cmd->write);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
