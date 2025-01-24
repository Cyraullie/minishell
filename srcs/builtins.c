/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:30:34 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 14:56:32 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to write a text and handle -n option
 * 
 * @param cmd get command line array
 */
void	ft_echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	if (cmd[i])
	{
		n = find_valid_flag(cmd[i], 'n');
		while (cmd[i] && find_valid_flag(cmd[i], 'n'))
			i++;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
		if (!n)
			printf("\n");
	}
	else
		printf("\n");
}

/**
 * @brief function to exit the program
 * 
 * @param cmd get command line array
 * @param env get environment var
 * @return int return error state
 */
int	ft_exit(char **cmd, char **env)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (cmd[1][i] != '\0')
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			printf("exit: %s: numeric argument required\n", cmd[1]);
			exit(2);
		}
		i++;
	}
	if (cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd[1])
	{
		clean_tab(env);
		exit(ft_atoi(cmd[1]));
	}
	exit(0);
}

/**
 * @brief function to display env data
 * 
 * @param cmd get command line array
 * @param env get env data
 */
void	ft_env(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return ;
	}
	while (env[i])
		printf("%s\n", env[i++]);
}

/**
 * @brief function to display actual location in directory
 * 
 * @param cmd command line array
 */
void	ft_pwd(char **cmd)
{
	char	*buf;

	if (cmd[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	buf = malloc(sizeof(char *) * BUFFER_SIZE);
	if (!buf)
		return ;
	getcwd(buf, BUFFER_SIZE);
	if (!buf)
		return ;
	printf("%s\n", buf);
	free(buf);
}

/**
 * @brief function to move in different directory
 * 
 * @param cmd command line array
 */
void	ft_cd(char **cmd, char ***env)
{
	char	*uh;

	uh = get_userhome();
	if (cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (cmd[1] && !ft_strncmp(cmd[1], "~/", 2))
	{
		cmd[1] = ft_strjoin(uh, ft_strchr(cmd[1], '/'));
		if (!cmd[1])
			return ;
	}
	ft_chdir(cmd, env);
}
