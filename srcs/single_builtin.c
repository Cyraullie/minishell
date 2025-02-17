/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:48:11 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/17 09:24:43 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief a function that setup minishell to execute a single builtin from
 * 		  the list we had to recreate (special exec because of no child process)
 * 
 * @param cmd the linked list of command
 * @param env the environnement variable
 * @return int the status of the executed command
 */
int	exec_single_builtins(t_command **cmd, char ***env)
{
	int	fdin_cpy;
	int	fdout_cpy;
	int	rvalue;

	if (ft_strncmp((*cmd)->cmd, "exit", 5))
	{
		fdin_cpy = dup(STDIN_FILENO);
		fdout_cpy = dup(STDOUT_FILENO);
	}
	rvalue = redir_single_builtin(*cmd, *env);
	if (rvalue)
	{
		dup2(fdin_cpy, STDIN_FILENO);
		dup2(fdout_cpy, STDOUT_FILENO);
		close(fdin_cpy);
		close(fdout_cpy);
		return (rvalue);
	}
	rvalue = exec_builtin(*cmd, env, cmd);
	dup2(fdin_cpy, STDIN_FILENO);
	dup2(fdout_cpy, STDOUT_FILENO);
	close(fdin_cpy);
	close(fdout_cpy);
	return (rvalue);
}

/**
 * @brief execute the correct builtin we created
 * 
 * @param cmd the linked list of commands
 * @param env the environnement variable
 * @return int the status of the executed builtin
 */
int	exec_builtin(t_command *cmd_tmp, char ***env, t_command **cmd)
{
	int	rvalue;

	if (!ft_strncmp(cmd_tmp->cmd, "echo", 5))
		rvalue = ft_echo(cmd_tmp->cmd_tab);
	else if (!ft_strncmp(cmd_tmp->cmd, "cd", 3))
		rvalue = ft_cd(cmd_tmp->cmd_tab, env);
	else if (!ft_strncmp(cmd_tmp->cmd, "pwd", 4))
		rvalue = ft_pwd(cmd_tmp->cmd_tab);
	else if (!ft_strncmp(cmd_tmp->cmd, "export", 7))
		rvalue = ft_export(cmd_tmp->cmd_tab, env);
	else if (!ft_strncmp(cmd_tmp->cmd, "unset", 6))
	{
		*env = ft_unset(cmd_tmp->cmd_tab, *env);
		rvalue = 0;
	}
	else if (!ft_strncmp(cmd_tmp->cmd, "env", 4))
		rvalue = ft_env(cmd_tmp->cmd_tab, *env);
	else if (!ft_strncmp(cmd_tmp->cmd, "exit", 5))
		rvalue = ft_exit(cmd_tmp->cmd_tab, env, cmd);
	return (rvalue);
}
