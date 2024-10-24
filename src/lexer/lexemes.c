/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexemes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/17 15:00:05 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexeme	*create_lexeme(char *str)
{
	t_lexeme	*lex;

	if (!str || !*str) // Check for NULL or empty string
		return (NULL);
	lex = ft_calloc(1, sizeof(t_lexeme));
	if (!lex) // Check if memory allocation was successful
		return (NULL);
	lex->str = ft_strdup(str);
	if (!lex->str) // Check if strdup was successful
	{
		free(lex);
		return (NULL);
	}
	return (lex);
}

int	init_lexeme(char *lex_str, t_cmd_data *data, t_list	**ls_lexemes)
{
	t_lexeme	*lex;

	lex = malloc(sizeof(t_lexeme));
	if (!lex)
		return (-1);
	lex->index = data->tok_id;
	lex->str = lex_str;
	lex->value = NULL;
	lex->type = 0;
	if (!*ls_lexemes)
		*ls_lexemes = ft_lstnew(lex);
	else
		ft_lstadd_back(ls_lexemes, ft_lstnew(lex));
	return (0);
}

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
