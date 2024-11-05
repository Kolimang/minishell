/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/05 12:38:57 by jrichir          ###   ########.fr       */
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
		command = ft_parse_lexemes(lexemes, *i, ft_arraylen(cmds));
		if (!command)
			return (g_ret_value);
		if (!commands)
			commands = ft_lstnew(command);
		else
			ft_lstadd_back(&commands, ft_lstnew(command));
		// DEBUG
		ft_print_command(command);
		(*i)++;
	}
	pre_exec(commands, *env, g_env);
	exec(commands, env, g_env);
	// array_str_free(cmds, ft_arraylen(cmds));
	// free_lists(lexemes, commands);
	return (0);
}
// t_list *mock_command_line(void)
// {
//     t_list *commands = NULL;
//     t_command *cmd1, *cmd2, *cmd3;
//     t_redir *redir;

//     // First command: echo test
//     // cmd1 = malloc(sizeof(t_command));
//     // cmd1->pid = 0;
//     // cmd1->argc = 2;
//     // cmd1->name = strdup("echo");
//     // cmd1->args = malloc(sizeof(char *) * 3);
//     // cmd1->args[0] = strdup("echo");
//     // cmd1->args[1] = strdup("test");
//     // cmd1->args[2] = NULL;
//     // cmd1->ls_redirs = NULL;
//     // cmd1->prevpipe = 0;    // No previous pipe
//     // cmd1->nextpipe = 0;    // Has next pipe
//     // cmd1->fd_hrdoc = -1;
//     // cmd1->builtin = ECHO;

//     // Second command: ls -l
//     cmd2 = malloc(sizeof(t_command));
//     cmd2->pid = 0;
//     cmd2->argc = 2;
//     cmd2->name = strdup("ls");
//     cmd2->args = malloc(sizeof(char *) * 3);
//     cmd2->args[0] = strdup("ls");
//     cmd2->args[1] = strdup("-l");
//     cmd2->args[2] = NULL;
//     cmd2->ls_redirs = NULL;
//     cmd2->prevpipe = 0;    // Has previous pipe
//     cmd2->nextpipe = 1;    // Has next pipe
//     cmd2->fd_hrdoc = -3;
//     cmd2->builtin = 0;

//     // // Third command: cat > output.txt
//     cmd3 = malloc(sizeof(t_command));
//     // cmd3->pid = 0;
//     cmd3->argc = 1;
//     cmd3->name = strdup("grep");
//     cmd3->args = malloc(sizeof(char *) * 2);
//     cmd3->args[0] = strdup("grep");
//     cmd3->args[1] = "hey";
	
//     // // Add redirection for cmd3
//     redir = malloc(sizeof(t_redir));

//     redir->value = strdup("output.txt");
//     redir->type = OUTFILE;  // Assuming this is your enum for '>'
//     cmd3->ls_redirs = ft_lstnew(redir);
//     cmd3->prevpipe = 1;    // Has previous pipe
//     cmd3->nextpipe = 0;    // No next pipe
//     cmd3->fd_hrdoc = -3;
//     cmd3->builtin = 0;
//     // // Create linked list
//     commands = ft_lstnew(cmd2);
//     ft_lstadd_back(&commands, ft_lstnew(cmd3));
//     // ft_lstadd_back(&commands, ft_lstnew(cmd3));

//     return (commands);
// }
// t_list *mock_command_line(void)
// {
// t_command *cmd1 = malloc(sizeof(t_command));
// cmd1->pid = 0;
// cmd1->argc = 1;
// cmd1->name = strdup("cat");
// cmd1->args = malloc(sizeof(char *) * 2);
// cmd1->args[0] = strdup("cat");
// cmd1->args[1] = NULL;

// // Set up heredoc for cmd1
// t_redir *heredoc_redir = malloc(sizeof(t_redir));
// heredoc_redir->value = strdup("EOF"); // This is the delimiter for the heredoc
// heredoc_redir->type = HERE_DOC;   

// t_redir *heredoc_redir2 = malloc(sizeof(t_redir));
// heredoc_redir2->value = strdup("EOF1"); // This is the delimiter for the heredoc
// heredoc_redir2->type = HERE_DOC;      // Assuming this is the enum/type for heredoc redirection

