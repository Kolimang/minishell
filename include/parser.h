/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/18 16:00:14 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_tok_type
{
	INFILE = 0,
	HERE_DOC,
	OUTFILE,
	APPEND,	
}	t_tok_type;

typedef struct s_io_fd
{
	int	fd_pipe[2];
	int	std_in;//backup des stdio
	int	std_out;//backup des stdio
	int	fd_in;//current fd in
	int	fd_out;//current fd out 
	int	fd_hrdoc;//fd_tmp pour HRDOC
}	t_io_fd;

typedef struct s_command
{
	int		index;
	int		argc;
	char	*name;
	char	**args;
	t_list	*ls_redirs;
	t_io_fd	*io;
	int		prevpipe;
	int		nextpipe;
	int		is_hrdoc;
}	t_command;

typedef struct s_redir
{
	char		*value;
	t_tok_type	type;
}	t_redir;

t_command	*check_cmd(t_command *command);
t_command	*ft_parse_lexemes(t_list *ls_lexemes, int id, int nb_commands);
char		**get_args(t_list *ls_lexemes, int argc);
void		handle_lexemes(t_list **ls_lexemes, t_command *command);
void		ft_add_redir(t_list **ls_lexemes, t_command *command, char *redirvalue,
				int type);

// For debugging
void		ft_print_command(t_command *command);
void		ft_print_redir(t_command *command);
#endif
