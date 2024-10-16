/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:11:02 by abboulak          #+#    #+#             */
/*   Updated: 2024/10/02 22:34:45 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_list(t_list *list)
{
	t_list		*tmp;
	const char	*t_types[] = {
		"WORD", "WHITE_SPACE", "NEW_LINE", "QUOTE",
		"DOUBLE_QUOTE", "ESCAPE", "ENV", "PIPE_LINE",
		"REDIR_IN", "REDIR_OUT", "HERE_DOC", "DREDIR_OUT"};
	const char	*t_states[] = {
		"IN_DQUOTE",
		"IN_QUOTE",
		"GENERAL"};
	tmp = list;
	while (tmp)
	{
		printf("'%s'\t", tmp->cont);
		printf("%d\t", tmp->len);
		printf("%s\t", t_types[tmp->type]);
		printf("%s\n", t_states[tmp->state]);
		printf("\n----------------------------------------\n");
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		i;
	int		j;
	int		k;

	1 && (i = 0, j = 0, k = 0, tmp_cmd = cmd);
	while (tmp_cmd)
	{
		1 && (i = 0, j = 0);
		printf("  COMMAND[%d] \n", k++);
		while ((tmp_cmd)->args &&  tmp_cmd->args[j])
			1 && (printf("args[%d]:  '%s'\n", j, tmp_cmd->args[j]), j++);
		while ((tmp_cmd)->redir && tmp_cmd->redir[i])
			1 && (printf("redir[%d]: '%s'\n", i, tmp_cmd->redir[i]), i++);
		printf("----------------\n");
		tmp_cmd = tmp_cmd->next;
	}
}
