/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/13 15:35:11 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	char	*cmd;
	char	*flags;
	char	**cmd_tab;
} t_command;

// parsing_utils.c
char	**mini_split(char const *s, char c);

// parsing.c
int		parsing(char *line, t_command *cmd);

#endif