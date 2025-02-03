/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:01 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 17:24:32 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to select the right builtins
 * 
 * @param cmd_tmp command write to call builtins
 * @param env array with the environment variable
 */
void	builtins(t_command *cmd_tmp, char ***env)
{
	if (cmd_tmp->cmd)
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
}
/*
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

void	exec(t_command *cmd_tmp, char ***env)
{
	char	*path;

	path = find_path(cmd_tmp->cmd, env);
	execve(path, cmd_tmp->cmd_tab, *env);
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

void	handle_pipe(t_command *cmd_tmp, char ***env)
{
	int		pipefd[2];
	pid_t	pid;

	if (cmd_tmp->next)
		pipe(pipefd);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) // Processus enfant
	{
		if (cmd_tmp->pipe_out)
		{
			close(pipefd[0]); // Fermer la lecture du pipe
			dup2(pipefd[1], STDOUT_FILENO); // Rediriger stdout vers le pipe
			close(pipefd[1]);
		}
		if (is_builtin(cmd_tmp->cmd))
		{
			builtins(cmd_tmp, env); // Exécuter le builtin
			exit(EXIT_SUCCESS); // Sortir uniquement du processus enfant
		}
		else
		{
			exec(cmd_tmp, env); // Exécuter une commande externe
			exit(EXIT_FAILURE); // Si exec échoue, quitter l'enfant
		}
	}
	else // Processus parent
	{
		if (cmd_tmp->next)
		{
			close(pipefd[1]); // Fermer l'écriture du pipe
			dup2(pipefd[0], STDIN_FILENO); // Lire à partir du pipe
			close(pipefd[0]);
		}
		waitpid(pid, NULL, 0); // Attendre que l'enfant termine
	}
}

*/

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
		/*if (cmd_tmp->write) // Redirection
			handle_redir(cmd_tmp);
		else if (cmd_tmp->pipe_in || cmd_tmp->pipe_out)
			handle_pipe(cmd_tmp, env);
		else*/
			builtins(cmd_tmp, env);

		dup2(out_cpy, STDOUT_FILENO);
		close(out_cpy);

		cmd_tmp = cmd_tmp->next; // On passe à la commande suivante
	}
}

