/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/29 14:27:13 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLE_H
# define SIGHANDLE_H

void	init_signals(void);
void	ft_sighandler(int signum);

#endif
