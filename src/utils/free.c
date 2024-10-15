/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/15 14:19:20 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	array_str_free(char **array, int limit)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (++i < limit)
	{
		free(array[i]);
	}
	free(array);
}

void	cleanup_lexemes(t_lexemes *lexeme)
{
	t_lexemes	*tmp;

	while (lexeme)
	{
		tmp = lexeme;
		free(lexeme->str);
		free(lexeme->value);
		lexeme = lexeme->next;
		free(tmp);
	}
}
