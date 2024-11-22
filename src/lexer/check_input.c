/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/22 04:25:01 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	checks_on_pipe_char(char *input, int i, int *in_sq, int *in_dq)
{
	char *c;

	c = &input[i];
	if (*c == '\"')
	{
		if (*in_dq == 0)
			*in_dq = 1;
		else
			*in_dq = 0;
	}
	else if (*c == '\'')
	{
		if (*in_sq == 0)
			*in_sq = 1;
		else
			*in_sq = 0;
	}
	else if (*c == '|' && *in_sq == 0 && *in_dq == 0)
	{
		if (i == 0 || !is_operator(input[i - 1]))
			*c = 6;
	}
}

char	**cmd_split(char *input)
{
	int		i;
	int		in_sq;
	int		in_dq;
	char	**cmds;

	in_sq = 0;
	in_dq = 0;
	i = -1;
	while (input[++i])
		checks_on_pipe_char(input, i, &in_sq, &in_dq);
	cmds = ft_split(input, 6);
	if (!cmds)
		return (NULL);
	i = -1;
	while (cmds[++i])
	{
		cmds[i] = ft_strtrim_replace(&cmds[i]);
		if (!cmds[i])
		{
			free_arr(cmds, i);
			return (NULL);
		}
	}
	return (cmds);
}

int	ft_check_input_cmd(char **cmdref)
{
	//int		last;
	char	*cmd;

	*cmdref = ft_strtrim_replace(cmdref);
	cmd = *cmdref;
	if (!cmd)
		return (EXIT_FAILURE);
	if ((int)ft_strlen(cmd) > 0)
	{
		//last = ft_strlen(cmd) - 1;
		if (cmd[0] == '|')
			return (merror(NULL, NULL, "|", 258));
		/*else if (cmd[last] == '|')
		{
			if (last - 1 >= 0 && cmd[last - 1] == '>')
				return (merror(NULL, NULL, "newline", 258));//DEBUG
			else
				return (merror(NULL, NULL, "|", 258));
		}*/ //DEBUG
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
