/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/30 11:05:01 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

// echo.c
int		ft_echo(char **args);

// cd.c
int		ft_cd(char **args, t_env *env);

// pwd.c
int		ft_pwd(char **args, t_env *env);

// export.c
int		ft_export(char **args, t_env **env);
int		print_env(t_env *env, int mode);
int		ft_env(char **args, t_env *env);

// env.c
void	sort_env(t_env **env);

// unset.c
int		ft_unset(char **args, t_env **env);

// exit.c
int		ft_exit(char **args, t_env *env, int eof);

#endif
