/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/15 13:47:45 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Global exit status
int	g_ret_value = 0;

int	ft_check_input_cmd(char **cmdref)
{
	char	last;
	char	*cmd;

	cmd = ft_strtrim_replace(cmdref);
	if ((int)ft_strlen(cmd) > 0)
	{
		last = cmd[(int)ft_strlen(cmd) - 1];
		if (cmd[0] == '|' || last == '|')
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (-1);
		}
	}
	else if (cmd[0] == '\0')
		return (-1);
	return (0);
}

int	execute(t_env *env)
{
	char		*prompt;
	char		*cmd;
	char		**cmds;
	t_list		*lexemes;
	t_command	*command;
	int			i;

	printf("\033[0;38;5;214m=== MiNiSHELL %s ===\033[0m\n\n", VERSION);
	prompt = "\033[0;32mminishell$\033[0m ";
	while (1)
	{
		cmd = readline(prompt);
		if (!cmd)
			return (1);
		ft_add_cmd_to_history(cmd);
		i = ft_check_input_cmd(&cmd);
		if (i == 0)
		{
			cmds = ft_split(cmd, '|');
			while (cmds[i]) 
			{
				cmds[i] = ft_strtrim_replace(&cmds[i]);
				if (cmds[i] && (cmds[i][0] == '\0'))
				{
					ft_putstr_fd("syntax error near unexpected token `|'\n", 2); // un second msg "Undefined error: 0" s'ajoute a l'output
					i = -1;
					break;
				}
				i++;
			}
		}
		if (i != -1)
		{
			i = 0;
			while (cmds[i])
			{
				lexemes = ft_tokenize(cmds[i]);
				if (!lexemes)
					return (printf("HEEERE\n"), free(cmds[i]), 1); // temp, not complete, must free all commands
				//ft_print_lexemes(lexemes, 1, ' ', "\033[0;33m[command ]\033[0m");
				ft_expand_lexeme_list(lexemes, env);
				//ft_print_lexemes(lexemes, 2, ' ', "\033[0;33m[expanded]\033[0m"); // in place of exec
				command = ft_parse_lexemes(lexemes, i, ft_arraylen(cmds)); // turn lexemes-list into commands-list
				if (command)
					ft_print_command(command); // For debug, in place of exec(command)
				// free_list or delete_list lexemes
				i++;
			}
			free(cmds); // Pas complet pour free toutes les cmds, ne free que le array "conteneur"
		}
		free(cmd);
	}
	return (0);
}

//env = test environment
int	main(int ac, char **av, char **o_env)
{
	t_env		*env;

	(void)ac;
	(void)av;
	g_ret_value = 0;
	env = init_env(o_env);
	//set_shlvl(env);
	if (execute(env))
		return (1);
	free_env(env);
	return (0);
}
