/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:59:16 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/18 12:08:51 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_error(const char *msg)
{
	g_ret_val = EXIT_FAILURE;
	write(2, "minishell: ", 12);
	perror(msg);
	return (-1);
}

void	return_error(char *arg)
{
	g_ret_val = EXIT_FAILURE;
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	is_last(t_list *curr)
{
	return (curr->next == NULL);
}
