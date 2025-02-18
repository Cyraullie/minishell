/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/18 09:27:49 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief main function
 * 
 * @param ac count of arguments
 * @param av array of arguments
 * @param envp array with the environment variable come from out
 * @return int return if the program finish successfully or with error
 */
int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_command	*cmd;
	char		**env;

	init_minishell(&env, envp);
	while (ac && av[0])
	{
		init_sig();
		cmd = NULL;
		line = readline("minishell> ");
		handle_eof(line, env);
		handle_history(line, env);
		if (!parsing(line, &cmd, &env))
			exec_main(&cmd, &env, 0);
		ft_listdelete(cmd);
	}
	return (0);
}
