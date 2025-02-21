/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:21:58 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/21 13:38:44 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief open previous read redirection, updates it if it succeeds does not
 * 		  update if open fails
 * 
 * @param cmd node in t_command linked list
 * @param i index in cmd->raw where redir szmbol was found
 * @param env environnement variable
 * @return t_command* 
 */
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

/**
 * @brief setup_redir_for single builtin
 * 
 * @param cmd the node in t_command linked list
 * @return int 1 on failure, 0 on succes
 */
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

/**
 * @brief Set the up input redirection heredoc or file
 * 
 * @param cmd node in t_command linked list
 * @param env environnement variable
 * @param data t_exec_data struct
 */
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
		{
			if (access(cmd->read, F_OK))
				create_error_msg(": No such file or directory\n", cmd->read,
					data, NULL);
			fd = open(cmd->read, O_RDONLY);
			if (fd == -1)
				create_error_msg(": Permission denied\n",
					cmd->read, data, NULL);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

/**
 * @brief Set the up output redirection in each command
 * 
 * @param cmd actual node in the lisr
 * @param data t_exec_data
 */
void	setup_output_redirection(t_command *cmd, t_exec_data *data)
{
	int	fd;

	if (cmd->write)
	{
		fd = open(cmd->write, cmd->write_type, 0644);
		if (fd == -1)
			create_error_msg(": Permission denied\n", cmd->write, data, NULL);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
