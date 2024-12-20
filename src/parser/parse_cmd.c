/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/03 13:31:25 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_cmd(t_cmd *command)
{
	command->pid = 0;
	command->argc = 0;
	command->args = NULL;
	command->ls_redirs = NULL;
	command->eflag = 0;
	command->prevpipe = 0;
	command->nextpipe = 0;
	command->fd_hrdoc = -3;
	command->i = 0;
}

// Turn lexemes-list into commands-list
t_cmd	*ft_parse_lexemes(t_list *ls_lxm, int id, int nb_commands, t_env *env)
{
	t_cmd		*command;
	t_list		*temp;
	int			ret;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	init_cmd(command);
	check_pipes(command, id, nb_commands);
	temp = ls_lxm;
	while (temp)
	{
		ret = handle_lexemes(&temp, command, env);
		if (ret)
		{
			g_ret_val = ret;
			return (NULL);
		}
		temp = temp->next;
	}
	command->args = get_args(ls_lxm, command->argc);
	if (command->args[0]
		&& (command->args[0][0] == '\0' || ft_strchr(command->args[0], ' ')))
		return (free(command), merror(command->args[0], NULL, NULL, 127), NULL);
	return (check_cmd(command));
}

int	is_redir_op(t_lexeme *node)
{
	int	len;

	len = ft_strlen(node->str) + 1;
	if (ft_strncmp(node->str, "<<<", len) == 0
		|| ft_strncmp(node->str, ">>", len) == 0
		|| ft_strncmp(node->str, "<<", len) == 0
		|| ft_strncmp(node->str, "<>", len) == 0
		|| ft_strncmp(node->str, "<&", len) == 0
		|| ft_strncmp(node->str, ">&", len) == 0
		|| ft_strncmp(node->str, "&>", len) == 0
		|| ft_strncmp(node->str, ">|", len) == 0
		|| ft_strncmp(node->str, "<", len) == 0
		|| ft_strncmp(node->str, ">", len) == 0)
		return (1);
	return (0);
}

int	handle_lexemes(t_list **ls_lxm, t_cmd *command, t_env *env)
{
	t_lexeme	*node;
	t_lexeme	*nextnode;
	t_list		**temp;

	node = (*ls_lxm)->content;
	if (!is_redir_op(node))
		return (mark_as_arg(command, node, env), 0);
	if (!(*ls_lxm)->next)
		return (merror(NULL, NULL, "newline", 258));
	nextnode = (*ls_lxm)->next->content;
	expand_nodes(&node, &nextnode, env);
	if (is_redir_op(nextnode) || char_in_set("|&", nextnode->value[0]))
		return (merror(NULL, NULL, nextnode->value, 258));
	if (ft_strlen(node->value) > 2 && ft_strncmp(node->value, "<<", 2))
		return (merror(NULL, NULL, &node->value[2], 258));
	temp = ls_lxm;
	if (ft_strncmp(node->value, ">>", 3) == 0)
		return (ft_add_redir(temp, command, nextnode->value, APPEND), 0);
	else if (ft_strncmp(node->value, "<<", 3) == 0)
		return (ft_add_redir(temp, command, nextnode->value, HERE_DOC), 0);
	else if (ft_strncmp(node->value, "<", 2) == 0)
		return (ft_add_redir(temp, command, nextnode->value, INFILE), 0);
	else if (ft_strncmp(node->value, ">", 2) == 0)
		return (ft_add_redir(temp, command, nextnode->value, OUTFILE), 0);
	return (ft_add_redir(temp, command, nextnode->value, OTHER), 0);
}

void	ft_add_redir(t_list **ls_lxm, t_cmd *cmd, char *value, int type)
{
	t_redir	*redir;
	t_list	**temp;

	temp = ls_lxm;
	redir = malloc(sizeof(t_redir));
	redir->val = ft_strdup(value);
	redir->type = type;
	if (!cmd->ls_redirs)
		cmd->ls_redirs = ft_lstnew(redir);
	else
		ft_lstadd_back(&cmd->ls_redirs, ft_lstnew(redir));
	*temp = (*temp)->next;
}