// // Attach heredoc redirection to cmd1
// cmd1->ls_redirs = ft_lstnew(heredoc_redir);
// cmd1->prevpipe = 0;    // No previous pipe
// cmd1->nextpipe = 0;    // Has next pipe
// cmd1->fd_hrdoc = -3;
// cmd1->builtin = 0;

// ft_lstadd_back(&(cmd1->ls_redirs), ft_lstnew(heredoc_redir2));
// // Second command: grep "hey"
// // t_command *cmd2 = malloc(sizeof(t_command));
// // cmd2->pid = 0;
// // cmd2->argc = 2;
// // cmd2->name = strdup("grep");
// // cmd2->args = malloc(sizeof(char *) * 3);
// // cmd2->args[0] = strdup("grep");
// // cmd2->args[1] = strdup("hey");
// // cmd2->args[2] = NULL;
// // cmd2->ls_redirs = NULL;
// // cmd2->prevpipe = 1;    // Has previous pipe
// // cmd2->nextpipe = 1;    // Has next pipe
// // cmd2->fd_hrdoc = -3;
// // cmd2->builtin = 0;

// // // Third command: sort > outfile
// // t_command *cmd3 = malloc(sizeof(t_command));
// // cmd3->pid = 0;
// // cmd3->argc = 1;
// // cmd3->name = strdup("ls");
// // cmd3->args = malloc(sizeof(char *) * 2);
// // cmd3->args[0] = strdup("ls");
// // cmd3->args[1] = NULL;

// // // Set up output redirection for cmd3 to outfile
// // t_redir *outfile_redir = malloc(sizeof(t_redir));
// // outfile_redir->value = strdup("outfile");
// // outfile_redir->type = OUTFILE;  // Assuming this is the enum/type for output redirection '>'

// // // Attach output redirection to cmd3
// // cmd3->ls_redirs = ft_lstnew(outfile_redir);
// // cmd3->prevpipe = 1;    // Has previous pipe
// // cmd3->nextpipe = 0;    // No next pipe
// // cmd3->fd_hrdoc = -3;
// // cmd3->builtin = 0;

// // Create the linked list of commands
// t_list *commands = ft_lstnew(cmd1);
// // ft_lstadd_back(&commands, ft_lstnew(cmd2));
// // ft_lstadd_back(&commands, ft_lstnew(cmd3));

// return commands;
// }

// for testing builtins:
// int	execute(t_env **env, char **g_env)
// {
// 	char	**args;
// 	char	*cmd;
// 	(void)g_env;
// 	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
// 	while (1)
// 	{
// 		cmd = readline("\033[0;32mminishell$\033[0m ");
// 		if (!cmd)
// 			ft_exit(NULL, *env, 1);
// 		ft_add_cmd_to_history(cmd);
// 		args = ft_split(cmd, ' ');
// 		if (!args)
// 			return (EXIT_FAILURE);
// 		if (!ft_strncmp(args[0], "cd", 3))
// 			ft_cd(args, *env);
// 		else if (!ft_strncmp(args[0], "echo", 5))
// 			ft_echo(args);
// 		else if (!ft_strncmp(args[0], "pwd", 4))
// 			ft_pwd(args, *env);
// 		else if (!ft_strncmp(args[0], "export", 7))
// 			ft_export(args, env);
// 		else if (!ft_strncmp(args[0], "env", 4))
// 			ft_env(args, *env);
// 		else if (!ft_strncmp(args[0], "unset", 6))
// 			ft_unset(args, env);
// 		else if (!ft_strncmp(args[0], "exit", 5))
// 			ft_exit(args, *env, 0);
// 		array_str_free(args, ft_arraylen(args));
// 		free(cmd);
// 	}
// 	return (0);
// }

