/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/09/29 20:16:59 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//WHAT TO DO WHEN !str , NULL of EXIT_FAILURE??


void handle_SQ(char **res, char *tmp, int *i)
{
    int start = *i; 

	(*i)++;
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
	if(res)
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
        while (tmp[*i] != DQ && tmp[*i]) {
            // If we encounter $, check if the next character is not a single quote
            if (tmp[*i] == '$' && tmp[*i + 1] != '\'') {
                break; // Exit the loop if we need to handle variable expansion
            }
            (*i)++; // Move to the next character
        }
        // Check if we encountered a closing double quote
        if (tmp[*i] == DQ) {
            append_to_str(res, tmp, *i, start);
            (*i)++; 
            return; 
        }
        if (tmp[*i] == '$') {
            append_to_str(res, tmp, *i, start);
			printf("%d\n", *i); // Append characters before $
            expander(res, tmp, i, new_env);
        }
    }
	if(res)
		free(res);
    // If we reach here, it means we didn't find a closing double quote
    fprintf(stderr, "Error: No closing double quote found.\n");
    exit(EXIT_FAILURE); // Handle the error as needed
}

char *handle_exp(char *tmp, t_lexems *lexeme, t_env *new_env)
{
	//set flag for SQ/NQ/DQ
	//process each case
	//colelct and append the str
	char *res;
	char *final_res;
	//calloc str;
	//calloc final_str????
	final_res = ft_calloc(sizeof(char), 1);
	res = ft_calloc(sizeof(char), 1);
	int i;
	i = 0;
	while(tmp[i])
	{
		if(tmp[i] == SQ)
			handle_SQ(&res, tmp, &i);
		else if(tmp[i] == DQ)
			handle_DQ(&res, tmp, &i, new_env); 
		printf("%d", lexeme ->type);
		// else
		// 	handle_NQ(&res, tmp, &i, new_env, &lexeme); //si on rajoute le lexer apres le parseur 
		final_res = ft_strjoin(final_res, res);
		i++;
	}
	return(final_res);
} 

void process_regular(t_lexems *lexeme, t_env *new_env)
{
{
    char *tmp;
    char *clean_str;

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
	char *var;
	char *exit_code_str;
	
	(*i)++;
	start = *i;
	printf("%d\n", *i);
	if((tmp[start] == ' ') ||(tmp[start] == '\0') || (tmp[start] == DQ))
		return(append_to_str(res, tmp, *i , start - 1));
	else if(ft_isdigit(tmp[*i]))//digit 0 - 9 -> skip num then append to str
		{
			while(tmp[*i] && tmp[*i] != DQ && tmp[*i] != ' ')
				(*i)++;
			printf("i : %d \n", *i);
			printf("start : %d \n", start);
			return(append_to_str(res, tmp, *i, start + 1));
		}
	else if (tmp[*i] == '?') //mise a jour du code d erreur 
	{
		exit_code_str = ft_itoa(ret_value); // Convert exit status to string using global variable
		*res = ft_strjoin(*res, exit_code_str);   // Append exit status to result
		free(exit_code_str);                      // Free the allocated string
		(*i)++;                                  // Move past the '?'
		return; 
	}// find exit error 
	else
	{ ///BUUUG  = SEGmentation fault 
		var  = replace_var(tmp, i, start, new_env);//fetch var in env and malloc var
		if(var)
			*res = ft_strjoin(*res, var);
		else
			*res = ft_strjoin(*res, "");
		free(var);
	}	//var found -> expand then append to str 
	
}


char	*find_var(char *var, t_env *new_env)
{
	while(new_env) // determiner le new_env structu
	{
		if (ft_strncmp(new_env->var_name, var, ft_strlen(var) + 1) == 0)
		{	
			var = new_env->var_val;
			return(var);
		}
		new_env = new_env->next;
	}
	return (NULL);
}

char	*replace_var(char *tmp, int *i, int start, t_env *new_env)
{
	char *var;

	while(ft_isalnum(tmp[*i]))
		i++;
	var = malloc(*i - start + 1);
	if(!var)
		return (NULL);
	ft_strlcpy(var, tmp, *i - start + 1);
	var = find_var(var, new_env);//if not found return NULL
	return(var);
}
//oblige de rajouter un espace
void append_to_str(char **res, char *tmp, int end, int start)
{
    char *new_part;
    char *new_res;

    new_part = malloc((end - start) * sizeof(char) + 1); 
    if (!new_part)
        return;
    ft_strlcpy(new_part, tmp + start, end - start + 1);
    if (*res)
    {
        new_res = ft_strjoin(*res, new_part);
        free(*res); 
        *res = new_res;
		// if(new_res)
		// 	free(new_res);
		
    }
    else
        *res = new_part;
    free(new_part);
}