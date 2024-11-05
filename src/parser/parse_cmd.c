/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/05 16:33:01 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command(t_command *command)
{
	command->pid = 0;
	command->argc = 0;
	command->args = NULL;
	command->ls_redirs = NULL;
	command->prevpipe = 0;
	command->nextpipe = 0;
	command->fd_hrdoc = -3;
}

char	**get_args(t_list *ls_lexemes, int argc)
{
	t_lexeme	*node;
	char		**args;
	int			i;

	args = malloc((argc + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	args[argc] = NULL;
	i = 0;
	while (ls_lexemes)
	{
		node = ls_lexemes->content;
		if (node->type == 2)
		{
			args[i] = node->value;
			i++;
		}
		ls_lexemes = ls_lexemes->next;
	}
	return (args);
}

// Turn lexemes-list into commands-list
t_command	*ft_parse_lexemes(t_list *ls_lexemes, int id, int nb_commands)
{
	t_command	*command;
	t_list		*start;
	int			i;
	int			ret;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(command);
	if (id < nb_commands - 1)
		command->nextpipe = 1;
	else if (id > 0)
		command->prevpipe = 1;
	i = 0;
	start = ls_lexemes;
	while (ls_lexemes)
	{
		ret = handle_lexemes(&ls_lexemes, command, 1);
		if (ret)
		{
			g_ret_value = ret;
			return (NULL);
		}
		ls_lexemes = ls_lexemes->next;
	}
	command->args = get_args(start, command->argc);
	return (check_cmd(command));
}

int	is_redir_symbol(t_lexeme *node)
{
	if (ft_strncmp(node->value, ">>", 2) == 0
	|| ft_strncmp(node->value, "<<", 2) == 0
	|| ft_strncmp(node->value, "<", 1) == 0
	|| ft_strncmp(node->value, ">", 1) == 0)
		return (1);
	return (0);
}

void	set_as_arg(t_command *command, t_lexeme *node)
{
	command->argc += 1;
	node->type = 2;
}

int	handle_lexemes(t_list **ls_lexemes, t_command *command, int flag)
{
	t_lexeme	*node;
	t_lexeme	*nextnode;

	node = (*ls_lexemes)->content;
	if (!is_redir_symbol(node))
		return (set_as_arg(command, node), 0);
	if (!(*ls_lexemes)->next)
		return (merror("minishell", NULL,
				"syntax error near unexpected token `newline\'", 258));
	nextnode = (*ls_lexemes)->next->content;
	if (is_redir_symbol(nextnode))
		return (merror("minishell: syntax error near unexpected token",
				NULL, nextnode->value, 258));
	if (ft_strlen(node->value) > 2)
		return (merror("minishell",
				NULL, "syntax error (bad redirection symbol)", 258));
	if (ft_strncmp(node->value, ">>", 3) == 0)
		ft_add_redir(ls_lexemes, command, nextnode->value, APPEND);
	else if (ft_strncmp(node->value, "<<", 3) == 0)
		ft_add_redir(ls_lexemes, command, nextnode->value, HERE_DOC);
	else if (ft_strncmp(node->value, "<", 2) == 0)
		ft_add_redir(ls_lexemes, command, nextnode->value, INFILE);
	else if (ft_strncmp(node->value, ">", 2) == 0)
		ft_add_redir(ls_lexemes, command, nextnode->value, OUTFILE);
	return (0);
}

void	ft_add_redir(t_list **ls_lexemes, t_command *cmd, char *value, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->value = value;
	redir->type = type;
	if (!cmd->ls_redirs)
		cmd->ls_redirs = ft_lstnew(redir);
	else
		ft_lstadd_back(&cmd->ls_redirs, ft_lstnew(redir));
	*ls_lexemes = (*ls_lexemes)->next;
}
