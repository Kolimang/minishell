/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:02:12 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/08 16:32:03 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*lex_handle_heredoc(t_cmd_data *dt, char *delim)
{
	char	*hd_input;
	t_list	*hd_tokens;

	hd_tokens = NULL;
	if (dt->bool_heredoc)
	{
		while (1)
		{
			hd_input = readline("\033[0;32mheredoc>\033[0m ");
			if (!hd_input)
			{
				free(hd_input);
				return (NULL);
			}
			if (!hd_tokens)
				hd_tokens = ft_lstnew(hd_input);
			else
			{
				if (!ft_strncmp(hd_input, delim, ft_strlen(delim)))
					return (hd_tokens);
				ft_lstadd_back(&hd_tokens, ft_lstnew(hd_input));
			}
		}
	}
	return (hd_tokens);
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
