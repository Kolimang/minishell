/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:26:40 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 19:15:32 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*check_cmd(t_command *command)
{
	if (command->argc == 1 && ft_strchr(command->args[0], '='))
	{
		free(command->args[0]);
		return (NULL);
	}
	return (command);
}

void	ft_print_command(t_command *command)
{
	// ft_printf("index            : %d\n", command->index);
	ft_printf("argc             : %d\n", command->argc);
	ft_printf("args             : ");
	ft_printarray(command->args, ' ');
	ft_printf("redir            : ");
	ft_print_redir(command);
	if (!command->ls_redirs)
		ft_printf("(null)");
	ft_printf("\n");
	ft_printf("prevpipe         : %d\n", command->prevpipe);
	ft_printf("nextpipe         : %d\n", command->nextpipe);
	ft_printf("--- --- --- --- --- ---\n");
}

void	ft_print_redir(t_command *command)
{
	t_redir	*redir;
	t_list	*rdlist;

	while (command->ls_redirs)
	{
		rdlist = command->ls_redirs;
		redir = rdlist->content;
		ft_printf("%s (%d)", redir->value, redir->type);
		if (command->ls_redirs->next)
			ft_printf(", ");
		command->ls_redirs = command->ls_redirs->next;
	}
}
