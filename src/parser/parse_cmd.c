/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/14 15:42:57 by jrichir          ###   ########.fr       */
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

// Turn lexemes-list into commands-list
t_command	*ft_parse_lexemes(t_list *ls_lexemes, int id, int nb_commands)
{
	t_command	*command;
	t_list		*temp;
	int			i;
	int			ret;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(command);
	check_pipes(command, id, nb_commands);
	i = 0;
	temp = ls_lexemes;
	while (temp)
	{
		ret = handle_lexemes(&temp, command, 1);
		if (ret)
		{
			g_ret_value = ret;
			return (NULL);
		}
		temp = temp->next;
	}
	command->args = get_args(ls_lexemes, command->argc);
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

int	handle_lexemes(t_list **ls_lexemes, t_command *command, int flag)
{
	t_lexeme	*node;
	t_lexeme	*nextnode;
	t_list		**temp;

	node = (*ls_lexemes)->content;
	if (!is_redir_symbol(node))
		return (mark_as_arg(command, node), 0);
	if (!(*ls_lexemes)->next)
		return (merror(NULL, NULL, "newline", 258));
	nextnode = (*ls_lexemes)->next->content;
	if (is_redir_symbol(nextnode))
		return (merror(NULL, NULL, nextnode->value, 258));
	if (ft_strlen(node->value) > 2)
		return (merror(NULL, NULL, &node->value[2], 258));
	temp = ls_lexemes;
	if (ft_strncmp(node->value, ">>", 3) == 0)
		ft_add_redir(temp, command, nextnode->value, APPEND);
	else if (ft_strncmp(node->value, "<<", 3) == 0)
		ft_add_redir(temp, command, nextnode->value, HERE_DOC);
	else if (ft_strncmp(node->value, "<", 2) == 0)
		ft_add_redir(temp, command, nextnode->value, INFILE);
	else if (ft_strncmp(node->value, ">", 2) == 0)
		ft_add_redir(temp, command, nextnode->value, OUTFILE);
	return (0);
}

void	ft_add_redir(t_list **ls_lexemes, t_command *cmd, char *value, int type)
{
	t_redir	*redir;
	t_list	**temp;

	temp = ls_lexemes;
	redir = malloc(sizeof(t_redir));
	redir->value = ft_strdup(value);
	redir->type = type;
	if (!cmd->ls_redirs)
		cmd->ls_redirs = ft_lstnew(redir);
	else
		ft_lstadd_back(&cmd->ls_redirs, ft_lstnew(redir));
	*temp = (*temp)->next;
}
