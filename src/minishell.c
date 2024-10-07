/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 16:16:34 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
