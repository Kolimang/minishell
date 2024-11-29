/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/29 22:23:53 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_exit_args(t_list	*cmds)
{
	t_list	*temp;
	t_cmd	*cmd;

	temp = cmds;
	while (temp)
	{
		cmd = cmds->content;
		if (!ft_strncmp(cmd->args[0], "exit", 5))
		{
			return (cmd->args);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_cmd	*get_exit_cmd(t_list *cmds)
{
	t_list	*temp;
	t_cmd	*cmd;

	temp = cmds;
	while (temp)
	{
		cmd = cmds->content;
		if (!ft_strncmp(cmd->args[0], "exit", 5))
		{
			if (temp->next)
				cmd->eflag = 1;
			return (cmd);
		}
		temp = temp->next;
	}
	return (NULL);
}
