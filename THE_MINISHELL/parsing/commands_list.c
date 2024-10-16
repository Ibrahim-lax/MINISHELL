/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:49:19 by abboulak          #+#    #+#             */
/*   Updated: 2024/10/03 21:08:47 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#define A ft_realloc
#define B ft_strjoin
#define C ft_strdup

void	init_cmd(t_cmd **cmd)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	(*cmd)->args = NULL;
	(*cmd)->redir = NULL;
	(*cmd)->next = NULL;
}

void	add_cmd(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!*head)
		*head = cmd;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}

char	**ft_realloc(char **str, char *cont)
{
	char	**new;
	int		i;

	i = 0;
	if (!str)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(cont);
		new[1] = NULL;
	}
	else
	{
		while (str[i])
			i++;
		new = (char **)malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (str[i])
		{
			new[i] = ft_strdup(str[i]);
			i++;
		}
		new[i] = ft_strdup(cont);
		new[i + 1] = NULL;
	}
	free_split(str);
	return (new);
}

t_cmd	*cmd_list(t_list *list)
{
	t_list	*tmp;
	t_cmd	*head;
	t_cmd	*cmd;
	t_list	*prev;
	int		i;
	char	*contTemp;

	head = NULL;
	tmp = list;
	prev = tmp;
	i = 0;
	while (tmp)
	{
		(i == 0) && (init_cmd(&cmd), i++);
		if (tmp->type == PIPE_LINE)
		{
			add_cmd(&head, cmd);
			i = 0;
		}
		else if (tmp->type == WHITE_SPACE && tmp->state == GENERAL)
		{
			tmp = tmp->next;
			continue ;
		}
		else if ((tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT || tmp->type == REDIR_IN) && tmp->next)
		{
			tmp = tmp->next;
			contTemp = B(B(C(prev->cont), " ", 1), tmp->cont, 1);
			cmd->redir = A(cmd->redir, contTemp);
			free(contTemp);
		}
		else
			cmd->args = A(cmd->args, tmp->cont);
		tmp = tmp->next;
		prev = tmp;
	}
	if (cmd)
		add_cmd(&head, cmd);
	return (head);
}
