/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/01 18:45:00 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//WHAT TO DO WHEN !str , NULL of EXIT_FAILURE??


void handle_SQ(char **res, char *tmp, int *i)
{
	(*i)++;
	int start = *i; 
    while (tmp[*i]) 
    {
        if (tmp[*i] == SQ) 
        {
            append_to_str(res, tmp, *i, start); 
            (*i)++; 
            return; // Exit the function
        }
        (*i)++; // Increment the index
    }
	free(res);
    fprintf(stderr, "Error: No closing single quote found.\n"); 
    exit(EXIT_FAILURE); // Exit if no closing quote is found
}


void handle_DQ(char **res, char *tmp, int *i, t_env *new_env) {
    int start = 0;
    (*i)++; // Move past the opening double quote

    while (tmp[*i]) {
        start = *i;
        // Append characters until reaching a closing double quote or $
        while (tmp[*i] != DQ && tmp[*i]) 
           { // If we encounter $, check if the next character is not a single quote
	
			if (tmp[*i] == '$' && tmp[*i + 1] != '\'') 
                break; 
             (*i)++; 
       		}
       
        if (tmp[*i] == DQ) {
            append_to_str(res, tmp, *i, start);
            (*i)++;
            return; 
        }
        if (tmp[*i] == '$') {
			append_to_str(res, tmp, *i, start);
            expander(res, tmp, i, new_env);
        }
    }
	if(res)
		free(res);
	//ATTTENNNNNTIONNNNNNNNNN FPRINTF
    fprintf(stderr, "Error: No closing double quote found.\n");
    exit(EXIT_FAILURE); // Handle the error as needed
}

char	*handle_exp(char *tmp, t_lexems *lexeme, t_env *new_env)
{
	char	*res;
	char	*final_res;
	int i;
	(void)lexeme;
	res = ft_calloc(sizeof(char), 1);
	final_res = ft_calloc(sizeof(char), 1);
	i = 0;
	while(tmp[i])
	{
		if(tmp[i] == SQ)
			handle_SQ(&res, tmp, &i);
		else if(tmp[i] == DQ)
			handle_DQ(&res, tmp, &i, new_env);
		else
			handle_NQ(&res, tmp, &i, new_env, &lexeme); //si on rajoute le lexer apres le parseur 
		// printf("str original: %s\n", res);
		final_res = ft_strjoin(final_res, res);
		free(res);
	}
	return(final_res);
} 

void process_regular(t_lexems *lexeme, t_env *new_env)
{
    char *tmp = 0;
    char *clean_str = 0;

    if (!lexeme || lexeme->str == NULL)
        exit(EXIT_FAILURE);
    tmp = ft_strdup(lexeme->str);
    if (!tmp)
        exit(EXIT_FAILURE);
    clean_str = handle_exp(tmp, lexeme, new_env);
    if (lexeme->value)
        free(lexeme->value);
    lexeme->value = ft_strdup(clean_str); 
    free(tmp);       
    free(clean_str);  
}

void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag)
{
    while(lexeme)
	{
		if (flag == 1)  // Normal exp case
			process_regular(lexeme, new_env);
    	// else
		// 	process_HRDOC(lexeme);
		if(lexeme)
			lexeme = lexeme->next;
	//error ?? 
}
}

void	expander(char **res, char *tmp, int *i, t_env *new_env)
{
	int start;
	char *var = 0;
	char *exit_code_str;
	(void) new_env;
	
	(*i)++;
	start = *i;
	if((tmp[start] == ' ') ||(tmp[start] == '\0') || (tmp[start] == DQ))
		return(append_to_str(res, tmp, *i , start - 1));
	else if(ft_isdigit(tmp[*i]))//digit 0 - 9 -> skip num then append to str
		{
			while(tmp[*i] && tmp[*i] != DQ && tmp[*i] != ' ')
				(*i)++;
			return(append_to_str(res, tmp, *i, start + 1));
		}
	else if (tmp[*i] == '?') //mise a jour du code d erreur 
	{
		exit_code_str = ft_itoa(ret_value); 
		*res = ft_strjoin(*res, exit_code_str);   
		free(exit_code_str);                                                 // Move past the '?'
		(*i)++;
		return; //move pat the ? 
	}// find exit error 
	else
	{ ///BUUUG  = SEGmentation fault 
		while(ft_isalnum(tmp[*i]))
			(*i)++;
		append_to_str(&var, tmp, *i, start);
		if(getenv(var))
			*res = ft_strjoin(*res, getenv(var)); //GET THE REAL VALUEEE
		else 
			*res = ft_strjoin("", *res);
		return;
	}	
}


