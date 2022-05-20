/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:18:17 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 14:18:20 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

# define ERROR_ARGS 1
# define ERROR_PHILOS 2
# define ERROR_MUTEX 3
# define ERROR_PTHREAD 4
# define ERROR_MALLOC 5

typedef struct s_phil
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	eat_cnt;
	int	dead;
}	t_phil;

typedef struct s_args
{
	struct s_proj	*p_proj;
	t_phil			*phil;
	t_phil			*phils_malloc;
	pthread_mutex_t	*forks;
	unsigned long	sleep_time;
	unsigned long	eat_time;
	unsigned long	time_to_die;
	unsigned long	death_time;
}	t_args;

typedef struct s_proj
{
	t_args			*args;
	int				phils_cnt;
	int				stop;
	int				num_of_eat;
	int				full_cnt;
	unsigned long	start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	data_mutex;
}	t_proj;

void			ft_usleep(unsigned long time_of_sleep);
unsigned long	ft_time(void);
void			print_log(t_args *args, char *str);
void			free_all(t_args *args);
void			error(t_args *args, int code);
int				init(int argc, char **argv, t_proj *proj);
int				ft_atoi(char *nptr);
void			*start(void *args);

#endif
