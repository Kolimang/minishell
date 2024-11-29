/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/29 16:08:23 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	arg_is_number(char *arg)
{
	int	i;

	i = 0;
	if (!char_in_set("+-", arg[i]) && !ft_isdigit(arg[i]))
		return (0);
	i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

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

t_cmd	*get_exit_cmd(t_list	*cmds)
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

int	handle_eof(int eof, t_envs *envs)
{
	if (!eof)
		return (0);
	ft_printf("\033[A\033[11C");
	ft_printf("exit\n");
	cleanup_envs(envs, 0);
	exit(g_ret_val);
}

void	get_ret_value(char *arg)
{
	int	nb = ft_atoi(arg);

	if (nb >= 0)
		g_ret_val = nb % 256;
	else
		g_ret_val = (256 + nb) % 256;
}

int	ft_exit(t_list *cmds, t_envs *envs, int eof, t_io_fd *io)
{
	char	**args;
	int		argc;
	t_cmd	*cmd;

	handle_eof(eof, envs);
	cmd = get_exit_cmd(cmds);
	args = get_exit_args(cmds);
	argc = array_len(args);
	if (cmd->eflag == 0)
		ft_printf("exit\n");
	if (args && args[1] && !arg_is_number(args[1]))
		merror(args[0], args[1], NULL, 22);
	else if (argc > 2)
		return (merror(args[0], NULL, NULL, 13));
	if (args && args[1] && arg_is_number(args[1]))
		get_ret_value(args[1]);
	free_commands(cmds);
	cleanup_envs(envs, 0);
	rl_clear_history();
	if (io)
		free(io);
	exit(g_ret_val);
}
