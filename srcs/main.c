/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/17 16:23:09 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*line;
	//t_command	cmd;

	init_sig();
	while (1)
	{
		line = readline("minishell> ");
		handle_eof(line);
		if (line && *line)
			add_history(line);
		//parsing(line, &cmd);
		free(line);
	}
}
