/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/16 15:11:01 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command(t_command *command)
{
	command->index = 0;
	command->argc = 0;
	command->args = NULL;
	command->ls_redirs = NULL;
	command->io = NULL;
	command->prevpipe = 0;
	command->nextpipe = 0;
	command->is_hrdoc = 0;
}

char	**get_args(t_list *lexemes, int argc)
{
	t_lexemes	*node;
	char		**args;
	int			i;

	args = malloc((argc + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	args[argc] = NULL;
	i = 0;
	while (lexemes)
	{
		node = lexemes->content;
		if (node->type == 2)
		{
			args[i] = node->value;
			i++;
		}
		lexemes = lexemes->next;
	}
	return (args);
}

t_command	*ft_parse_lexemes(t_list *lexemes, int id, int nb_commands)
{
	t_command	*command;
	t_list		*start;
	int			i;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(command);
	command->index = id;
	if (id < nb_commands - 1)
		command->nextpipe = 1;
	else if (id > 0)
		command->prevpipe = 1;
	i = 0;
	start = lexemes;
	while (lexemes)
	{
		handle_lexemes(&lexemes, command);
		lexemes = lexemes->next;
	}
	command->args = get_args(start, command->argc);
	return (check_cmd(command));
}

void	handle_lexemes(t_list **lexemes, t_command *command)
{
	t_lexemes	*node;
	t_lexemes	*nextnode;

	node = (*lexemes)->content;
	if ((*lexemes)->next && (*lexemes)->next->content)
		nextnode = (*lexemes)->next->content;
	if (ft_strncmp(node->value, "<<", 2) == 0)
	{
		ft_add_redir(lexemes, command, nextnode->value, HERE_DOC);
		command->is_hrdoc = 1;
	}
	else if (ft_strncmp(node->value, ">>", 2) == 0)
		ft_add_redir(lexemes, command, nextnode->value, APPEND);
	else if (ft_strncmp(node->value, "<", 1) == 0)
		ft_add_redir(lexemes, command, nextnode->value, INFILE);
	else if (ft_strncmp(node->value, ">", 1) == 0)
		ft_add_redir(lexemes, command, nextnode->value, OUTFILE);
	else
	{
		command->argc += 1;
		node->type = 2;
	}
}

void	ft_add_redir(t_list **lexemes, t_command *command, char *redirvalue, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->value = redirvalue;
	redir->type = type;
	if (!command->ls_redirs)
		command->ls_redirs = ft_lstnew(redir);
	else
		ft_lstadd_back(&command->ls_redirs, ft_lstnew(redir));
	*lexemes = (*lexemes)->next;
}
