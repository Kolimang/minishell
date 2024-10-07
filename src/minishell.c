/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 11:00:50 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the cmd string is empty, if it is not then it is added to history.
// set SHLVL 
// void	set_shlvl();
// void	ft_add_cmd_to_history(char *cmd)
// {
// 	if (cmd && *cmd)
// 		add_history(cmd);
// }

// int	execute(void)
// {
// 	char	*prompt;
// 	char	*cmd;

// 	printf("\033[0;38;5;214m=== MiNishell v0.1 ===\033[0m\n\n");
// 	prompt = "\033[0;32mminishell>\033[0m";
// 	while (1)
// 	{
// 		cmd = readline(prompt);
// 		printf("Last input: %s\n", cmd);
// 		ft_add_cmd_to_history(cmd);
// 		free(cmd);
// 	}
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	// set_shlvl();
// 	if (execute())
// 		return (execute());
// 	return (0);
// }

//TESTTT pour expander only 
int ret_value = 0;  // Global exit status

void cleanup_lexemes(t_lexems *lexeme)
{
    while (lexeme)
    {
        t_lexems *tmp = lexeme;
        free(lexeme->str);
		free(lexeme->value);
        lexeme = lexeme->next;
        free(tmp);
    }
}

void	ft_printarray(char **lexems)
{
	int	i;

	i = 0;
	while (lexems[i])
	{
		printf("%s\n", lexems[i]);
		i++;
	}
}

void	init_cmd_data(t_cmd_data *data)
{
	data->bool_in_sq = 0;
	data->bool_in_dq = 0;
	data->bool_endq_sep = 0;
	data->bool_endstr = 0;
	data->bool_heredoc = 0;
	data->bool_delimit_tok = 0;
	data->bool_tok_in_progress = 0;
	data->tok_id = 0;
	data->tok_len = 0;
	data->tok_start = 0;
}

int	char_in_set(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_operator(char c) // add dashes (- & --) in the set ?
{
	char	*set;

	set = "<|>";
	return (char_in_set(set, c));
}

t_list	*handle_heredoc(t_cmd_data *dt, char *delim)
{
	char	*hd_input;
	t_list	*hd_tokens;

	hd_tokens = NULL;
	if (dt->bool_heredoc)
	{
		while (1)
		{
			hd_input = readline("\033[0;32mheredoc>\033[0m ");
			if (!hd_input)
			{
				free(hd_input);
				return (NULL);
			}
			if (!hd_tokens)
				hd_tokens = ft_lstnew(hd_input);
			else
			{
				if (!ft_strncmp(hd_input, delim, 3))
					return (hd_tokens);
				ft_lstadd_back(&hd_tokens, ft_lstnew(hd_input));
			}
		}
	}
	return (hd_tokens);
}

void	ft_print_list(t_list *list, char *title)
{
	if (!list)
		return ;
	if (title && title[0] != '\0')
		printf("%s\n", title);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}

char	*find_delim(t_list *tokens)
{
	int	i;

	i = 0;
	while(tokens)
	{
		if ((!ft_strncmp(tokens->content, "<<", 2)) && ft_strlen(tokens->content) == 2)
		{
			return (tokens->next->content);
		}
		tokens = tokens->next;
	}
	return (NULL);
}

t_list	*ft_tokenize(char *cmd)
{
	int			i;
	t_cmd_data	data;
	t_list		*list_lexems;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = 0;
	list_lexems = NULL;
	while (cmd[i])
	{
		handle_operators(cmd, i, &data);
		handle_spaces(cmd, i, &data);
		handle_quotes(cmd, i, &data);
		create_node(cmd, i, &data, &list_lexems);
		i++;
	}
	ft_print_list(handle_heredoc(&data, find_delim(list_lexems)), "--- Heredoc input ---");
	return (list_lexems);
}

int	execute(void)
{
	char	*prompt;
	char	*cmd;
	t_list	*lexems;

	printf("\033[0;38;5;214m=== MiNiSHELL v0.1 ===\033[0m\n\n");
	prompt = "\033[0;32mminishell>\033[0m ";
	while (1)
	{
		cmd = readline(prompt);
		if (!cmd)
			return (1);
		lexems = ft_tokenize(cmd);
		if (!lexems)
		{
			free(cmd);
			return (1);
		}
		ft_print_list(lexems, "--- List of lexems ---");
		ft_add_cmd_to_history(cmd);
		free(cmd);
	}
	return (0);
}

t_lexems *create_lexeme(char *str)
{
    if (!str || !*str)  // Check for NULL or empty string
        return NULL;
    t_lexems *lexeme = ft_calloc(1, sizeof(t_lexems));
    if (!lexeme)  // Check if memory allocation was successful
        return NULL;
    lexeme->str = ft_strdup(str);
    if (!lexeme->str)  // Check if strdup was successful
    {
        free(lexeme);
        return NULL;
    }
    lexeme->next = NULL;
    return lexeme;
}

int main(int ac, char **av, char **o_env)
{
    // Set up a test environment with some example variables
    t_env *env = init_env(o_env);
	(void)ac;
	(void)av;
    // Create a list of lexemes (tokens) for testing
    t_lexems *lexeme1 = create_lexeme("$a");
	printf("%s\n", getenv("PATH"));
    // t_lexems *lexeme2 = create_lexeme("\"$12'USER    '   \"");
    // t_lexems *lexeme3 = create_lexeme("'Literal $USER'");
    // t_lexems *lexeme4 = create_lexeme("Exit code: $?");
    // t_lexems *lexeme5 = create_lexeme("\"Mixed $USER and $? quotes\"");
    
    // Chain lexemes together
    // lexeme1->next = lexeme2;
    // lexeme2->next = lexeme3;
    // lexeme3->next = lexeme4;
    // lexeme4->next = lexeme5;

    // Call expand_lexer on the lexemes with normal expansion flag
	expand_lexer(lexeme1, env, 1);
	// expand_lexer(lexeme2, env, 1);  // Flag 1 for normal expansion
    // Clean up memory
	if(!lexeme1)
		return 1;
	printf("value : %s\n", lexeme1->value);
	printf("str : %s\n", lexeme1->str);
	// printf("lex2 : %s", lexeme2->value);
    cleanup_lexemes(lexeme1);
	//  cleanup_lexemes(lexeme2);
    free_env(env);
    
    return (0);
}
