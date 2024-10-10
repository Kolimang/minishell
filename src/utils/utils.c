/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/10 16:22:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	ft_printarray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
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

void	ft_print_lexemes(t_list *list, int option, char separator, char *title)
{
	t_lexemes	*lexeme;

	if (!list)
		return ;
	if (title && title[0] != '\0')
	{
		if (separator == '\n')
			printf("%s\n", title);
		else
			printf("%s ", title);
	}
	while (list)
	{
		lexeme = list->content;
		if (option == 1)
			printf("%s", lexeme->str);
		else if (option == 2)
			printf("%s", lexeme->value);
		if (list->next)
			printf("%c", separator);
		list = list->next;
	}
	if (separator != '\n')
		printf("\n");
}
