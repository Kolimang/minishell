/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/16 12:00:41 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum {
	INPUT = 0,
	HEREDOC = 1,
	OUTPUT = 2,
	APPEND = 3
};

typedef struct s_command
{
	int		index;
	int		argc;
	char	**args;
	t_list	*redir_list;
	int		prevpipe;
	int		nextpipe;
}	t_command;

typedef struct s_redir
{
	char	*value;
	int		redir_type;
}	t_redir;

void		ft_print_command(t_command *command); // For debug
void		ft_print_redir(t_command *command); // For debug
t_command	*ft_parse_lexemes(t_list *lexemes, int id, int nb_commands); // turn lexemes-list into commands-list
char		**get_args(t_list *lexemes, int argc);
void		ft_add_redir(t_list **lexemes, t_command *command, char *redirvalue, int type);
void		handle_lexemes(t_list **lexemes, t_command *command);
t_command	*check_cmd(t_command *command);

#endif
