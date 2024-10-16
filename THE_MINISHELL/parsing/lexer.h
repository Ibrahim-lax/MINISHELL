/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:32:57 by librahim          #+#    #+#             */
/*   Updated: 2024/10/08 22:35:07 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define g_exit_status "g_exit_status"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "../GNL/get_next_line.h"

# define COLOR_RED "\033[0;31m"
# define COLOR_BOLD_GREEN "\033[1;32m"
# define TEXT_BOLD "\033[1m"
# define RESET_FORMATTING "\033[0m"

enum e_type
{
	WORD,
	WHITE_SPACE,
	NEW_LINE,
	QUOTE,
	DOUBLE_QUOTE,
	ESCAPE,
	ENV,
	PIPE_LINE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_list
{
	char			*cont;
	int				len;
	enum e_type		type;
	enum e_state	state;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_env
{
	char			*key;
	char			*base;
	char			*vl;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*line;
	char			**args;
	char			**redir;
	int				exit_status;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_data
{
	int		cmd_nbr;
	t_env	*env;
	t_env	*exp;
	char	**paths;
	t_list	*list;
	t_cmd	*cmds;
	pid_t	*pids;
}				t_data;

t_env	*search_for_path(t_env	*env);
char	**get_path(t_env	*e);
t_list	*lexer(char	*line);
int		syntax_error(t_list *list, int i, char *s, t_list *tmp);
void	fixing_states(t_list **list, int i, int j);
void	fixing_env(t_list **list, char **env);
char	*ft_modded_strcat(char *dest, char *src, int len);
void	init_list(t_list **list);
t_cmd	*cmd_list(t_list *list);
void	heredoc(t_list *tmp, char *li, t_list	*prev, char **env);
void	print_cmd(t_cmd *cmd);
void	print_list(t_list *list);
int		ft_strcmp(char *s1, char *s2);
void	free_list(t_list *list);
void	free_env(t_env *env);
void	lexer_suite1(t_list **list, char **line, char *lcont);
void	lexer_suite2(t_list **list, char **l, char *lcont);
void	add_list(t_list **head, t_list *list);
void	remove_node(t_list **list, t_list *nodeToremove, t_list *prevtemp);
t_cmd	*parsing_input(char **env);
void	free_cmd(t_cmd *cmd);
void	ex_single_nb_cmd(t_data	*d, char **env);
t_env	*list_env(char **env);
void	how_many_cmds(t_data *d);

#endif
