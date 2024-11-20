/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 17:31:33 by lboumahd         ###   ########.fr       */
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
t_cmd	*ft_parse_lexemes(t_list *ls_lxm, int id, int nb_commands)
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
		ret = handle_lexemes(&temp, command);
		if (ret)
		{
			g_ret_val = ret;
			return (NULL);
		}
		temp = temp->next;
	}
	command->args = get_args(ls_lxm, command->argc);
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

int	handle_lexemes(t_list **ls_lxm, t_cmd *command)
{
	t_lexeme	*node;
	t_lexeme	*nextnode;
	t_list		**temp;

	node = (*ls_lxm)->content;
	if (!is_redir_symbol(node))
		return (mark_as_arg(command, node), 0);
	if (!(*ls_lxm)->next)
		return (merror(NULL, NULL, "newline", 258));
	nextnode = (*ls_lxm)->next->content;
	if (is_redir_symbol(nextnode))
		return (merror(NULL, NULL, nextnode->value, 258));
	if (ft_strlen(node->value) > 2)
		return (merror(NULL, NULL, &node->value[2], 258));
	temp = ls_lxm;
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
