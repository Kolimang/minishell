/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:26:40 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/03 17:02:32 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_args(t_list *ls_lxm, int argc)
{
	t_list		*temp;
	t_lexeme	*node;
	char		**args;
	int			i;

	args = malloc((argc + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	args[argc] = NULL;
	i = 0;
	temp = ls_lxm;
	while (temp)
	{
		node = temp->content;
		if (node->type == 2)
		{
			args[i] = ft_strdup(node->value);
			i++;
		}
		temp = temp->next;
	}
	return (args);
}

void	mark_as_arg(t_cmd *command, t_lexeme *node, t_env *env)
{
	command->argc += 1;
	node->type = 2;
	expand_lexeme(node, env);
}

t_cmd	*check_cmd(t_cmd *command)
{
	if (command->args[0] != NULL)
	{
		if (command->argc == 1 && ft_strchr(command->args[0], '='))
		{
			free(command->args[0]);
			return (NULL);
		}
		if (!ft_strncmp(command->args[0], ".", 2))
		{
			return (merror(command->args[0], NULL, NULL, 2), NULL);
		}
	}
	return (command);
}

void	check_pipes(t_cmd *command, int id, int nb_commands)
{
	if (id < nb_commands - 1)
		command->nextpipe = 1;
	if (id > 0)
		command->prevpipe = 1;
}

void	expand_nodes(t_lexeme **node1, t_lexeme **node2, t_env *env)
{
	expand_lexeme(*node1, env);
	expand_lexeme(*node2, env);
}
