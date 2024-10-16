/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboulak <abboulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:54:36 by abboulak          #+#    #+#             */
/*   Updated: 2024/10/01 01:50:35 by abboulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#define ALM ft_isalnum

void	init_list(t_list **list)
{
	*list = (t_list *)malloc(sizeof(t_list));
	(*list)->cont = NULL;
	(*list)->len = 0;
	(*list)->type = 0;
	(*list)->state = GENERAL;
	(*list)->next = NULL;
	(*list)->prev = NULL;
}

void	add_list(t_list **head, t_list *list)
{
	t_list	*tmp;

	if (!*head)
		*head = list;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = list;
	}
}

void	lexer_suite2(t_list **list, char **l, char *lcont)
{
	if (**l == '$')
	{
		(1) && (lcont = *l, (*list)->type = ENV, (*l)++, (*list)->len++);
		if ((**l != '\'' && **l != '\"' && **l != '$'))
		{
			while (**l && (ALM(**l) || **l == '_' || **l == '?'))
				(1) && ((*list)->len++, (*l)++);
			(1) && ((*list)->cont = ft_substr(lcont, 0, (*list)->len), (*l)--);
		}
		else if (**l == '$')
			1 && ((*list)->cont = ft_strdup("$$")), ((*list)->len = 1);
		else
			1 && ((*list)->cont = ft_strdup("")), ((*l)--);
	}
	else if (**l != ' ' && **l != '\n' && **l != '\''
		&& **l != '\"' && **l != '\\' && **l != '|'
		&& **l != '<' && **l != '>' && **l != '\0' && **l != '$')
	{
		(1) && (lcont = *l, (*list)->type = WORD);
		while (**l != ' ' && **l != '\n' && **l != '\'' && **l != '\"'
			&& **l != '\\' && **l != '|' && **l != '<'
			&& **l != '>' && **l != '\0' && **l != '$')
			(1) && ((*list)->len++, (*l)++);
		(1) && ((*list)->cont = ft_substr(lcont, 0, (*list)->len), (*l)--);
	}
}

void	lexer_suite1(t_list **list, char **line, char *lcont)
{
	(**line == ' ') && ((*list)->type = WHITE_SPACE, (*list)->len++);
	(**line == '\n') && ((*list)->type = NEW_LINE, (*list)->len++);
	(**line == '\'') && ((*list)->type = QUOTE, (*list)->len++);
	(**line == '\"') && ((*list)->type = DOUBLE_QUOTE, (*list)->len++);
	(**line == '\\') && ((*list)->type = ESCAPE, (*list)->len++);
	(**line == '|') && ((*list)->type = PIPE_LINE, (*list)->len++);
	if ((**line == '>' && *(*line + 1) == '>')
		|| (**line == '<' && *(*line + 1) == '<'))
	{
		(**line == '>') && ((*list)->type = 11,
			(*list)->cont = ft_strdup(">>"));
		(**line == '<') && ((*list)->type = 10,
			(*list)->cont = ft_strdup("<<"));
		(1) && ((*line)++, (*list)->len = 2);
	}
	else if (**line == '<')
		((*list)->type = REDIR_IN) && ((*list)->len++);
	else if (**line == '>')
		((*list)->type = REDIR_OUT) && ((*list)->len++);
}

t_list	*lexer(char	*line)
{
	t_list	*list;
	t_list	*head;
	t_list	*tmp;
	char	*lcont;

	head = NULL;
	while (line && *line)
	{
		init_list(&list);
		lexer_suite1(&list, &line, lcont);
		lexer_suite2(&list, &line, lcont);
		(!list->cont) && (list->cont = ft_substr(line, 0, list->len));
		(1) && (add_list(&head, list), line++);
	}
	(1) && (fixing_states(&head, 0, 0), tmp = head);
	(syntax_error(head, 0, NULL, tmp)) && (free_list(head), head = NULL);
	while (tmp)
	{
		if (tmp->type == ENV && (tmp->state == IN_DQUOTE
				|| tmp->state == IN_QUOTE) && tmp->len == 1)
			(1) && (free(tmp->cont), tmp->cont = ft_strdup("$"),
				tmp->type = WORD);
		tmp = tmp->next;
	}
	return (head);
}
