/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:46:59 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 15:47:14 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the cmd string is empty, if it is not then it is added to history.
void	ft_add_cmd_to_history(char *cmd)
{
	if (cmd && *cmd)
		add_history(cmd);
}
