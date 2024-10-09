/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:02:12 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/09 13:36:20 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*lex_handle_heredoc(t_cmd_data *dt, char *delim)
{
	char		*hd_input;
	t_list		*hd_lexemes_list;
	t_lexemes	*hd_lexeme;

	hd_lexemes_list = NULL;
	while (dt->bool_heredoc)
	{
		hd_input = readline("\033[0;35mheredoc>\033[0m ");
		if (!hd_input)
			return (NULL);
		hd_lexeme = malloc(sizeof(t_lexemes));
		hd_lexeme->str = hd_input;
		hd_lexeme->value = NULL;
		hd_lexeme->type = 1;
		if (!hd_lexemes_list)
			hd_lexemes_list = ft_lstnew(hd_lexeme);
		else
		{
			if (!ft_strncmp(hd_input, delim, ft_strlen(delim)))
				return (free(hd_input), hd_lexemes_list);
			ft_lstadd_back(&hd_lexemes_list, ft_lstnew(hd_lexeme));
		}
	}
	return (hd_lexemes_list);
}

char	*find_delim(t_list *list)
{
	int			i;
	t_lexemes	*lexeme;
	t_lexemes	*lexeme_next;

	i = 0;
	while (list)
	{
		lexeme = list->content;
		if ((!ft_strncmp(lexeme->str, "<<", 2))
			&& ft_strlen(lexeme->str) == 2)
		{
			if (list->next)
			{
				lexeme_next = list->next->content;
				return (lexeme_next->str);
			}
		}
		list = list->next;
	}
	return (NULL);
}
