/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 02:05:29 by librahim          #+#    #+#             */
/*   Updated: 2024/10/07 02:55:55 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


 // for 2 commands;

void	exec_mult_cmds(t_data	*d, char **env)
{
	int	fd[2];
	int	pid;
	int	ex_st;

	if (d->cmd_nbr < 2)
		return ;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ex_single_nb_cmd(d, env);
	}
	else
	{
		waitpid(-1, &ex_st, 0);
		d->cmds = d->cmds->next;
		d->cmd_nbr--;
		// while (1);
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close (fd[1]);
			ex_single_nb_cmd(d, env);
			dup2(STDIN_FILENO, fd[0]);
			close(fd[0]);
		}
		else
		{
			// waitpid(pid, &ex_st, 0);
			printf("eaiting ");
		}
		return ;
	}
}
