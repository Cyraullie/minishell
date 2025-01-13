/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:02:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/13 15:38:49 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parsing(char *line, t_command *cmd)
{
	char **tab;

	tab = mini_split(line, ' ');
	
	return (1);
}