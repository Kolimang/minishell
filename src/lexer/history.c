/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:46:59 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/28 18:25:53 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Unless cmd string is empty, add cmd to command history.
void	ft_add_cmd_to_history(char *cmd)
{
	if (cmd && *cmd)
		add_history(cmd);
}
