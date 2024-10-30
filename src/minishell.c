/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/30 14:39:17 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Global exit status


// int	ft_check_input_cmd(char **cmdref)
// {
// 	char	last;
// 	char	*cmd;

// 	cmd = ft_strtrim_replace(cmdref);
// 	if ((int)ft_strlen(cmd) > 0)
// 	{
// 		last = cmd[(int)ft_strlen(cmd) - 1];
// 		if (cmd[0] == '|' || last == '|')
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
// 			g_ret_value = 258;
// 			return (-1);
// 		}
// 	}
// 	else if (cmd[0] == '\0')
// 		return (-1);
// 	return (0);
// }

// int	check_commands(char **cmds, int *i)
// {
// 	while (cmds[*i])
// 	{
// 		cmds[*i] = ft_strtrim_replace(&cmds[*i]);
// 		if (!cmds[*i])
// 			return (-1);
// 		if (cmds[*i] && (cmds[*i][0] == '\0'))
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
// 			g_ret_value = 258;
// 			*i = -1;
// 			break ;
// 		}
// 		(*i)++;
// 	}
// 	return (0);
// }

int	handle_commands (t_env *env, int *i, char **g_env)
{
	t_list		*lexemes;
	t_list		*commands;
	t_command	*command;

	commands = NULL;
	*i = 0;
	
	commands = mock_command_line();
	t_command *cmd = commands->content;
	
	pre_exec(commands, env, g_env);
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
// 		i = ft_check_input_cmd(&cmd);
// 		if (i == 0)
// 		{
// 			cmds = ft_split(cmd, '|');
// 			check_commands(cmds, &i);
// 		}
// 		if (i != -1)
// 			handle_commands(cmds, env, &i, g_env);
// 		free(cmd);
// 	}
// 	return (0);
// }

//env = test environment
t_list *mock_command_line(void)
{
    // First command: cat with multiple heredocs
    t_command *cmd1 = malloc(sizeof(t_command));
    cmd1->pid = 0;
    cmd1->argc = 1;
    cmd1->name = strdup("cat");
    cmd1->args = malloc(sizeof(char *) * 2);
    cmd1->args[0] = strdup("cat");
    cmd1->args[1] = NULL;

    // Set up multiple heredocs for cmd1
    t_redir *heredoc_redir1 = malloc(sizeof(t_redir));
    heredoc_redir1->value = strdup("EOF");
    heredoc_redir1->type = HERE_DOC;

    t_redir *redir1 = malloc(sizeof(t_redir));
    redir1->value = strdup("infile1");
    redir1->type = INFILE;
	t_redir *redir2 = malloc(sizeof(t_redir));
    redir2->value = strdup("infile");
    redir2->type = INFILE;
	t_redir *redir3 = malloc(sizeof(t_redir));
    redir3->value = strdup("outfile");
    redir3->type = OUTFILE;
	t_redir *redir4 = malloc(sizeof(t_redir));
    redir4->value = strdup("out");
    redir4->type = OUTFILE;

    t_redir *heredoc_redir3 = malloc(sizeof(t_redir));
    heredoc_redir3->value = strdup("EOF2");
    heredoc_redir3->type = HERE_DOC;

    // Attach heredoc redirections to cmd1
    cmd1->ls_redirs = ft_lstnew(redir1);
	//  cmd1->ls_redirs = ft_lstnew(redir2);
	//  ft_lstadd_back(&(cmd1->ls_redirs), ft_lstnew(heredoc_redir3));
    ft_lstadd_back(&(cmd1->ls_redirs), ft_lstnew(redir3));
    // ft_lstadd_back(&(cmd1->ls_redirs), ft_lstnew(redir2));
	

    cmd1->prevpipe = 0;    // No previous pipe
    cmd1->nextpipe = 0;    // No next pipe
    cmd1->fd_hrdoc = -3;
    cmd1->builtin = 0;

	//second cmd
	t_command *cmd2 = malloc(sizeof(t_command));
    cmd2->pid = 0;
    cmd2->argc = 2;
    cmd2->name = strdup("cat");
    cmd2->args = malloc(sizeof(char *) * 2);
    cmd2->args[0] = strdup("cat");
    cmd2->args[1] = NULL;

    // Set up multiple heredocs for cmd1
    t_redir *heredoc_redir4 = malloc(sizeof(t_redir));
    // heredoc_redir4->value = strdup("EOF");
    // heredoc_redir4->type = HERE_DOC;
	heredoc_redir4->value = strdup("out");
    heredoc_redir4->type = OUTFILE;
	cmd2->prevpipe = 0;    // No previous pipe
    cmd2->nextpipe = 0;    // No next pipe
    cmd2->fd_hrdoc = -3;
    cmd2->builtin = 0;
  	
	// t_redir *redir1 = malloc(sizeof(t_redir));
    // redir1->value = strdup("out");
    // redir1->type = OUTFILE;
	// cmd2->ls_redirs = ft_lstnew(redir1);
	// ft_lstnew(heredoc_redir4);
	// ft_lstadd_back(&(cmd2->ls_redirs), ft_lstnew(heredoc_redir4));
	//Create the linked list of commands
	t_list *commands = ft_lstnew(cmd1);
	
	// ft_lstadd_back(&commands, ft_lstnew(cmd2));
    return commands;
}

int	main(int ac, char **av, char **o_env)
{
	t_env		*env;

	(void)ac;
	(void)av;
	g_ret_value = 0;
	env = init_env(o_env);
	int i;
	//set_shlvl(env);
	// if (execute(env, o_env))
	// {
	// 	free_env(env);
	// 	return (1);
	// }
	handle_commands(env, &i, o_env);
	free_env(env);
	return (0);
}
