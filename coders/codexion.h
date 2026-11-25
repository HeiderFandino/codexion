/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandino <hfandino@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:52:41 by hfandino          #+#    #+#             */
/*   Updated: 2026/11/25 23:13:48 by hfandino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	long long		last_release_ms;
	int				in_use;
}	t_dongle;

typedef struct s_coder
{
	pthread_t	coder;
	long long	compile_start;
	int			id_coder;
	int			times_compiled;
}	t_coder;

typedef struct s_simulation
{
	t_scheduler		scheduler;
	pthread_mutex_t	mutex;
	t_coder			*coders;
	t_dongle		*dongles;
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				compiles_required;
	int				dongle_cooldown;
	int				finish;
}	t_simulation;

#endif
