/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 12:00:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	arg_is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

char **get_exit_args(t_list	*cmds)
{
	t_list		*temp;
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

t_cmd *get_exit_cmd(t_list	*cmds)
{
	t_list		*temp;
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

int	handle_eof(int eof, t_envs *envs)
{
	if (!eof)
		return (0);
	ft_printf("\033[A\033[11C");
	ft_printf("exit\n");
	cleanup_envs(envs, 0);
	exit(g_ret_value);
}

int	ft_exit(t_list *cmds, t_envs *envs, int eof, t_io_fd *io)
{
	char		**args;
	int			argc;
	int			ret;
	t_cmd	*cmd;

	handle_eof(eof, envs);
	cmd = get_exit_cmd(cmds);
	args = get_exit_args(cmds);
	argc = array_len(args);
	if (cmd->eflag == 0)
		ft_printf("exit\n");
	ret = 0;
	if (args && args[1] && !arg_is_number(args[1]))
		merror(args[0], args[1], NULL, 22);
	if (args && args[1] && arg_is_number(args[1])
		&& ft_atoi(args[1]) >= 0)
		g_ret_value = ft_atoi(args[1]) % 256;
	else if (argc > 2)
		merror(args[0], NULL, NULL, 13);
	free_commands(cmds);
	cleanup_envs(envs, 0);
	if (io)
		free(io);
	exit(g_ret_value);
}
