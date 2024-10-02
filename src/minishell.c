/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/02 18:08:33 by lboumahd         ###   ########.fr       */
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

// Helper function to create a new lexeme
t_lexems *create_lexeme(char *str)
{
    t_lexems *lexeme = ft_calloc(1, sizeof(t_lexems));
    if (!lexeme)
        return NULL;
    lexeme->str = ft_strdup(str);
    lexeme->next = NULL;
    return lexeme;
}

// Helper function to set up test environment variables
t_env *setup_env()
{
    t_env *env = ft_calloc(1, sizeof(t_env));
    
    // Example: Add USER="user_value" to environment
    env->var_name = ft_strdup("\"$\'USER\'\"");
    env->var_val = ft_strdup("user_value");
    env->next = ft_calloc(1, sizeof(t_env));
    
    // Add PATH="/usr/bin" to environment
    env->next->var_name = ft_strdup("PATH");
    env->next->var_val = ft_strdup("/usr/bin");
    env->next->next = NULL; // Terminate the list
    
    return env;
}

// Simple cleanup for environment
void cleanup_env(t_env *env)
{
    while (env)
    {
        t_env *tmp = env;
        free(env->var_name);
        free(env->var_val);
        env = env->next;
        free(tmp);
    }
}

// Simple cleanup for lexemes
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

int main(void)
{
    // Set up a test environment with some example variables
    t_env *env = setup_env();

    // Create a list of lexemes (tokens) for testing
    t_lexems *lexeme1 = create_lexeme("'$?'");
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
	printf("value : %s\n", lexeme1->value);
	printf("str : %s\n", lexeme1->str);
	// printf("lex2 : %s", lexeme2->value);
    cleanup_lexemes(lexeme1);
	//  cleanup_lexemes(lexeme2);
    cleanup_env(env);
    
    return 0;
}
