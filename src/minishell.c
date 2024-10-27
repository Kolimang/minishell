/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 20:35:00 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_input_cmd(char **cmdref)
{
	char	last;
	char	*cmd;

	cmd = ft_strtrim_replace(cmdref);
	if ((int)ft_strlen(cmd) > 0)
	{
		last = cmd[(int)ft_strlen(cmd) - 1];
		if (cmd[0] == '|' || last == '|')
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_ret_value = 258;
			return (-1);
		}
	}
	else if (cmd[0] == '\0')
		return (-1);
	return (0);
}

int	check_commands(char **cmds, int *i)
{
	while (cmds[*i])
	{
		cmds[*i] = ft_strtrim_replace(&cmds[*i]);
		if (!cmds[*i])
			return (-1);
		if (cmds[*i] && (cmds[*i][0] == '\0'))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_ret_value = 258;
			*i = -1;
			break ;
		}
		(*i)++;
	}
	return (0);
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
		ft_printf("cmd[%d]: %s\n", *i, cmds[*i]);
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

t_list *mock_command_line(void)
{
    t_list *commands = NULL;
    t_command *cmd1, *cmd2, *cmd3;
    t_redir *redir;

    // First command: echo test
    cmd1 = malloc(sizeof(t_command));
    cmd1->pid = 0;
    cmd1->argc = 2;
    cmd1->name = strdup("echo");
    cmd1->args = malloc(sizeof(char *) * 3);
    cmd1->args[0] = strdup("echo");
    cmd1->args[1] = strdup("test");
    cmd1->args[2] = NULL;
    cmd1->ls_redirs = NULL;
    cmd1->prevpipe = 0;    // No previous pipe
    cmd1->nextpipe = 1;    // Has next pipe
    cmd1->fd_hrdoc = -1;
    cmd1->builtin = ECHO;

    // Second command: ls -l
    cmd2 = malloc(sizeof(t_command));
    cmd2->pid = 0;
    cmd2->argc = 2;
    cmd2->name = strdup("ls");
    cmd2->args = malloc(sizeof(char *) * 3);
    cmd2->args[0] = strdup("ls");
    cmd2->args[1] = strdup("-l");
    cmd2->args[2] = NULL;
    cmd2->ls_redirs = NULL;
    cmd2->prevpipe = 1;    // Has previous pipe
    cmd2->nextpipe = 1;    // Has next pipe
    cmd2->fd_hrdoc = -1;
    cmd2->builtin = 0;

    // Third command: cat > output.txt
    cmd3 = malloc(sizeof(t_command));
    cmd3->pid = 0;
    cmd3->argc = 1;
    cmd3->name = strdup("cat");
    cmd3->args = malloc(sizeof(char *) * 2);
    cmd3->args[0] = strdup("cat");
    cmd3->args[1] = NULL;
    
    // Add redirection for cmd3
    redir = malloc(sizeof(t_redir));
    redir->value = strdup("output.txt");
    redir->type = OUTFILE;  // Assuming this is your enum for '>'
    cmd3->ls_redirs = ft_lstnew(redir);
    
    cmd3->prevpipe = 1;    // Has previous pipe
    cmd3->nextpipe = 0;    // No next pipe
    cmd3->fd_hrdoc = -1;
    cmd3->builtin = 0;

    // Create linked list
    commands = ft_lstnew(cmd1);
    ft_lstadd_back(&commands, ft_lstnew(cmd2));
    ft_lstadd_back(&commands, ft_lstnew(cmd3));

    return (commands);
}

// for testing builtins:
// int	execute(t_env *env)
// {
// 	char	**args;
// 	char	*cmd;
// 	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
// 	while (1)
// 	{
// 		cmd = readline("\033[0;32mminishell$\033[0m ");
// 		if (!cmd)
// 			return (1);
// 		args = ft_split(cmd, ' ');
// 		if (!ft_strncmp(args[0], "cd", 3))
// 			ft_cd(args, env);
// 		else if (!ft_strncmp(args[0], "echo", 5))
// 			ft_echo(args);
// 		else if (!ft_strncmp(args[0], "pwd", 4))
// 			ft_pwd(args, env);
// 		else if (!ft_strncmp(args[0], "export", 7))
// 			ft_export(args, env);
// 		free(args);
// 	}
// 	return (0);
// }

int	execute(t_env *env, char**g_env)
{
	int			i;
	char		*cmd;
	char		**cmds;

	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
	while (1)
	{
		cmd = readline("\033[0;32mminishell$\033[0m ");
		if (!cmd)
			return (1);
		ft_add_cmd_to_history(cmd);
		i = ft_check_input_cmd(&cmd);
		if (i == 0)
		{
			cmds = ft_split(cmd, '|');
			check_commands(cmds, &i);
		}
		if (i != -1)
			handle_commands(env, cmds, &i, g_env);
		free(cmd);
	}
	return (0);
}

//env = test environment
int	main(int ac, char **av, char **o_env)
{
	t_env		*env;

	(void)ac;
	(void)av;
	g_ret_value = 0;
	env = init_env(o_env);
	int i;
	//set_shlvl(env);
	if (execute(env, o_env))
	{
		free_env(env);
		return (1);
	}
	//handle_commands(env, &i, o_env);
	free_env(env);
	return (0);
}
