/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 11:40:14 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_input_cmd(char **cmdref)
{
	char	last;
	char	*cmd;

	cmd = ft_strtrim_replace(cmdref);
	if (!cmd)
		return (EXIT_FAILURE);
	if ((int)ft_strlen(cmd) > 0)
	{
		last = cmd[(int)ft_strlen(cmd) - 1];
		if (cmd[0] == '|' || last == '|')
			return (merror(NULL, NULL, "|", 258));
	}
	else if (cmd[0] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_commands(char **cmds, int *i)
{
	while (cmds[*i])
	{
		cmds[*i] = ft_strtrim_replace(&cmds[*i]);
		if (!cmds[*i])
			return (EXIT_FAILURE);
		if (cmds[*i] && (cmds[*i][0] == '\0'))
		{
			*i = -1;
			return (merror(NULL, NULL, "|", 258));
		}
		(*i)++;
	}
	return (EXIT_SUCCESS);
}
