/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/03 13:31:17 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Global var definition
int		g_ret_val;

void	the_execution(t_list *commands, t_envs *envs)
{
	pre_exec(commands, envs);
	exec(commands, envs);
	free_commands(commands);
}

int	handle_commands(t_envs *envs, char **cmds, int *i)
{
	t_list	*lxms;
	t_list	*commands;
	t_cmd	*command;

	commands = NULL;
	*i = 0;
	while (cmds[*i])
	{
		lxms = ft_tokenize(cmds[*i]);
		if (!lxms)
			return (free_arr(cmds, array_len(cmds)), 1);
		command = ft_parse_lexemes(lxms, *i, array_len(cmds), *(envs->l_env));
		free_ls(lxms);
		if (!command)
			return (free_arr(cmds, array_len(cmds)), g_ret_val);
		if (!commands)
			commands = ft_lstnew(command);
		else
			ft_lstadd_back(&commands, ft_lstnew(command));
		(*i)++;
	}
	free_arr(cmds, array_len(cmds));
	the_execution(commands, envs);
	return (0);
}

int	minishell(t_envs *envs)
{
	int		i;
	char	*cmd;
	char	**cmds;

	while (1)
	{
		set_signals_parent();
		cmd = readline("\001\033[0;32m\002minishell$\001\033[0m\002 ");
		if (!cmd)
			ft_exit(NULL, envs, 1, NULL);
		ft_add_cmd_to_history(cmd);
		if (ft_check_input_cmd(&cmd) == EXIT_SUCCESS)
		{
			cmds = cmd_split(cmd);
			free(cmd);
			if (!cmds)
				return (EXIT_FAILURE);
			i = 0;
			if (check_commands(cmds, &i) == EXIT_SUCCESS)
				handle_commands(envs, cmds, &i);
			else
				free_arr(cmds, array_len(cmds));
		}
	}
	return (EXIT_SUCCESS);
}

int	init_envs(t_envs **envs, char **o_env)
{
	*envs = malloc(sizeof(t_envs));
	if (!*envs)
		return (EXIT_FAILURE);
	(*envs)->g_env = o_env;
	(*envs)->l_env = malloc(sizeof(t_env *));
	if (!(*envs)->l_env)
	{
		free(*envs);
		return (EXIT_FAILURE);
	}
	*((*envs)->l_env) = init_env(o_env);
	if (!(*envs)->l_env)
	{
		free(*envs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **o_env)
{
	t_envs	*envs;

	(void)ac;
	(void)av;
	g_ret_val = 0;
	if (init_envs(&envs, o_env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_shlvl(envs->l_env);
	if (change_term_attr() == 1 || minishell(envs) == EXIT_FAILURE)
		return (cleanup_envs(envs, EXIT_FAILURE));
	return (cleanup_envs(envs, EXIT_SUCCESS));
}
