/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:11:02 by librahim          #+#    #+#             */
/*   Updated: 2024/10/07 23:01:37 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_single_nb_cmd(t_data	*d, char **env)
{
	int		i;
	char	*p;

	i = 0;
	while (d->paths[i])
	{
		p = ft_strjoin(d->paths[i], "/", 0);
		p = ft_strjoin(p, d->cmds->args[0], 1);
		if (execve(p, d->cmds->args , env) == -1)
			i++;
	}
	free(p);
	perror("Error:");
}

void	ft_print_exports_var(t_env *s)
{
	t_env	*cur;

	if (!s)
		return ;
	cur = s;
	while (cur)
	{
		ft_putstr_fd("export ", 1);
		if (cur->key)
			ft_putstr_fd(cur->key, 1);
		if (ft_strchr(cur->base, '='))
		{
			ft_putstr_fd("=\"", 1);
			if (cur->vl)
				ft_putstr_fd(cur->vl, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		cur = cur->next;
	}
}

void	how_many_cmds(t_data *d)
{
	int		cmd;
	t_cmd	*cur;

	cmd = 0;
	cur = d->cmds;
	while (cur)
	{
		cmd++;
		cur = cur->next;
	}
	d->cmd_nbr = cmd;
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*str;

	if (!cmd || !cmd->args)
		return (0);
	str = cmd->args[0];
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

t_data	*init_data(char **env)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if(!d)
	{
		printf("error malloc\n");
		return NULL;
	}
	d->cmds = parsing_input(env);
	if (!d->cmds)
		return NULL;
	d->env = list_env(env);
	d->exp = list_env(env);
	d->paths = get_path(search_for_path(d->env));
	how_many_cmds(d);
	return (d);
}

int	start_execute(t_data *d, char **evvv)
{
	if (!ft_isbuiltin(d->cmds))
		exec_mult_cmds(d, evvv);
	return 0;
}

t_env	*search_for_path(t_env	*env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return env;
		else
			env = env->next;
	}
	return NULL;
}

char	**get_path(t_env *e)
{
	char **res;

	if (e && e->vl != NULL && *(e->vl))
		res = ft_split(e->vl, ':');
	if (!res)
		return NULL;
	return (res);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*d;

	while (1)
	{
		d = init_data(env);
		if (!d)
		{
			printf("error initialization\n");
			break ;
		}
		start_execute(d, env);
	}
	return (0);
}
