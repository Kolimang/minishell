/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/29 10:35:21 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*var_name;
	char			*var_val;
	int				index;
	struct s_env	*next;
}	t_env;

t_env	*init_env(char **original_env);
int		add_env_var(t_env **env, const char *var_name, const char *var_val,
			int index);
char	*get_env_val(t_env *env, const char *var_name);
t_env	*create_env_node(const char *var_name, const char *var_val, int index);
void	free_env(t_env *env);
void	set_shlvl(t_env *env);
// jp
int	update_env(char *name, char *value, t_env **env);

#endif
