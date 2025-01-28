/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:01 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/28 12:02:10 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins(t_command *cmd_tmp, char ***env)
{
	if (!ft_strncmp(cmd_tmp->cmd, "echo", 5))
		ft_echo(cmd_tmp->cmd_tab);
	else if (!ft_strncmp(cmd_tmp->cmd, "cd", 3))
		ft_cd(cmd_tmp->cmd_tab, env);
	else if (!ft_strncmp(cmd_tmp->cmd, "pwd", 4))
		ft_pwd(cmd_tmp->cmd_tab);
	else if (!ft_strncmp(cmd_tmp->cmd, "export", 7))
		*env = ft_export(cmd_tmp->cmd_tab, *env);
	else if (!ft_strncmp(cmd_tmp->cmd, "unset", 6))
		*env = ft_unset(cmd_tmp->cmd_tab, *env);
	else if (!ft_strncmp(cmd_tmp->cmd, "env", 4))
		ft_env(cmd_tmp->cmd_tab, *env);
	else if (!ft_strncmp(cmd_tmp->cmd, "exit", 5))
		ft_exit(cmd_tmp->cmd_tab, *env);
}

void	redirection(t_command *cmd_tmp, char ***env)
{
	int	fd;
	int	out_cpy;

	if (cmd_tmp->write)
	{
		out_cpy = dup(STDOUT_FILENO);
		fd = open(cmd_tmp->write, cmd_tmp->write_type, 0755);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	builtins(cmd_tmp, env);
	if (cmd_tmp->write)
		dup2(out_cpy, STDOUT_FILENO);

}

void	handle_pipe(t_command *cmd_tmp, char ***env)
{
	/*int		p[2];
	pid_t	t;

	if (cmd_tmp->next)
	{
		pipe(p);
		t = fork();
	}
	printf("%d_%s\n", t, cmd_tmp->cmd_tab[1]);*/
	redirection(cmd_tmp, env);
}

void	exec_built(t_command **cmd, char ***env)
{
	t_command *cmd_tmp;

	cmd_tmp = *cmd;
	while (cmd_tmp)
	{
		handle_pipe(cmd_tmp, env);
		cmd_tmp = cmd_tmp->next;
	}
}

