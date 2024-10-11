/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:33 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/11 12:00:57 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command(t_command *command)
{
	command->index = 0;
	command->argc = 0;
	command->args = NULL;
	command->i_file = NULL;
	command->i_hd_delimiter = NULL;
	command->o_file = NULL;
	command->o_file_append = NULL;
	command->nextpipe = 0;
}

char	**get_args(t_list *lexemes, int argc)
{
	t_lexemes	*node;
	char		**args;
	int			i;

	args = malloc((argc + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	args[argc] = NULL;
	i = 0;
	while (lexemes)
	{
		node = lexemes->content;
		if (node->type == 2)
		{
			args[i] = node->value;
			i++;
		}
		lexemes = lexemes->next;
	}
	return (args);
}

t_command	*ft_parse_lexemes(t_list *lexemes, int id, int nb_commands)
{
	t_command	*command;
	t_lexemes	*node;
	t_lexemes	*nextnode;
	t_list		*start;
	int			i;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(command);
	command->index = id;
	if (id < nb_commands - 1)
	command->nextpipe = 1;
	i = 0;
	start = lexemes;
	while (lexemes)
	{
		node = lexemes->content;
		if (lexemes->next && lexemes->next->content)
			nextnode = lexemes->next->content;
		if (ft_strncmp(node->value, "<<", 2) == 0)
		{
			command->i_hd_delimiter = nextnode->value;
			lexemes = lexemes->next;
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
		else
		{
			command->argc += 1;
			node->type = 2;
		}
		lexemes = lexemes->next;
	}
	command->args = get_args(start, command->argc);
	return (command);
}

void	ft_print_command(t_command *command)
{
	ft_printf("index            : %d\n", command->index);
	ft_printf("argc             : %d\n", command->argc);
	ft_printf("args             : ");
	ft_printarray(command->args, ' ');
	ft_printf("i_file           : %s\n", command->i_file);
	ft_printf("i_hd_delimiter   : %s\n", command->i_hd_delimiter);
	ft_printf("o_file           : %s\n", command->o_file);
	ft_printf("o_file_append    : %s\n", command->o_file_append);
	ft_printf("nextpipe         : %d\n", command->nextpipe);
	ft_printf("--- --- --- --- --- ---\n");
}
