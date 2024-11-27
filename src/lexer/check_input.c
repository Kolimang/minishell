/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/27 14:29:19 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	successive_pipes(char *input)
{
	char	*c;
	int		i;
	int		j;
	int		in_sq;
	int		in_dq;

	in_sq = 0;
	in_dq = 0;
	i = -1;
	while (input[++i])
	{
		c = &input[i];
		updt_quote_status(*c, &in_sq, &in_dq);
		if (*c == '|' && !in_sq && !in_dq)
		{
			j = 1;
			while (input[i + j] && input[i + j] == ' ')
				j++;
			if (input[i + j] && input[i + j] == '|')
				return (1);
			if (i == 0 || !is_redir_chr(input[i - 1]))
				*c = 6;
		}
	}
	return (0);
}

char	**cmd_split(char *input)
{
	char	**cmds;

	cmds = ft_split(input, 6);
	if (!cmds)
		return (NULL);
	return (cmds);
}

int	ft_check_input_cmd(char **cmdref)
{
	char	*cmd;

	*cmdref = ft_strtrim_replace(cmdref);
	cmd = *cmdref;
	if (!cmd)
		return (EXIT_FAILURE);
	if ((int)ft_strlen(cmd) > 0)
		if (cmd[0] == '|')
			return (merror(NULL, NULL, "|", 258));
	if ((int)ft_strlen(cmd) > 1)
	{
		if (cmd[ft_strlen(cmd) - 1] == '|'
			&& !char_in_set("<>", cmd[ft_strlen(cmd) - 2]))
			return (merror(NULL, NULL, "|", 258));
	}
	else if (cmd[0] == '\0')
		return (EXIT_FAILURE);
	if (successive_pipes(cmd))
		return (merror(NULL, NULL, "|", 258));
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
