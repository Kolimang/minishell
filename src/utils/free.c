/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 12:17:32 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_arr(char **array, int limit)
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

void	free_ls_lxmt_list *ls_lexemes)
{
	t_lexeme	*lex;
	t_list		*temp;
	int			i;

	i = 0;
	while (ls_lexemes)
	{
		temp = ls_lexemes;
		ls_lexemes = ls_lexemes->next;
		lex = temp->content;
		free(lex->str);
		free(lex->value);
		free(lex);
		lex = NULL;
		free(temp);
		temp = NULL;
		i++;
	}
}

void	free_commands(t_list *ls_commands)
{
	t_cmd	*cmd;
	t_redir		*redir;
	t_list		*temp;
	t_list		*temp2;

	while (ls_commands)
	{
		temp = ls_commands;
		ls_commands = ls_commands->next;
		cmd = temp->content;
		free_arr(cmd->args, array_len(cmd->args));
		while (cmd->ls_redirs)
		{
			temp2 = cmd->ls_redirs;
			cmd->ls_redirs = cmd->ls_redirs->next;
			redir = temp2->content;
			free(redir->val);
			free(redir);
			free(temp2);
			temp2 = NULL;
		}
		free(cmd);
		free(temp);
		temp = NULL;
	}
}

void	free_lists(t_list *ls_lexemes, t_list *ls_commands)
{
	free_ls_lxmls_lexemes);
	free_commands(ls_commands);
}
