/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/14 15:33:53 by lboumahd         ###   ########.fr       */
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

typedef	struct s_envs
{
	char	**g_env;
	t_env	**l_env; 
}t_envs;

t_env	*init_env(char **original_env);
int		add_env_var(t_env **env, const char *var_name, const char *var_val,
			int index);
char	*get_env_val(t_env *env, const char *var_name);
t_env	*create_env_node(const char *var_name, const char *var_val, int index);
void	free_env(t_env **env);
void	set_shlvl(t_env *env);

int		update_env(char *name, char *value, t_env **env, int mode);
int		print_env_sorted(t_env *env);
int		print_env_unsorted(t_env *env);
int		get_env_len(t_env *env);
t_env	*clone_env(t_env *env);
char	**env_to_array(t_env *env, int len);

#endif
