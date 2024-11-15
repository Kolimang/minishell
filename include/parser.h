/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 07:07:49 by jrichir          ###   ########.fr       */
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
}	t_tok_type;

typedef enum e_builtin_type
{
	B_ECHO = 1,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT,
}	t_builtin_type;

typedef struct s_io_fd
{
	int	pipe[2];
	int	std_in;//backup des stdio
	int	std_out;//backup des stdio
	int	fd_in;
	int	fd_out;
	// int	fd_tmp;//for closing multi fds
}	t_io_fd;

typedef struct s_command
{
	int		pid;
	int		argc;
	char	*name;
	char	**args;
	t_list	*ls_redirs;
	int		eflag;
	int		prevpipe;
	int		nextpipe;
	int		fd_hrdoc;
	t_builtin_type	builtin;
}	t_command;

typedef struct s_redir
{
	char		*value;
	t_tok_type	type;
}	t_redir;

void		check_pipes(t_command *command, int id, int nb_commands);
t_command	*check_cmd(t_command *command);
t_command	*ft_parse_lexemes(t_list *ls_lexemes, int id, int nb_commands);
char		**get_args(t_list *ls_lexemes, int argc);
int			is_redir_symbol(t_lexeme *node);
int			handle_lexemes(t_list **ls_lexemes, t_command *command, int flag);
void		ft_add_redir(t_list **ls_lexemes, t_command *command, char *redirvalue,
				int type);
void		mark_as_arg(t_command *command, t_lexeme *node);

#endif
