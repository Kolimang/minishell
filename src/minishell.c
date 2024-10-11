/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/11 15:49:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TESTTT pour expander only 
int	g_ret_value = 0; // Global exit status

void	cleanup_lexemes(t_lexemes *lexeme)
{
	t_lexemes	*tmp;

	while (lexeme)
	{
		tmp = lexeme;
		free(lexeme->str);
		free(lexeme->value);
		lexeme = lexeme->next;
		free(tmp);
	}
}

int	execute(t_env *env)
{
	char	*prompt;
	char	*cmd;
	char	**cmds;
	t_list	*lexemes;
	int		i;

	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
	prompt = "\033[0;32mminishell$\033[0m ";
	while (1)
	{
		cmd = readline(prompt);
		if (!cmd)
			return (1);
		cmd = ft_strtrim(cmd, " "); // memory leak, refaire ca proprement en dupliquant cmd puis free
		if (cmd[0] == '|')
		{
			perror("syntax error near unexpected token `|'"); // un second msg "Undefined error: 0" s'ajoute a l'output
			exit (EXIT_FAILURE); // should probably return promt instead of exiting minishell program entirely ?
		}
		ft_add_cmd_to_history(cmd);
		cmds = ft_split(cmd, '|');
		free(cmd);
		i = 0;
		while (cmds[i])
		{
			lexemes = ft_tokenize(cmds[i]);
			if (!lexemes)
				return (free(cmd), 1); // temp, not complete, must free all commands
			//ft_print_lexemes(lexemes, 1, ' ', "\033[0;33m[command ]\033[0m");
			ft_expand_lexeme_list(lexemes, env);
			//ft_print_lexemes(lexemes, 2, ' ', "\033[0;33m[expanded]\033[0m"); // in place of exec
			t_command	*command;
			command = ft_parse_lexemes(lexemes, i, ft_arraylen(cmds)); // turn lexemes-list into commands-list
			ft_print_command(command);
			// exec
			// free_list or delete_list lexemes
			i++;
		}
	}
	return (0);
}

// hdoc_flag: 1 for normal expansion ; 2 for heredoc expansion
void	ft_expand_lexeme_list(t_list *list, t_env *env)
{
	if (!list)
		return ;
	while (list)
	{
		expand_lexeme(list->content, env);
		list = list->next;
	}
}

t_lexemes	*create_lexeme(char *str)
{
	t_lexemes	*lexeme;

	if (!str || !*str) // Check for NULL or empty string
		return (NULL);
	lexeme = ft_calloc(1, sizeof(t_lexemes));
	if (!lexeme) // Check if memory allocation was successful
		return (NULL);
	lexeme->str = ft_strdup(str);
	if (!lexeme->str) // Check if strdup was successful
	{
		free(lexeme);
		return (NULL);
	}
	lexeme->next = NULL;
	return (lexeme);
}

// env = test environment
int	main(int ac, char **av, char **o_env)
{
	t_env		*env;

	(void)ac;
	(void)av;
	
	g_ret_value = 0;
	env = init_env(o_env);
	//set_shlvl(env);
	if (execute(env))
		return (1);
	free_env(env);
	return (0);
}
