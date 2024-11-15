/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 10:45:51 by jrichir          ###   ########.fr       */
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
		return ;
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

void	ft_print_command(t_command *command)
{
	ft_printf("argc             : %d\n", command->argc);
	ft_printf("args             : ");
	ft_printarray(command->args, ' ');
	ft_printf("redir            : ");
	ft_print_redir(command);
	ft_printf("\n");
	ft_printf("prevpipe         : %d\n", command->prevpipe);
	ft_printf("nextpipe         : %d\n", command->nextpipe);
	ft_printf("eflag            : %d\n", command->eflag);
	ft_printf("--- --- --- --- --- ---\n");
}

void	ft_print_redir(t_command *command)
{
	t_redir	*redir;
	t_list	*rdlist;
	t_list	*initial;

	initial = command->ls_redirs;
	if (!initial)
	{
		ft_printf("(null)");
		return ;
	}
	while (command->ls_redirs)
	{
		rdlist = command->ls_redirs;
		redir = rdlist->content;
		ft_printf("%s (type:%d)", redir->value, redir->type);
		if (command->ls_redirs->next)
			ft_printf(", ");
		command->ls_redirs = command->ls_redirs->next;
	}
	command->ls_redirs = initial;
}
