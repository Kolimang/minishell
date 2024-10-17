/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:02:12 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/17 14:20:51 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*lex_handle_heredoc(t_cmd_data *dt, char *delim)
{
	char		*hd_input;
	t_list		*ls_hd_lexemes;
	t_lexeme	*hd_lex;

	ls_hd_lexemes = NULL;
	while (dt->bool_heredoc)
	{
		hd_input = readline("\033[0;35mheredoc>\033[0m ");
		if (!hd_input)
			return (NULL);
		hd_lex = malloc(sizeof(t_lexeme));
		hd_lex->str = hd_input;
		hd_lex->value = NULL;
		hd_lex->type = 1;
		if (!ls_hd_lexemes)
			ls_hd_lexemes = ft_lstnew(hd_lex);
		else
		{
			if (!ft_strncmp(hd_input, delim, ft_strlen(delim)))
				return (free(hd_input), ls_hd_lexemes);
			ft_lstadd_back(&ls_hd_lexemes, ft_lstnew(hd_lex));
		}
	}
	return (ls_hd_lexemes);
}

char	*find_delim(t_list *list)
{
	int			i;
	t_lexeme	*lex;
	t_lexeme	*next_lex;

	i = 0;
	while (list)
	{
		lex = list->content;
		if ((!ft_strncmp(lex->str, "<<", 2))
			&& ft_strlen(lex->str) == 2)
		{
			if (list->next)
			{
				next_lex = list->next->content;
				return (next_lex->str);
			}
		}
		list = list->next;
	}
	return (NULL);
}
