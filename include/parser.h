/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/10 15:00:59 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	int					index;
	int					builtin;
	char				*name;
	char				*options;
	char				*args;
	char				*i_file;
	t_list				*i_heredoc;
	char				*o_file;
	char				*o_file_append;
	struct s_command	*next;
}	t_command;

t_command	*ft_parse_lexemes(t_list *lexemes, int id); // turn lexemes-list into commands-list
void	ft_print_command(t_command *command);

#endif
