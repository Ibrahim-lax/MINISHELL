/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:22:38 by abboulak          #+#    #+#             */
/*   Updated: 2024/10/02 23:40:29 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#define ALM ft_isalnum

t_env	*list_env(char **env)
{
	t_env	*env_list;
	t_env	*head;
	t_env	*tmp;
	int		i;

	1 && (i = 0, env_list = NULL);
	while (env[i])
	{
		tmp = calloc(1, sizeof(t_env));
		if (!tmp)
			return (NULL);
		tmp->base = env[i];
		tmp->key = ft_substr(env[i], 0, (ft_strchr(env[i], '=') - env[i]));
		tmp->vl = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!env_list)
			1 && (env_list = tmp, head = env_list);
		else
			1 && (env_list->next = tmp, env_list = env_list->next);
		i++;
	}
	return (head);
}

void	fixing_env_dquote(t_list **list, t_env *env_list, t_env *te, int i)
{
	t_list	*t;

	t = *list;
	while (t)
	{
		if (t->type == ENV && t->state == IN_DQUOTE)
		{
			(1) && (te = env_list, i = 0);
			while (ALM(t->cont[i]) || t->cont[i] == '_'
				|| t->cont[i] == '?')
				i++;
			while (te)
			{
				if (!ft_strncmp(t->cont + 1, te->key, i - 1))
				{
					(1) && (free(t->cont), t->cont = ft_strdup(te->vl), i = -1);
					break ;
				}
				te = te->next;
			}
			if (i >= 0 && t->len > 1)
				1 && (free(t->cont), t->cont = ft_strdup(""));
		}
		t = t->next;
	}
}

char	*nonquote_suite(t_env *te, int i, t_list *t)
{
	char	**ts;
	char	**s;

	1 && (s = ft_split(te->vl, ' '), ts = s, i = 0, t->len = 0);
	while (*ts)
	{
		(1) && (t->len += ft_strlen(*ts), ts++, i++);
		if (!*ts)
			break ;
	}
	(1) && (free(t->cont), ts = s);
	t->cont = calloc(t->len + i + 1, 1);
	while (s)
	{
		t->cont = ft_modded_strcat(t->cont, *s, t->len + 1);
		s++;
		if (!*s)
		{
			free_split(ts);
			t->cont = ft_strtrim(t->cont, ' ');
			break ;
		}
	}
	return (t->cont);
}

void	fixing_env_nonquote(t_list **list, t_env *env_list, t_env *te, int i)
{
	t_list	*t;

	t = *list;
	while (t)
	{
		if (t->type == ENV && t->state == GENERAL)
		{
			(1) && (te = env_list, i = 0);
			if (t->cont[i] == '?')
				1 && (t->cont = "g_exit_status", i -= 1);
			while (ft_isalnum(t->cont[i]) || t->cont[i] == '_')
				i++;
			while (te)
			{
				if (!ft_strncmp(t->cont + 1, te->key, i - 1))
				{
					1 && (t->cont = nonquote_suite(te, i, t), i = -1);
					break ;
				}
				te = te->next;
			}
			if (i >= 0 && t->len > 1)
				1 && (free(t->cont), t->cont = ft_strdup(""));
		}
		t = t->next;
	}
}

void	fixing_env(t_list **list, char **env)
{
	t_env	*env_list;
	t_list	*t;
	t_env	*te;
	int		i;

	env_list = list_env(env);
	t = *list;
	te = env_list;
	i = 0;
	while (t)
	{
		if (t->type == HERE_DOC && t->state == GENERAL)
		{
			t = t->next;
			while (t->type == WHITE_SPACE)
				t = t->next;
			(t->type == ENV) && (t->type = WORD);
		}
		t = t->next;
	}
	t = *list;
	fixing_env_dquote(list, env_list, te, i);
	fixing_env_nonquote(list, env_list, te, i);
	free_env(env_list);
}
