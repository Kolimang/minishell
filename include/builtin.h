/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 14:46:52 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

// echo.c
int	ft_echo(char **args);

// cd.c
int	ft_cd(char **args, t_env *env);

// pwd.c
int	ft_pwd(char **args, t_env *env);

// export.c
int	ft_export(char **args, t_env *env);
int	print_env(t_env *env, int mode);
int	ft_env(char **args, t_env *env);

// env.c
//void	prep_sort_env(t_env **env);
// void	sort_env(t_env **env, t_env *current, t_env *prev_curr);
void	sort_env(t_env **env);
#endif
