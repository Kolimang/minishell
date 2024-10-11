/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/11 11:50:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	int			index;
	int			argc;
	char		**args;
	char		*i_file;
	char		*i_hd_delimiter;
	char		*o_file;
	char		*o_file_append;
	int			nextpipe;
}	t_command;

t_command	*ft_parse_lexemes(t_list *lexemes, int id, int nb_commands); // turn lexemes-list into commands-list
void	ft_print_command(t_command *command);
char	**get_args(t_list *lexemes, int argc);

#endif
