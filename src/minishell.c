/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/11 16:55:41 by jrichir          ###   ########.fr       */
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
			return (merror(NULL, NULL, "|", 258)); //return (merror(NULL, NULL, "syntax error near unexpected token `|'", 258));
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
			return (merror(NULL, NULL,
				"syntax error near unexpected token `|'", 258));
		}
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

int	handle_commands(t_env **env, char **cmds, int *i, char **g_env)
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
		ft_expand_lexeme_list(lexemes, *env);
		if (DEBUG) // DEBUG
			ft_print_lexemes(lexemes, 2, ' ', "Lexemes: ");
		command = ft_parse_lexemes(lexemes, *i, ft_arraylen(cmds));
		if (!command)
			return (g_ret_value); // DEBUG
		if (!commands)
			commands = ft_lstnew(command);
		else
			ft_lstadd_back(&commands, ft_lstnew(command));
		if (DEBUG) // DEBUG
			ft_print_command(command);
		(*i)++;
	}
	array_str_free(cmds, ft_arraylen(cmds));
	pre_exec(commands, *env, g_env);
	exec(commands, env, g_env);
	free_lists(lexemes, NULL);// free_lists(lexemes, commands); 
	return (0);
}

int	execute(t_env **env, char**g_env)
{
	int		i;
	char	*cmd;
	char	**cmds;

	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
	//int j = -1;//DEBUG VALGRIND
	//while (++j < 3)//while (1) //DEBUG VALGRIND
	while (1)
	{
		cmd = readline("\033[0;32mminishell$\033[0m ");
		if (!cmd)
			ft_exit(NULL, *env, 1);
		ft_add_cmd_to_history(cmd);
		if (ft_check_input_cmd(&cmd) == EXIT_SUCCESS)
		{
			cmds = ft_split(cmd, '|');
			free(cmd);
			if (!cmds)
				return (EXIT_FAILURE);
			i = 0;
			if (check_commands(cmds, &i) == EXIT_SUCCESS)
				handle_commands(env, cmds, &i, g_env);
			else
				array_str_free(cmds, ft_arraylen(cmds));
			//system("leaks minishell");// works only on MacOS ?
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **o_env)
{
	t_env	*l_env;

	(void)ac;
	(void)av;
	g_ret_value = 0;
	init_signals();
	l_env = init_env(o_env);
	if (!l_env || change_term_attr() == 1)
		return (EXIT_FAILURE);
	//set_shlvl(l_env);
	if (execute(&l_env, o_env) == EXIT_FAILURE)
	{
		free_env(&l_env);
		return (EXIT_FAILURE);
	}
	//handle_commands(env, &i, o_env);
	free_env(&l_env);
	return (EXIT_SUCCESS);
}
