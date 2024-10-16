/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexemes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/15 13:43:31 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// hdoc_flag: 1 for normal expansion ; 2 for heredoc expansion
void	ft_expand_lexeme_list(t_list *list, t_env *env)
{
	if (!list)
		return ;
	while (list)
	{
		expand_lexeme(list->content, env);
		list = list->next;
	}
}

t_lexemes	*create_lexeme(char *str)
{
	t_lexemes	*lexeme;

	if (!str || !*str) // Check for NULL or empty string
		return (NULL);
	lexeme = ft_calloc(1, sizeof(t_lexemes));
	if (!lexeme) // Check if memory allocation was successful
		return (NULL);
	lexeme->str = ft_strdup(str);
	if (!lexeme->str) // Check if strdup was successful
	{
		free(lexeme);
		return (NULL);
	}
	lexeme->next = NULL;
	return (lexeme);
}
