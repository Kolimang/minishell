/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 03:16:02 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Global var definition (declaration in header file)
int		g_ret_value;

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

int	handle_commands(t_envs *envs, char **cmds, int *i)
{
	t_list		*lexemes;
	t_list		*commands;
	t_command	*command;

	commands = NULL;
	*i = 0;
	while (cmds[*i])
	{
		lexemes = ft_tokenize(cmds[*i]);
		if (!lexemes)
			return (array_str_free(cmds, ft_arraylen(cmds)), 1);
		ft_expand_lexeme_list(lexemes, *(envs->l_env));
		command = ft_parse_lexemes(lexemes, *i, ft_arraylen(cmds));
		if (!command)
			return (g_ret_value);
		if (!commands)
			commands = ft_lstnew(command);
		else
			ft_lstadd_back(&commands, ft_lstnew(command));
		(*i)++;
	}
	array_str_free(cmds, ft_arraylen(cmds));
	free_lexemes(lexemes);
	pre_exec(commands, envs);
	exec(commands, envs);
	free_commands(commands);
	return (0);
}

int	execute(t_envs *envs)
{
	int		i;
	char	*cmd;
	char	**cmds;

	printf("\033[0;38;5;214m === MiNiSHELL === \033[0m\n\n");
	while (1)
	{
		cmd = readline("\033[0;32mminishell$\033[0m ");
		if (!cmd)
			ft_exit(NULL, envs, 1, 0);
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
				array_str_free(cmds, ft_arraylen(cmds));
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
	init_signals();
	if (init_envs(&envs, o_env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//set_shlvl(l_env);
	if (change_term_attr() == 1 || execute(envs) == EXIT_FAILURE)
		return (cleanup_envs(envs, EXIT_FAILURE));
	return (cleanup_envs(envs, EXIT_SUCCESS));
}
