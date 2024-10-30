/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/30 09:35:26 by jrichir          ###   ########.fr       */
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
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_ret_value = 258;
			return (EXIT_FAILURE);
		}
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
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_ret_value = 258;
			*i = -1;
			return (EXIT_FAILURE);
		}
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

int	handle_commands(t_env *env, char **cmds, int *i, char **g_env)
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
		ft_expand_lexeme_list(lexemes, env);
		command = ft_parse_lexemes(lexemes, *i, ft_arraylen(cmds));
		if (!commands)
			commands = ft_lstnew(command);
		else
			ft_lstadd_back(&commands, ft_lstnew(command));
		(*i)++;
	}
	pre_exec(commands, env, g_env);
	exec(commands, env, g_env);
	// array_str_free(cmds, ft_arraylen(cmds));
	// free_lists(lexemes, commands);
	return (0);
}
// t_list *mock_command_line(void)
// {
// t_command *cmd1 = malloc(sizeof(t_command));
// cmd1->pid = 0;
// cmd1->argc = 1;
// cmd1->name = strdup("cat");
// cmd1->args = malloc(sizeof(char *) * 2);
// cmd1->args[0] = strdup("cat");
// cmd1->args[1] = NULL;

// Set up heredoc for cmd1
// t_redir *heredoc_redir = malloc(sizeof(t_redir));
// heredoc_redir->value = strdup("EOF"); // This is the delimiter for the heredoc
// heredoc_redir->type = HERE_DOC;        // Assuming this is the enum/type for heredoc redirection

// Attach heredoc redirection to cmd1
// cmd1->ls_redirs = ft_lstnew(heredoc_redir);
// cmd1->prevpipe = 0;    // No previous pipe
// cmd1->nextpipe = 0;    // Has next pipe
// cmd1->fd_hrdoc = -3;
// cmd1->builtin = 0;

// Second command: grep "hey"
// t_command *cmd2 = malloc(sizeof(t_command));
// cmd2->pid = 0;
// cmd2->argc = 2;
// cmd2->name = strdup("grep");
// cmd2->args = malloc(sizeof(char *) * 3);
// cmd2->args[0] = strdup("grep");
// cmd2->args[1] = strdup("hey");
// cmd2->args[2] = NULL;
// cmd2->ls_redirs = NULL;
// cmd2->prevpipe = 1;    // Has previous pipe
// cmd2->nextpipe = 1;    // Has next pipe
// cmd2->fd_hrdoc = -3;
// cmd2->builtin = 0;

// for testing builtins:
int	execute(t_env **env, char **g_env)
{
	char	**args;
	char	*cmd;
	(void)g_env;
	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
	while (1)
	{
		cmd = readline("\033[0;32mminishell$\033[0m ");
		if (!cmd)
			ft_exit(NULL, *env);//return (EXIT_FAILURE);
		ft_add_cmd_to_history(cmd);
		args = ft_split(cmd, ' ');
		if (!args)
			return (EXIT_FAILURE);
		if (!ft_strncmp(args[0], "cd", 3))
			ft_cd(args, *env);
		else if (!ft_strncmp(args[0], "echo", 5))
			ft_echo(args);
		else if (!ft_strncmp(args[0], "pwd", 4))
			ft_pwd(args, *env);
		else if (!ft_strncmp(args[0], "export", 7))
			ft_export(args, env);
		else if (!ft_strncmp(args[0], "env", 4))
			ft_env(args, *env);
		else if (!ft_strncmp(args[0], "unset", 6))
			ft_unset(args, env);
		else if (!ft_strncmp(args[0], "exit", 5))
			ft_exit(args, *env);
		array_str_free(args, ft_arraylen(args));
		free(cmd);
	}
	return (0);
}

// int	execute(t_env *env, char**g_env)
// {
// 	int			i;
// 	char		*cmd;
// 	char		**cmds;

// 	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
// 	while (1)
// 	{
// 		cmd = readline("\033[0;32mminishell$\033[0m ");
// 		if (!cmd)
// 			return (1);
// 		ft_add_cmd_to_history(cmd);
// 		if (ft_check_input_cmd(&cmd) == EXIT_SUCCESS)
// 		{
// 			cmds = ft_split(cmd, '|');
// 			if (!cmds)
// 				return (EXIT_FAILURE);
// 			if (check_commands(cmds, &i) == EXIT_SUCCESS)
// 				handle_commands(env, cmds, &i, g_env);
// 			else
// 				array_str_free(cmds, ft_arraylen(cmds));
// 		}
// 		free(cmd);
// 	}
// 	return (EXIT_SUCCESS);
// }

//env = test environment
int	main(int ac, char **av, char **o_env)
{
	t_env	*env;

	(void)ac;
	(void)av;
	g_ret_value = 0;
	init_signals();
	env = init_env(o_env);
	if (!env)
		return (1);
	//set_shlvl(env);
	if (execute(&env, o_env) == EXIT_FAILURE)
	{
		free_env(env);
		return (EXIT_FAILURE);
	}
	//handle_commands(env, &i, o_env);
	free_env(env);
	return (EXIT_SUCCESS);
}