// char	*find_var(char *var, t_env *new_env) //getenv
// {
// 	while(new_env) // determiner le new_env structu
// 	{
// 		if (ft_strncmp(new_env->var_name, var, ft_strlen(var) + 1) == 0)
// 		{	
// 			var = new_env->var_val;
// 			return(var);
// 		}
// 		new_env = new_env->next;
// 	}
// 	return (NULL);
// }

// char	*replace_var(char *tmp, int *i, int start, t_env *new_env)
// {
// 	char *var;

// 	while(ft_isalnum(tmp[*i]))
// 		i++;
// 	var = malloc(*i - start + 1);
// 	if(!var)
// 		return (NULL);
// 	ft_strlcpy(var, tmp, *i - start + 1);
// 	var = find_var(var, new_env);//if not found return NULL
// 	return(var);
// }
// oblige de rajouter un espace
// void append_to_str(char **res, char *tmp, int end, int start)
// {
//     char *new_part;
//     // char *new_res;

//     new_part = malloc((end - start + 1) * sizeof(char)); 
//     if (!new_part)
//         return;
//     ft_strlcpy(new_part, tmp + start, end - start + 1);
//     if (*res)
//     {
//         *res = ft_strjoin(*res, new_part);
// 		// if(new_res)
// 		// 	free(new_res);
//     }
//     else
//         *res = new_part;
// 	if(new_part)
// 		free(new_part);
// }
void	append_to_str(char **res, char *tmp, int end, int start)
{
    char *new_part;
    char *new_res;

    new_part = malloc((end - start + 1) * sizeof(char)); 
    if (!new_part)
        return; 
    ft_strlcpy(new_part, tmp + start, end - start + 1);
    if (*res) {
        new_res = ft_strjoin(*res, new_part);
        *res = new_res; 
    } else {
        *res = new_part;
        new_part = NULL;
    }
    if (new_part) {
        free(new_part);
    }
}

// void handle_NQ(char **res, char *tmp, int *i, t_env *new_env, t_lexems **lexeme)
// {
// 	//dollar case
// 	if(tmp[*i] == '$' && (tmp[*i + 1]))
// 	//SQ found
// }
void handle_NQ(char **res, char *tmp, int *i, t_env *new_env, t_lexems **lexeme) {
    int start;
    char *var = NULL;
    char *exit_code_str;

    (void)new_env;  // Ignore new_env for now, adjust if necessary
	(void)lexeme;
    // Initialize the index
    (*i)++;
    start = *i;

    // Handle single quotes
    if (tmp[start] == '\'') {
        (*i)++;  // Skip the opening single quote
        start = *i;
        // Append characters until the closing single quote
        while (tmp[*i] && tmp[*i] != '\'') {
            (*i)++;
        }
        append_to_str(res, tmp, *i, start);  // Append the content inside single quotes
        if (tmp[*i] == '\'') (*i)++;  // Skip the closing single quote
        return;
    }
    // Handle double quotes
    else if (tmp[start] == '"') {
        (*i)++;  // Skip the opening double quote
        start = *i;
        // Append characters until the closing double quote
        while (tmp[*i] && tmp[*i] != '"') {
            if (tmp[*i] == '$') {
                // Handle variable expansion within double quotes
                expander(res, tmp, i, new_env);  // Call expander for variable expansion
            } else {
                (*i)++;
            }
        }
        append_to_str(res, tmp, *i, start);  // Append the content inside double quotes
        if (tmp[*i] == '"') (*i)++;  // Skip the closing double quote
        return;
    }

    // Handle the case of a dollar sign ($)
    if (tmp[start] == '$') {
        (*i)++;  // Skip the dollar sign
        start = *i;

        // Check for the case where it is a number (e.g., $1)
        if (ft_isdigit(tmp[*i])) {
            while (tmp[*i] && tmp[*i] != ' ') {
                (*i)++;
            }
            return append_to_str(res, tmp, *i, start);  // Just append as is
        }
        // Handle special case for exit code ($?)
        else if (tmp[*i] == '?') {
            exit_code_str = ft_itoa(ret_value);  // Get the exit code
            *res = ft_strjoin(*res, exit_code_str);  // Append the exit code
            free(exit_code_str);  // Free the memory
            (*i)++;
            return;  // Return after handling exit code
        }
        // Handle variable names (e.g., $USER)
        else {
            while (ft_isalnum(tmp[*i])) {
                (*i)++;
            }
            append_to_str(&var, tmp, *i, start);  // Extract the variable name

            // Check if the variable exists in the environment
            char *env_value = getenv(var);
            if (env_value) {
                *res = ft_strjoin(*res, env_value);  // Append the variable value if found
            }
            free(var);  // Free the variable name memory
            return;
        }
    }

    // Append remaining characters until encountering a special condition
    while (tmp[*i] && tmp[*i] != '$' && tmp[*i] != '"' && tmp[*i] != '\'') {
        (*i)++;
    }
    append_to_str(res, tmp, *i, start);  // Append the remaining content
}
