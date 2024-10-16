/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:54:41 by abboulak          #+#    #+#             */
/*   Updated: 2024/10/03 21:07:49 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#define STR "syntax error near unexpected token `"

void	print_error(int i, char *s)
{
	char	*tmp;

	tmp = NULL;
	(s) && (tmp = ft_strjoin(ft_strdup(s), "'\n", 1));
	if (i == 0)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (i == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd(STR, 2);
		ft_putstr_fd(tmp, 2);
	}
	(tmp) && (free(tmp), tmp = NULL);
}

int	syntax_error(t_list *list, int i, char *s, t_list *tmp)
{
	(1) && (tmp = list, s = STR, i = 0);
	while (tmp)
	{
		if ((tmp->type == PIPE_LINE) && (tmp->state == GENERAL))
		{
			(tmp = tmp->next);
			while (tmp && tmp->type == WHITE_SPACE)
				tmp = tmp->next;
			if (!tmp || tmp->type == PIPE_LINE || i == 0)
				return (print_error(0, NULL), 1);
		}
		if ((tmp->type >= 8 && tmp->type <= 11) && tmp->state == 2)
		{
			(tmp = tmp->next);
			while (tmp && tmp->type == WHITE_SPACE)
				tmp = tmp->next;
			if (!(tmp))
				return (print_error(1, NULL), 1);
			if (tmp->type >= 7 && tmp->type <= 11)
				return (print_error(2, tmp->cont), 1);
		}
		1 && (tmp = tmp->next, i++);
	}
	return (0);
}

void	fixing_states(t_list **list, int i, int j)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == DOUBLE_QUOTE || tmp->type == QUOTE)
		{
			(1) && (i = 0, j = tmp->type);
			while (tmp->next)
			{
				(1) && (tmp = tmp->next, tmp->state = (4 - j));
				if (tmp->type == j)
				{
					(1) && (tmp->state = GENERAL, i++);
					break ;
				}
			}
			if (i == 0)
			{
				printf("Error: missing quote\n");
				exit(1);
			}
		}
		tmp = tmp->next;
	}
}
