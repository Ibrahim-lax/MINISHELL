/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paring.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:45:40 by abboulak          #+#    #+#             */
/*   Updated: 2024/10/07 02:53:19 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	remove_node(t_list **list, t_list *nodeToremove, t_list *prevtemp)
{
	if (prevtemp == nodeToremove)
		*list = nodeToremove->next;
	else
		prevtemp->next = nodeToremove->next;
	nodeToremove->next = NULL;
	free(nodeToremove->cont);
	free(nodeToremove);
}

void	remove_quotes(t_list **list)
{
	t_list	*tmp;
	t_list	*prevtemp;

	1 && (tmp = *list, prevtemp = tmp);
	if (tmp && (tmp->state == 2 && (tmp->type == 4 || tmp->type == QUOTE)))
		1 && (remove_node(list, tmp, prevtemp), tmp = *list, prevtemp = tmp);
	while (tmp && tmp->next)
	{
		if (tmp->next->state == 2
			&& (tmp->next->type == 4 || tmp->next->type == 3))
			remove_node(list, tmp->next, prevtemp);
		else
			tmp = prevtemp->next;
		prevtemp = tmp;
	}
}

void	remove_spaces(t_list **list)
{
	t_list	*tmp;
	t_list	*prevtemp;

	1 && (tmp = *list, prevtemp = tmp);
	while (tmp)
	{
		if (tmp->state == GENERAL && tmp->type == WHITE_SPACE)
		{
			1 && (prevtemp = tmp, tmp = tmp->next);
			while (tmp->state == GENERAL && tmp->type == WHITE_SPACE)
				1 && (remove_node(list, tmp, prevtemp), tmp = prevtemp->next);
		}
		if (!tmp || !tmp->next)
			break ;
		tmp = tmp->next;
	}
}

void	remove_white_spaces(t_list **list)
{
	t_list	*tmp;
	t_list	*prevtemp;

	tmp = *list;
	while (tmp && tmp->next)
	{
		prevtemp = tmp;
		tmp = tmp->next;
		if (tmp->type == WHITE_SPACE)
			remove_node(list, tmp, prevtemp);
		tmp = prevtemp->next;
	}
}


void	ft_free_split(char **split)
{
	if (!split)
		return ;
	while (*split)
	{
		free(*split);
		*split = NULL;
		split++;
	}
	free(split);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_split(tmp->args);
		free_split(tmp->redir);
		free(tmp);
		tmp = NULL;
	}
}

int	compere_list(t_list *list1, t_list *list2)
{
	while (list1 && list2)
	{
		if (strcmp(list1->cont, list2->cont) != 0)
			return (0);
		list1 = list1->next;
		list2 = list2->next;
	}
	if (list1 || list2)
		return (0);
	return (1);
}

t_list	*copy_list(t_list *list)
{
	t_list	*new;
	t_list	*head;

	head = NULL;
	while (list)
	{
		init_list(&new);
		new->cont = ft_strdup(list->cont);
		add_list(&head, new);
		list = list->next;
	}
	return (head);
}

void	join_quoted_ones(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->state == IN_QUOTE || tmp->state == IN_DQUOTE)
		{
			while (tmp->state == IN_QUOTE || tmp->state == IN_DQUOTE)
			{
				if (tmp->next && (tmp->next->state == IN_QUOTE || tmp->next->state == IN_DQUOTE))
				{
					tmp->cont = ft_strjoin(tmp->cont, tmp->next->cont, 1);
					remove_node(list, tmp->next, tmp);
				}
				else
					break ;
			}
		}
		if (!tmp || !tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == ENV)
		{
			if (tmp->next && (tmp->next->state == IN_DQUOTE || tmp->next->state == IN_QUOTE))
			{
				tmp->cont = ft_strjoin(tmp->cont, tmp->next->cont, 1);
				remove_node(list, tmp->next, tmp);
			}
		}
		if (tmp->state == IN_DQUOTE || tmp->state == IN_QUOTE)
		{
			if (tmp->next && (tmp->next->type == ENV || tmp->next->type == WORD))
			{
				tmp->cont = ft_strjoin(tmp->cont, tmp->next->cont, 1);
				remove_node(list, tmp->next, tmp);
			}
		}
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == ENV)
		{
			if (tmp->next && (tmp->next->type == ENV || tmp->next->type == WORD))
			{
				tmp->cont = ft_strjoin(tmp->cont, tmp->next->cont, 1);
				remove_node(list, tmp->next, tmp);
			}
		}
		tmp = tmp->next;
	}
}

t_cmd	*parsing_input(char **env)
{
	char	*line;
	t_list	*list;
	t_cmd	*cmd;

	while (1)
	{
		line = readline("Minishell $>");
		if (line && ft_strlen(line) > 0)
		{
			line = ft_strtrim(line, ' ');
			add_history(line);
			list = lexer(line);
			if (!list)
			{
				free(line);
				continue ;
			}
			fixing_env(&list, env);
			remove_quotes(&list);
			remove_spaces(&list);
			t_list *tmp = copy_list(list);
			join_quoted_ones(&list);
			while (compere_list(list, tmp) == 0)
			{
				free_list(tmp);
				tmp = copy_list(list);
				join_quoted_ones(&list);
			}
			free_list(tmp);
			heredoc(list, NULL, NULL, env);
			remove_white_spaces(&list);
			tmp = copy_list(list);
			while (compere_list(list, tmp) == 0)
			{
				free_list(tmp);
				tmp = copy_list(list);
				remove_white_spaces(&list);
			}
			free_list(tmp);
			cmd = cmd_list(list);
			// print_cmd(cmd);
			// print_list(list);
			// free_cmd(cmd);
			free_list(list);
			free(line);
			return (cmd);
		}
	}
	return (0);
}
