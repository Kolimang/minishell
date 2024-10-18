/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/18 15:36:44 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

// echo.c
int	ft_echo(char **args);

// cd.c
int	ft_cd(char **args, t_env *env);
static int	set_pwd(char *path, t_env *env);

// pwd.c
int	ft_pwd(char **args, t_env *env);

#endif
