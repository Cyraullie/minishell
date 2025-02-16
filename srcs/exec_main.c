/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:35 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/15 16:57:17 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief create a child process and execute the command given as argument
 * 
 * @param cmd a element of the list of command
 * @param env the environnement variable
 * @return int the status of the executed command
 */
/*int	exec_pipe(t_command *cmd, char ***env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exec_redir(cmd, pipefd, *env);
		execute(cmd, env);
	}
	wait_pid(pid, &status);
	if (cmd->next)
		if (cmd->next->pipe_in)
			dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	return (status);
}*/

/**
 * @brief loop over every command in the list to execute them 
 * 
 * @param cmd the linked list of command
 * @param env the environnement variable
 * @return int the status of the last executed command
 */
/*int	standard_exec(t_command **cmd, char ***env)
{
	t_command	*cmd_tmp;
	int			status;

	cmd_tmp = *cmd;
	while (cmd_tmp)
	{
		status = exec_pipe(cmd_tmp, env);
		cmd_tmp = cmd_tmp->next;
	}
	return (status);
}*/

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
		return (rvalue);
	rvalue = exec_builtin(*cmd, env, cmd);
	dup2(fdin_cpy, STDIN_FILENO);
	dup2(fdout_cpy, STDOUT_FILENO);
	close(fdin_cpy);
	close(fdout_cpy);
	return (rvalue);
}

/**
 * @brief chooses if we use the standard way of doing the builtins with a child
 * 		  process for every command or if we just stay in the same process
 * 		  (when there is only one command we needed to recreate)
 * 
 * @param cmd the linked list of commands
 * @param env 
 */
/*void	exec_main(t_command **cmd, char ***env, int status)
{
	pid_t	pid;

	if (!(*cmd)->cmd)
		return ;
	if (!(*cmd)->next && is_builtin((*cmd)->cmd))
	{
		status = exec_single_builtins(cmd, env);
		update_exitvalue(status, env);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			status = standard_exec(cmd, env);
			ft_listdelete(*cmd);
			clean_tab(*env);
			exit(WEXITSTATUS(status));
		}
		else
			wait_pid(pid, &status);
		update_exitvalue(WEXITSTATUS(status), env);
	}
}*/

static int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	setup_input_redirection(t_command *cmd, char **env)
{
	int	fd;

	if (cmd->read)
	{
		if (cmd->heredoc)
			fd = heredoc_redir(cmd, env);
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

static void	setup_output_redirection(t_command *cmd)
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

static void	setup_child_pipes(int **pipes, int i, int cmd_count, t_command *cmd)
{
	if (i < cmd_count - 1 && cmd->pipe_out)
		dup2(pipes[i][1], STDOUT_FILENO);
	if (i > 0 && cmd->pipe_in)
		dup2(pipes[i - 1][0], STDIN_FILENO);
}

static void	close_child_pipes(int **pipes, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	no_command_exit(t_exec_data *data, int **pipes)
{
	ft_listdelete(data->head);
	clean_tab(*data->env);
	close_pipes(pipes, data->cmd_count);
	free(data->pids);
	exit (0);
}

static int	handle_child_process(t_command *cmd, int **pipes, int i,
	t_exec_data *data)
{
	setup_child_pipes(pipes, i, data->cmd_count, cmd);
	close_child_pipes(pipes, data->cmd_count);
	setup_input_redirection(cmd, *(data->env));
	setup_output_redirection(cmd);
	if (!cmd->cmd)
		no_command_exit(data, pipes);
	execute(cmd, data->env);
	return (1);
}


static t_command	*get_cmd_at_index(t_command *start, int target_index)
{
	t_command	*current;
	int			i;

	current = start;
	i = 0;
	while (i < target_index && current)
	{
		current = current->next;
		i++;
	}
	return (current);
}

static void	init_exec_data(t_exec_data *data, t_command *cmd)
{
	data->cmd_count = 0;
	data->cmd_tmp = cmd;
	data->head = cmd;
	while (data->cmd_tmp)
	{
		data->cmd_count++;
		data->cmd_tmp = data->cmd_tmp->next;
	}
	data->pipes = create_pipes(data->cmd_count);
	data->pids = ft_calloc(sizeof(pid_t), data->cmd_count);
}

static int	wait_for_processes(pid_t *pids, int cmd_count)
{
	int	i;
	int	status[100];

	i = cmd_count - 1;
	while (i >= 0)
	{
		wait_pid(pids[i], &status[i]);
		i--;
	}
	free(pids);
	return (status[cmd_count - 1]);
}

static int	execute_commands(t_exec_data *data, t_command *first_cmd)
{
	int			i;
	t_command	*current_cmd;

	i = data->cmd_count - 1;
	while (i >= 0)
	{
		current_cmd = get_cmd_at_index(first_cmd, i);
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (1);
		if (data->pids[i] == 0)
			handle_child_process(current_cmd, data->pipes, i, data);
		i--;
	}
	if (data->pipes)
		close_pipes(data->pipes, data->cmd_count);
	return (0);
}

int	exec_command_chain(t_command **cmd, char ***env)
{
	t_exec_data	data;
	int			status;

	data.env = env;
	init_exec_data(&data, *cmd);
	if (!data.pids)
	{
		if (data.pipes)
			close_pipes(data.pipes, data.cmd_count);
		return (1);
	}
	if (execute_commands(&data, *cmd))
	{
		free(data.pids);
		return (1);
	}
	status = wait_for_processes(data.pids, data.cmd_count);
	return (status);
}

void	exec_main(t_command **cmd, char ***env, int status)
{
	pid_t	pid;

	if (!(*cmd)->next && is_builtin((*cmd)->cmd))
	{
		status = exec_single_builtins(cmd, env);
		update_exitvalue(status, env);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			status = exec_command_chain(cmd, env);
			ft_listdelete(*cmd);
			clean_tab(*env);
			exit(WEXITSTATUS(status));
		}
		else
			wait_pid(pid, &status);
		update_exitvalue(WEXITSTATUS(status), env);
	}
}