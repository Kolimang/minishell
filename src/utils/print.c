/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/14 11:51:11 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_printarray(char **array, char separator)
{
	int	i;

	i = 0;
	if (!array || !array[0])
		ft_printf("(null)");
	while (array[i])
	{
		ft_printf("%s", array[i]);
		if (i < (ft_arraylen(array) - 1))
			ft_printf("%c", separator);
		i++;
	}
	ft_printf("\n");
}

void	ft_print_list(t_list *list, char *title)
{
	t_list	*temp;

	temp = list;
	if (!list)
		return ;
	if (title && title[0] != '\0')
		printf("%s\n", title);
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

void	ft_print_lexemes(t_list *list, int option, char separator, char *title)
{
	t_lexeme	*lex;
	t_list		*temp;

	if (!list)
		return ;
	if (!title || title[0] == '\0')
		return;
	if (separator == '\n')
		printf("%s\n", title);
	else
		printf("%s ", title);
	temp = list;
	while (temp)
	{
		lex = temp->content;
		if (option == 1)
			printf("%s", lex->str);
		else if (option == 2)
			printf("%s", lex->value);
		if (temp->next)
			printf("%c", separator);
		temp = temp->next;
	}
	if (separator != '\n')
		printf("\n");
}
