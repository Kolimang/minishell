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

// int	ft_exit(char **args, t_env *env, int eof)
// {
// 	int	argc;
// 	int	ret;

// 	if (eof)
// 		ft_printf("\033[A\033[11C");
// 	ft_printf("exit\n");
// 	ret = 0;
// 	argc = array_len(args);
// 	if (args && args[1] && !arg_is_number(args[1]))
// 	{
// 		g_ret_value = 255;
// 		merror(args[0], args[1], "numeric argument required", 1);
// 	}
// 	if (args && args[1] && arg_is_number(args[1])
// 		&& ft_atoi(args[1]) >= 0)
// 		g_ret_value = ft_atoi(args[1]) % 256;
// 	else if (argc > 2)
// 	{
// 		g_ret_value = 1;
// 		merror(args[0], NULL, "too many arguments", 1);
// 	}
// 	free_arr(args, array_len(args));
// 	free_env(&env);
// 	exit(g_ret_value); // Check if I should really return that value
// }
// version for printinf exit with no pipe

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

int	ft_exit(t_list *cmds, t_envs *envs, int eof, int flag)
{
	char		**args;
	int			argc;
	int			ret;
	t_cmd	*cmd;

	if (eof)
		ft_printf("\033[A\033[11C");
	if (flag == 0)
		ft_printf("exit\n");
	ret = 0;
	args = get_exit_args(cmds);
	argc = array_len(args);
	if (args && args[1] && !arg_is_number(args[1]))
		merror(args[0], args[1], NULL, 22);
	if (args && args[1] && arg_is_number(args[1])
		&& ft_atoi(args[1]) >= 0)
		g_ret_value = ft_atoi(args[1]) % 256;
	else if (argc > 2)
		merror(args[0], NULL, NULL, 13);
	free_commands(cmds);
	cleanup_envs(envs, 0);//free_env(&env);
	exit(g_ret_value);
}
