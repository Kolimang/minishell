/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/09/24 17:36:48 by lboumahd         ###   ########.fr       */
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
//returns cleaned str without SQ 
char *handle_SQ(char **iter)
{
	char *str;
	int i = 0;
	char *tmp;
	tmp = *iter;
	while(++*iter)
	{
		if((**iter) == SQ)
			str = ft_substr(tmp, 0, i - 1);
		i++;
	}
	return(str);
}

char *handle_DQ(char **iter, t_env *new_env)
{
	//SQ is treated as literal characters
}

char *clean(char *tmp, t_lexems *lexeme, t_env *new_env)
{
	//set flag for SQ/NQ/DQ
	//process each case
	char *str;
	char *final_str;
	char *iter;
	iter = tmp;
	while(iter++)
	{
		if(*iter == SQ)
			str = handle_SQ(&iter);
		else if(*iter == DQ)
			str = handle_DQ(&iter, new_env);
		else
			str = handle_NQ();
		final_str = ft_strjoin(final_str, str);
	}
	return(final_str);
}

void process_regular(t_lexems *lexeme, t_env *new_env)
{
    char	*tmp;
	char *clean_str;
	if (!lexeme)
		exit(EXIT_FAILURE);
	if (lexeme->str == NULL)
        return;
	tmp = ft_strdup(lexeme->str);
	clean_str = clean(tmp, lexeme, new_env);
	free(tmp);
}

void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag)
{
	//$is detected , the str is sent without $ ??????????/ a discuter 
	//echo "$'USER'" the whole arg is a string 
	//the SQ or DQ is supposed to arrive enclosed 
    if (flag == 1)  // Normal exp case
		process_regular(lexeme, new_env);
    else
		process_HRDOC(lexeme);
	//error ?? 
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