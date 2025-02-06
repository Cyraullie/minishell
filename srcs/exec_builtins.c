/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:01 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/06 14:58:37 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_exitvalue(char **env)
{
	char	*content;
	int		eval;

	content = get_env_content("?", env);
	eval = ft_atoi(content);
	printf("%d\n", eval);
	return (eval);
}

void	update_exitvalue(int eval, char ***env)
{
	char	*line;
	char	*content;
	int		i;

	line = NULL;
	i = get_envline(*env, "?");
	content = ft_itoa(eval);
	line = ft_strjoin("?=", content);
	free(env[0][i]);
	*env[i] = ft_strdup(line);
	//content = get_env_content("?", env);
	//eval = ft_atoi(content);
	printf("%s line:%d value:%d\n", env[0][i], i, eval);
}

/**
 * @brief function to select the right builtins
 * 
 * @param cmd_tmp command write to call builtins
 * @param env array with the environment variable
 */
void	builtins(t_command *cmd_tmp, char ***env, t_command **cmd)
{
	int	rvalue;

	rvalue = get_exitvalue(*env);
	if (!ft_strncmp(cmd_tmp->cmd, "echo", 5))
	{
		ft_echo(cmd_tmp->cmd_tab);
		rvalue = 0;
	}
	else if (!ft_strncmp(cmd_tmp->cmd, "cd", 3))
		rvalue = ft_cd(cmd_tmp->cmd_tab, env);
	else if (!ft_strncmp(cmd_tmp->cmd, "pwd", 4))
	{
		ft_pwd(cmd_tmp->cmd_tab);
		rvalue = 0;
	}
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
		ft_exit(cmd_tmp->cmd_tab, env, cmd);
	update_exitvalue(rvalue, env);
}


void	handle_redir(t_command *cmd_tmp)
{
	int	fd;

	if (cmd_tmp->write)
	{
		fd = open(cmd_tmp->write, cmd_tmp->write_type, 0755);
		if (fd == -1)
			perror("open");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static	char	*get_full_path(char *path, char *cmd)
{
	path = ft_strjoin(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin(path, cmd);
	if (!path)
		return (NULL);
	return (path);
}


static	char	*search_env(char **env)
{
	int		i;
	char	*path_list;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_list = env[i];
			return (path_list + 5);
		}
		i++;
	}
	ft_putendl_fd("PATH not found", 2);
	return (NULL);
}

char	*find_path(char *cmd, char ***env)
{
	char	*path_list;
	char	**src;
	int		i;
	char	*path;

	path_list = search_env(*env);
	if (!path_list)
		exit(1);
	src = ft_split(path_list, ':');
	i = 0;
	while (src[i])
	{
		path = get_full_path(src[i], cmd);
		if (!access(path, F_OK))
		{
			free(src);
			return (path);
		}
		free(path);
		i++;
	}
	free(src);
	return (NULL);
}

void	exec_bash(t_command *cmd_tmp, char ***env)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (!access(cmd_tmp->cmd, X_OK))
			execve(cmd_tmp->cmd, cmd_tmp->cmd_tab, *env);
		else
		{
			path = find_path(cmd_tmp->cmd, env);
			if (!access(path, X_OK))
				execve(path, cmd_tmp->cmd_tab, *env);
			else
				ft_putstr_fd("command not found\n", 2);
		}
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
}

/**
 * @brief function to handle execution of command
 * 
 * @param cmd commande write in the shell
 * @param env array with the environment variable
 */
void	exec_built(t_command **cmd, char ***env)
{
	t_command	*cmd_tmp;
	int			out_cpy;

	cmd_tmp = *cmd;
	while (cmd_tmp)
	{
		out_cpy = dup(STDOUT_FILENO);
		/*if (cmd_tmp->write)
			handle_redir(cmd_tmp);
		else if (cmd_tmp->pipe_in || cmd_tmp->pipe_out)
			handle_pipe(cmd_tmp, env);
		else
		{*/
			if (is_builtin(cmd_tmp->cmd))
				builtins(cmd_tmp, env, cmd);
			else
				exec_bash(cmd_tmp, env);
		//}
		dup2(out_cpy, STDOUT_FILENO);
		close(out_cpy);

		cmd_tmp = cmd_tmp->next;
	}
}

