/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/17 14:50:16 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <stdlib.h>


int	main(void);

/**
 * @brief 
 * 
 * @param sig 
 */
void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		return ;
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}

int	main(void)
{
	char		*line;
	//t_command	cmd;


	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, handle_sig);
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (line && *line)
			add_history(line);


		//parsing(line, &cmd);
	}
}
