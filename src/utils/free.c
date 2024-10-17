/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/17 15:04:48 by jrichir          ###   ########.fr       */
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

void	free_lexemes(t_list *ls_lexemes)
{
	t_lexeme	*lex;

	while (ls_lexemes)
	{
		lex = ls_lexemes->content;
		free(lex->str);
		free(lex->value);
		free(lex);
		ls_lexemes = ls_lexemes->next;
	}
}

void	free_commands(t_list *ls_commands)
{
	t_command	*cmd;
	t_redir		*redir;

	while (ls_commands)
	{
		cmd = ls_commands->content;
		array_str_free(cmd->args, ft_arraylen(cmd->args));
		while (cmd->ls_redirs)
		{
			redir = cmd->ls_redirs->content;
			free(redir->value);
			cmd->ls_redirs = cmd->ls_redirs->next;
		}
		free(cmd);
		ls_commands = ls_commands->next;
	}
}

void	free_lists(t_list *ls_lexemes, t_list *ls_commands)
{
	free_lexemes(ls_lexemes);
	free_commands(ls_lexemes);
}
