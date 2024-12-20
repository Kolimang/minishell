/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/03 13:27:08 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_tok_type
{
	INFILE = 1,
	HERE_DOC,
	OUTFILE,
	APPEND,
	OTHER
}	t_tok_type;

typedef enum e_builtin_type
{
	B_ECHO = 1,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}	t_builtin_type;

typedef struct s_io_fd
{
	int	pipes;
	int	std_in;
	int	std_out;
	int	**fds;
}	t_io_fd;

typedef struct s_command
{
	int				pid;
	int				argc;
	char			*name;
	char			**args;
	t_list			*ls_redirs;
	int				eflag;
	int				prevpipe;
	int				nextpipe;
	int				fd_hrdoc;
	t_builtin_type	builtin;
	int				fd_in;
	int				fd_out;
	int				i;
}	t_cmd;

typedef struct s_redir
{
	char		*val;
	t_tok_type	type;
}	t_redir;

// parser_cmd.c
t_cmd	*ft_parse_lexemes(t_list *ls_lxm, int id, int nb_commands, t_env *env);
int		is_redir_op(t_lexeme *node);
int		handle_lexemes(t_list **ls_lxm, t_cmd *command, t_env *env);
void	ft_add_redir(t_list **ls_lxm, t_cmd *command, char *redirvalue,
			int type);

// parser_utils.c
void	check_pipes(t_cmd *command, int id, int nb_commands);
t_cmd	*check_cmd(t_cmd *command);
char	**get_args(t_list *ls_lxm, int argc);
void	mark_as_arg(t_cmd *command, t_lexeme *node, t_env *env);
void	expand_nodes(t_lexeme **node1, t_lexeme **node2, t_env *env);

#endif
