/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:26:40 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/19 13:37:09 by lboumahd         ###   ########.fr       */
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

void	mark_as_arg(t_cmd *command, t_lexeme *node)
{
	command->argc += 1;
	node->type = 2;
}

t_cmd	*check_cmd(t_cmd *command)
{
	if (command->argc == 1 && ft_strchr(command->args[0], '='))
	{
		free(command->args[0]);
		return (NULL);
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
// void check_pipes(t_cmd *command, int id, int nb_commands)
// {
//     command->prevpipe = (id > 0);
//     command->nextpipe = (id < nb_commands - 1);
// }