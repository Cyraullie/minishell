/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:10 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/17 14:16:46 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

typedef struct s_command
{
	char	*read;
	char	*write;
	char	*cmd;
	char	*flags;
	char	**cmd_tab;
} t_command;

// split_commands.c
char	**mini_split(char *s, t_command **cmd);
int 	ft_isspace(int c);
void	toggle_quotes(char *c, int i, int *in_d_quotes, int *in_s_quotes);

// parsing.c
int		parsing(char *line, t_command **cmd, char **env);

// setup_commands.c
void 	setup_command(char *line, t_command *cmd, char **env);

#endif