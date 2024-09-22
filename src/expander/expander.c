/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/09/22 23:09:07 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*expand $ and ~ 
gets a linked list from lexer () 
 ->receiving the arg to expand only 
 $ cases :	
	"$VAR" || $VAR : <user_name>
	'$VAR' : $VAR
	$?
	$VAR$USER$HOME 
~ cases: 
	cd ~/fd/fd1 : cd /USERS/user_name/fd/fd1
	---- The expansion happens in 2 caes : D_Quotes and No_Quotes
	---- The expansion in here_doc : both '' and ""
	
*/
char *get_real_value(char *str, t_env *new_env)
{
	// handling digit or no?? 
    if (ft_isdigit(str[0]))
        return strdup("");
    t_env *env = new_env;
    while (env)
    {
        if (ft_strcmp(env->var, str) == 0) 
            return (ft_strdup(env->value));
        env = env->next;
    }
    return strdup("");
}

void expand(t_lexems *lexeme, t_env *new_env)
{
    char	*str = lexeme->str;
    char	*clean_str = NULL; 

    //handle SQ
	//handle ? 
	
	 {
		//join $ with str and return 
		 return(lexeme->value = ft_strdup(str));  //no exp
    if (str[0] == '?' && str[1] == '\0')  // If it's just $?
        return(lexeme->value = get_exit_status());
	//handle the case where '' is inside DQ !!!!
		//if its expandable expand it 
		//if not empty string and skip it 
    clean_str = get_clean_str(str);
    lexeme->value = get_real_value(clean_str, new_env); //exp
    if (clean_str)
        free(clean_str);
}

void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag)
{
	//$is detected , the str is sent without $ ??????????/ a discuter 
	//echo "$'USER'" the whole arg is a string 
	//the SQ or DQ is supposed to arrive enclosed 
    if (lexeme == NULL || lexeme->str == NULL)
        return; //ERRORRRRRRRRR RETURN
    if (flag == 1)  // Normal exp case
    {
	  //if theres only $ to echo $ only
        if (lexeme->str[0] == SQ)  //no expansion
            lexeme->value = ft_strdup(lexeme->str);
        else if (lexeme->str[0] == DQ) // DQ or NQ, expand
            expand_DQ(lexeme, new_env); 
		else 
			expand_NQ(lexeme, new_lexeme);
    }
    else
        expand_HR(lexeme);
}

//TESTS 
/*
bash-3.2$ echo $USER
lboumahd
bash-3.2$ echo '$USERl'
$USERl
bash-3.2$ echo $'$USERl'
$USERl
bash-3.2$ echo $'$USER'
$USER
bash-3.2$ echo $"$USER"
lboumahd
bash-3.2$ echo $'$USER'
$USER
bash-3.2$ echo $'$'$USER'' woowwww
$lboumahd
bash-3.2$ 
*/