int	execute(t_env **env, char**g_env)
{
	int			i;
	char		*cmd;
	char		**cmds;

	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
	while (1)
	{
		cmd = readline("\033[0;32mminishell$\033[0m ");
		if (!cmd)
			ft_exit(NULL, *env, 1);
		ft_add_cmd_to_history(cmd);
		if (ft_check_input_cmd(&cmd) == EXIT_SUCCESS)
		{
			cmds = ft_split(cmd, '|');
			if (!cmds)
				return (EXIT_FAILURE);
			if (check_commands(cmds, &i) == EXIT_SUCCESS)
				handle_commands(env, cmds, &i, g_env);
			else
				array_str_free(cmds, ft_arraylen(cmds));
		}
		free(cmd);
	}
	return (EXIT_SUCCESS);
}
/*
t_list *mock_command_line(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    cmd->pid = 0;
    cmd->argc = 1;
    cmd->name = strdup("cat");
    cmd->args = malloc(sizeof(char *) * 2);
    cmd->args[0] = strdup("cat");
    cmd->args[1] = NULL;
	cmd->prevpipe = 0;
    cmd->nextpipe = 1;
    cmd->fd_hrdoc = -3;
    cmd->builtin = 0;

    // Set up infile redirection
    t_redir *redir_infile2 = malloc(sizeof(t_redir));
    redir_infile2->value = strdup("infile2");
    redir_infile2->type = INFILE;

    t_redir *redir_infile1 = malloc(sizeof(t_redir)); // Allocate new memory
    redir_infile1->value = strdup("infile1");
    redir_infile1->type = INFILE;
	  t_redir *redir_infile3 = malloc(sizeof(t_redir)); // Allocate new memory
    redir_infile3->value = strdup("infile3");
    redir_infile3->type = INFILE;

    // Set up heredoc redirection
    t_redir *redir_heredoc = malloc(sizeof(t_redir));
    redir_heredoc->value = strdup("EOF");
    redir_heredoc->type = HERE_DOC;

 t_redir *redir_heredoc2 = malloc(sizeof(t_redir));
    redir_heredoc2->value = strdup("EOF2");
    redir_heredoc2->type = HERE_DOC;
    // Set up outfile redirection
    t_redir *redir_outfile = malloc(sizeof(t_redir));
    redir_outfile->value = strdup("outfile");
    redir_outfile->type = OUTFILE;

    t_redir *redir_outfile2 = malloc(sizeof(t_redir));
    redir_outfile2->value = strdup("outfile2");
    redir_outfile2->type =OUTFILE;

    cmd->ls_redirs = ft_lstnew(redir_infile2);
    // ft_lstadd_back(&(cmd->ls_redirs), ft_lstnew(redir_infile1));
	// ft_lstadd_back(&(cmd->ls_redirs), ft_lstnew(redir_outfile2)); 
	// ft_lstadd_back(&(cmd->ls_redirs),ft_lstnew(redir_heredoc));// < infile1
	ft_lstadd_back(&(cmd->ls_redirs), ft_lstnew(redir_outfile));
	
	t_command *cmd2 = malloc(sizeof(t_command));
    cmd2->pid = 0;
    cmd2->argc = 1;
    cmd2->name = strdup("cat");
    cmd2->args = malloc(sizeof(char *) * 2);
    cmd2->args[0] = strdup("cat");
    cmd2->args[1] = NULL;
	cmd2->prevpipe = 1;
    cmd2->nextpipe = 1;
    cmd2->fd_hrdoc = -3;
    cmd2->builtin = 0;

	cmd2->ls_redirs = ft_lstnew(redir_infile2);
	ft_lstadd_back(&(cmd2->ls_redirs),ft_lstnew(redir_heredoc2));
	// ft_lstadd_back(&(cmd2->ls_redirs), ft_lstnew(redir_outfile2));
	t_command *cmd3 = malloc(sizeof(t_command));
    cmd3->pid = 0;
    cmd3->pid = 0;
    cmd3->argc = 1;
    cmd3->name = strdup("cat");
    cmd3->args = malloc(sizeof(char *) * 2);
    cmd3->args[0] = strdup("cat");
    cmd3->args[1] = NULL;
	cmd3->prevpipe = 1;
    cmd3->nextpipe = 0;
    cmd3->fd_hrdoc = -3;
    cmd3->builtin = 1;

	cmd3->ls_redirs = ft_lstnew(redir_outfile2);
	// ft_lstadd_back(&(cmd3->ls_redirs),ft_lstnew(redir_outfile2));	
    t_list *commands = ft_lstnew(cmd);
	ft_lstadd_back(&commands, ft_lstnew(cmd2));
	ft_lstadd_back(&commands, ft_lstnew(cmd3));
    return commands;
}
*/

int	main(int ac, char **av, char **o_env)
{
	t_env		*l_env;

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
		free_env(l_env);
		return (EXIT_FAILURE);
	}
	//handle_commands(env, &i, o_env);
	free_env(l_env);
	return (EXIT_SUCCESS);
}
