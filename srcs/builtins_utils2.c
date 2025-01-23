/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:05:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/23 11:58:33 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to add a line in env var
 * 
 * @param env environment variable
 * @param nenv new environment variable
 * @param title name of the variable 
 */
void	add_envline(char **env, char **nenv, char *title, char **name)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != get_envline(env, name[0]))
			dup_env(env, nenv, i, j++);
		else
		{
			nenv[j] = ft_strdup(title);
			check_tabenv(nenv, j++);
		}
		i++;
	}
	if (get_envline(env, name[0]) == -1)
	{
		nenv[j] = ft_strdup(title);
		check_tabenv(nenv, j++);
	}
	nenv[j] = NULL;
	clean_env(name);
}

/**
 * @brief function to duplicate the original env
 * 
 * @param env original environment variable
 * @param nenv new environment variable
 * @param i index for env
 * @param j index for nenv
 */
void	dup_env(char **env, char **nenv, int i, int j)
{
	nenv[j] = ft_strdup(env[i]);
	check_tabenv(nenv, j);
}

/**
 * @brief Create a nenv object for export
 * 
 * @param env environment variable
 * @param name name of the variable 
 * @return char** return new env
 */
char	**create_nenv(char **env, char **name)
{
	int		i;
	char	**nenv;

	i = 0;
	while (env[i])
		i++;
	if (get_envline(env, name[0]) == -1)
		nenv = ft_calloc(sizeof(char *), i + 2);
	else
		nenv = ft_calloc(sizeof(char *), i + 1);
	return (nenv);
}

/**
 * @brief check if the name of the env contain special char or digit
 * 
 * @param n name of the env var
 * @return int return state 0 if contain forbiden char and 1 if it's ok
 */
int	check_normenv(char *n)
{
	int			i;
	int			j;
	const char	*sc = "!@#-$\%^&* (){}[]<>?/~`|\\.,:;\"";

	i = 0;
	if (ft_isdigit(n[i]))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		return (0);
	}
	while (n[i])
	{
		j = 0;
		while (sc[j])
		{
			if (n[i] == sc[j])
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

//TODO faire un tri a -> z pour les titres des variables
//TODO mettre le texte apres le = entre guillment (dexlare -x bla="bla")
/**
 * @brief 
 * 
 * @param env 
 */
void	write_env(char **env)
{
	int		i;
	int		*tab;
	//char	**split;

	i = 0;
	while (env[i])
		i++;
	tab = ft_calloc(sizeof(int *), i + 1);
	if (!tab)
		return ;
	sort_env(env, tab);
	/*i = -1;
	while (tab[++i] != -1)
	{
		split = ft_split(env[tab[i]], '=');
		if (!split)
			return ;
		printf("declare -x %s=\"%s\"\n", split[0], \
			ft_strchr(env[tab[i]], '=') + 1);
		free(split);
	}*/
}
void	sort_by_name(int *tab, char **name, int size)
{
	int		*t;
	char	*tn;
	int		o;
	int		p;
	int		k;
	int		x;

	(void)tab;
	x = 0;
	t = ft_calloc(sizeof(int *), size);
	if (!t)
		return ;
	o = 0;
	while (o < (size))
	{
		//if (t[o]) == 0;
		t[o] = -1;
		o++;
	}
	//TODO o => j
	o = -1;
	while (name[++o] != NULL)
	{
		//TODO trop de variable (new function ?)
		p = 0;
		k = -1;
		while (name[++k] != NULL)
		{
			if (ft_strncmp(name[o], name[k], ft_strlen(name[k])) > 0)
				p++;
			/*else if (ft_strncmp(name[o], name[k], ft_strlen(name[k])) < 0)
				p++;*/
		}
		if (o != p)
		{
			t[o] = p;
			/*tmp = tab[start + o];
			tab[start + o] = tab[start + p];
			tab[start + p] = tmp;*/
			//o = -1;

		}
	}
	o = 0;
	while (o < (size))
	{
		//if (t[o]) == 0;
		printf("%d_p=%d\n", o, t[o]);
		o++;
	}
	while (o < (size))
	{
		printf("%d_p=%d\n", o, t[o]);
		/*tmp = tab[start + i];
		tab[start + i] = tab[start + t[i]];
		tab[start + t[i]] = tmp;*/
		if (t[o] != -1)
		{
			tn = name[o];
			name[o] = name[t[o]];
			name[t[o]] = tn;
		}
		o++;
	}
	free(t);
	o = -1;
	while (name[++o] != NULL)
	{
		k = -1;
		while (name[++k] != NULL)
		{
			if (ft_strncmp(name[o], name[k], ft_strlen(name[k])) > 0)
				p++;
			if (o != p)
				x++;
		}
	}
	/*if (x != 0)
		sort_by_name(tab, name, size);*/
}


void	sort_by_word(int start, int end, char **env, int *tab)
{
	int		i;
	int		j;
	//int		tmp;
	char	**name;

	i = 0;
	j = 0;
	//tmp = 0;
	name = ft_calloc(sizeof(char *), (end - start));
	if (!name)
		return ;

	while (i < (end - start))
	{
		name[i] = ft_calloc(sizeof(char ), 20);
		if (!name[i])
		{
			free(name);
			return ;
		}
		i++;
	}
	i = start;
	while (tab[i] != -1)
	{
		name[j++] = ft_split(env[tab[i++]], '=')[0];
		name[j] = NULL;
	}
			//printf("caca%d\n", tab[i]);
		//TODO si le if est dans le while le programe tourne a l'infini
	if (j != 0)
	{
		//if (name[0][0] == 'C')
			sort_by_name(tab, name, (end - start));
		
	}

	/*if (j != 0)
	{
		i = 0;
		while (i < (end - start))
		{
			printf("%d_p=%d\n", i, t[i]);
			tmp = tab[start + i];
			tab[start + i] = tab[start + t[i]];
			tab[start + t[i]] = tmp;
			i++;
		}
		//free(t);
	}*/

	if (j != 0)
		clean_env(name);
	else
		free(name);
}


void	sort_by_letter(char c, char **env, int *tab)
{
	int	i;
	static int	j;
	int	start;

	i = 0;
	if (c == 'A')
		j = 0;
	start = j;
	while (env[i])
	{
		if (!ft_strncmp(env[i], &c, 1))
			tab[j++] = i;		
		i++;
	}
	tab[j] = -1;

	printf("______%c_____\n", c);
	sort_by_word(start, j, env, tab);
}

void	sort_env(char **env, int *tab)
{
	char	c;

	c = 'A';
	while (c != 123)
	{
		//printf("%c\n", c);
		sort_by_letter(c, env, tab);
		/*while (env[i])
		{
			if (!ft_strncmp(env[i], &c, 1))
			{
				printf("%s\n", env[i]);
			}
			i++;
		}*/
		/*if (!env[i])
		{
			i = 0;
		}*/
		//i++;
		if (c == 'Z')
			c = 'a';
		else
			c++;
	}
}
