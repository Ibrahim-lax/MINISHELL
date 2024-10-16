/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboulak <abboulak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:50:28 by abboulak          #+#    #+#             */
/*   Updated: 2024/09/28 10:48:36 by abboulak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*lexer_heredoc(char	*line)
{
	t_list	*list;
	t_list	*head;
	t_list	*tmp;
	char	*lcont;

	head = NULL;
	while (*line)
	{
		init_list(&list);
		lexer_suite1(&list, &line, lcont);
		lexer_suite2(&list, &line, lcont);
		(!list->cont) && (list->cont = ft_substr(line, 0, list->len));
		(1) && (add_list(&head, list), line++);
	}
	(1) && (fixing_states(&head, 0, 0), tmp = head);
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

void	expanding_env(char	*line, char **env, int fd)
{
	t_list	*list;
	t_list	*tmp;

	list = lexer_heredoc(line);
	tmp = list;
	fixing_env(&list, env);
	while (list)
	{
		write (fd, list->cont, ft_strlen(list->cont));
		list = list->next;
	}
	free_list(tmp);
}

void	heredoc_suite(int *fd)
{
	FILE	*file;

	file = fopen("heredoc_tmp", "r");
	if (file)
		1 && (fclose(file), remove("heredoc_tmp"));
	*fd = open ("heredoc_tmp", O_RDWR | O_CREAT, 0666);
}

void	heredoc(t_list *tmp, char *li, t_list *prev, char **env)
{
	int	fd;
	int	len;

	while (tmp)
	{
		prev = tmp;
		if (tmp->type == HERE_DOC && tmp->state == GENERAL)
		{
			tmp = tmp->next;
			(tmp->type == WHITE_SPACE) && (tmp = tmp->next);
			1 && (heredoc_suite(&fd), tmp->type = WHITE_SPACE);
			while (1)
			{
				1 && (li = gnl(0), len = ft_strlen(li) - 1);
				(len < ft_strlen(tmp->cont)) && (len = ft_strlen(tmp->cont));
				(ft_strncmp(li, tmp->cont, len) == 0) && (free(li), li = NULL);
				if (!li)
					break ;
				1 && (expanding_env(li, env, fd), free(li), li = NULL);
			}
			1 && (free(prev->cont), prev->cont = ft_strdup("heredoc_tmp"));
			1 && (prev->type = WORD, close (fd));
		}
		tmp = tmp->next;
	}
}
