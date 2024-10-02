
#include "minishell.h"
void dup_word(char **res, char *str, int *i)
{
	int		start;

	if (!str || !i)
		exit(EXIT_FAILURE);
	start = *i; 
	while (str[*i])
	{
		
		if (!ft_isalnum(str[*i]) && *i != start && str[*i] != '?')
		{
			append_to_str(res, str, *i, start + 1); 
			return;
		}
		(*i)++;  
	}
	append_to_str(res, str, *i, start);
}

void	handle_NQ(char **res, char *tmp, int *i, t_env *new_env, t_lexems *lexeme)
{
	(void)lexeme;
	int start = *i;

	if (tmp[*i] == '$' && (tmp[*i + 1] == DQ || tmp[*i + 1] == SQ))
	{	
		if (tmp[*i + 1] == DQ)
			dup_word(res, tmp, i);
		else if (tmp[*i + 1] == SQ)
		{
			handle_SQ(res, tmp, i, start);
		}
		return;
	}
	// Handle variable expansion
	else if (tmp[*i] == '$')
	{
		expander(res, tmp, i, new_env);
		return;
	}
	else
	{
		while (tmp[*i] && tmp[*i] != '$' && tmp[*i] != SQ && tmp[*i] != DQ)
		{
			(*i)++;  // Move *i to the end of the current non-special segment
		}
		// Append the portion of the string from start to the current *i
		append_to_str(res, tmp, *i, start);
	}
}


// void handle_DQ(char **res, char *tmp, int *i, int start, t_env *new_env) 
// {
//     (*i)++; // Move past the opening double quote

//     while (tmp[*i]) 
// 	{
		
//         start = *i;
// 		(*i)++;
		
//         while (tmp[*i] != DQ && tmp[*i]) 
//            { 
// 			if (tmp[*i] == '$' && tmp[*i + 1] != '\'') 
//                 break; 
//         	(*i)++; 
//        		}
       
//         if (tmp[*i] == DQ) 
// 		{
//             append_to_str(res, tmp, *i, start);
//             (*i)++;
//             return; 
//         }
//         if (tmp[*i] == '$') {
// 			append_to_str(res, tmp, *i, start);
//             expander(res, tmp, i, new_env);
//         }
//     }
// 	if(res)
// 		free(res);
// 	//ATTTENNNNNTIONNNNNNNNNN FPRINTF
//     fprintf(stderr, "Error: No closing double quote found.\n");
//     exit(EXIT_FAILURE); // Handle the error as needed
// }
// void handle_DQ(char **res, char *tmp, int *i, int start, t_env *new_env) 
// {
   
//     (*i)++; // Move past the opening double quote

//     while (tmp[*i]) 
// 	{
		
//         start = *i;
// 		(*i)++;
		
//         while (tmp[*i] != DQ && tmp[*i]) 
//            { 
// 			if (tmp[*i] == '$' && tmp[*i + 1] != '\'') 
//                 break; 
//         	(*i)++; 
//        		}
       
//         if (tmp[*i] == DQ) 
// 		{
//             append_to_str(res, tmp, *i, start);
//             (*i)++;
//             return; 
//         }
//         if (tmp[*i] == '$') {
// 			append_to_str(res, tmp, *i, start);
//             expander(res, tmp, i, new_env);
// 			(*i)++;
// 			return;
//         }
//     }
// 	free(res);
// 	//ATTTENNNNNTIONNNNNNNNNN FPRINTF
//     fprintf(stderr, "Error: No closing double quote found.\n");
//     exit(EXIT_FAILURE); // Handle the error as needed
// }