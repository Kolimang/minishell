/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/14 14:42:04 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_shlvl(t_env *env)
{
	char	*current;
	char	**cmd;
	char	*tmp;
	int		val;

	current = get_env_val(env, "SHLVL");
	if (!current)
		current = "0";
	val = ft_atoi(current);
	tmp = ft_itoa(val + 1);
	cmd = malloc (sizeof(char *) * 3);
	//ft_export
	//to finish once export is coded
	free(cmd);
	free(tmp);
}

char	*get_env_val(t_env *env, const char *var_name)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, var_name, ft_strlen(var_name) + 1) == 0)
			return (temp->var_val);
		temp = temp->next;
	}
	return (NULL);
}

int	get_env_len(t_env *env)
{
	t_env	*temp;
	int		len;

	if (!env)
		return (0);
	temp = env;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len += 1;
	}
	return (len);
}

static char	*node_to_line(t_env *node)
{
	char	*line;
	char	*templine;

	templine = ft_strjoin(node->var_name, "=");
	if (!templine)
		return (NULL);
	line =  ft_strjoin(templine, node->var_val);
	free(templine);
	if (!line)
		return (NULL);
	return (line);
}

char	**env_to_array(t_env *env)
{
	t_env	*temp;
	int		i;
	int		len;
	char	**array;

	len = get_env_len(env);
	array = malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	temp = env;
	i = 0;
	while (temp)
	{
		array[i] = node_to_line(temp);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
