/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/10 17:00:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command(t_command *command)
{
	command->index = 0;
	command->name = NULL;
	command->options = NULL;
	command->args = NULL;
	command->i_file = NULL;
	command->i_heredoc = NULL;
	command->o_file = NULL;
	command->o_file_append = NULL;
}

t_command	*ft_parse_lexemes(t_list *lexemes, int id)
{
	t_command	*command;
	t_lexemes	*node;
	t_lexemes	*nextnode;
	t_list		*temp;
	int			i;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(command);
	i = 0;
	while (lexemes)
	{
		temp = lexemes;
		node = lexemes->content;
		if (lexemes->next && lexemes->next->content)
			nextnode = lexemes->next->content;
		command->index = id;
		if (ft_strncmp(node->value, "<<", 2) == 0)
		{
			while (lexemes)
			{
				node = lexemes->content;
				if (node->type == 1)
				{
					command->i_heredoc = lexemes;
					break;
				}
				lexemes = lexemes->next;
			}
			lexemes = temp->next;
		}
		else if (ft_strncmp(node->value, ">>", 2) == 0)
		{
			command->o_file_append = nextnode->value;
			lexemes = lexemes->next;
		}
		else if (ft_strncmp(node->value, "<", 1) == 0)
		{
			command->i_file = nextnode->value;
			lexemes = lexemes->next;
		}
		else if (ft_strncmp(node->value, ">", 1) == 0)
		{
			command->o_file = nextnode->value;
			lexemes = lexemes->next;
		}
		else if (ft_strncmp(node->value, "-", 1) == 0)
		{
			command->options = node->value;
		}
		else if (!command->name)
		{
			if (node->type == 0)
				command->name = node->value;
		}
		else if (!command->args)
		{
			if (node->type == 0)
				command->args = node->value;
		}
		lexemes = lexemes->next;
	}
	return (command);
}

void	ft_print_command(t_command *command)
{
	ft_printf("index         : %d\n", command->index);
	ft_printf("name          : %s\n", command->name);
	ft_printf("options       : %s\n", command->options);
	ft_printf("args          : %s\n", command->args);
	ft_printf("i_file        : %s\n", command->i_file);
	ft_printf("i_heredoc     : ");
	if (command->i_heredoc)
		ft_print_lexemes(command->i_heredoc, 2, ' ', "");
	ft_printf("\n");
	ft_printf("o_file        : %s\n", command->o_file);
	ft_printf("o_file_append : %s\n", command->o_file_append);
}
