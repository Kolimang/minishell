/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 12:00:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Global var definition
int		g_ret_value;

void	the_execution(t_list *commands, t_envs *envs)
{
	pre_exec(commands, envs);
	exec(commands, envs);
	free_commands(commands);
}

int	handle_commands(t_envs *envs, char **cmds, int *i)
{
	t_list		*lexemes;
	t_list		*commands;
	t_cmd	*command;

	commands = NULL;
	*i = 0;
	while (cmds[*i])
	{
		lexemes = ft_tokenize(cmds[*i]);
		if (!lexemes)
			return (free_arr(cmds, array_len(cmds)), 1);
		ft_expand_lexeme_list(lexemes, *(envs->l_env));
		command = ft_parse_lexemes(lexemes, *i, array_len(cmds));
		if (!command)
			return (free_lexemes(lexemes), free_arr(cmds, array_len(cmds)), g_ret_value);
		if (!commands)
			commands = ft_lstnew(command);
		else
			ft_lstadd_back(&commands, ft_lstnew(command));
		free_lexemes(lexemes);
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
		signal(SIGINT, sig_handler_main);
		cmd = readline("\033[0;32mminishell$\033[0m ");
		if (!cmd)
			ft_exit(NULL, envs, 1, NULL);
		ft_add_cmd_to_history(cmd);
		if (ft_check_input_cmd(&cmd) == EXIT_SUCCESS)
		{
			cmds = ft_split(cmd, '|');
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
	g_ret_value = 0;
	signal(SIGQUIT, SIG_IGN);
	if (init_envs(&envs, o_env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_shlvl(envs->l_env);
	if (change_term_attr() == 1 || minishell(envs) == EXIT_FAILURE)
		return (cleanup_envs(envs, EXIT_FAILURE));
	return (cleanup_envs(envs, EXIT_SUCCESS));
}
