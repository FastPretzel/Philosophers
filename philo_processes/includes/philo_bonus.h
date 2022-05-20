/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:20:06 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 14:58:23 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# define ERROR_ARGS 1
# define ERROR_PHILOS 2
# define ERROR_FORK 3
# define DEAD 4
# define FULL 5

typedef struct s_phil
{
	int				id;
	int				eat_cnt;
	pid_t			pid;
	unsigned long	death_time;
	struct s_proj	*p_proj;
}	t_phil;

typedef struct s_proj
{
	int				phils_cnt;
	int				stop;
	int				num_of_eat;
	int				full_cnt;
	t_phil			*phils;
	unsigned long	start_time;
	unsigned long	sleep_time;
	unsigned long	eat_time;
	unsigned long	time_to_die;
	sem_t			*forks;
	sem_t			*write;
}	t_proj;

void			ft_usleep(unsigned long time_of_sleep);
unsigned long	ft_time(void);
void			print_log(t_phil *phil, char *str);
void			free_all(t_proj *proj, int exit_code);
void			error(t_proj *proj, int code);
int				valid_argv(int argc, char **argv);
int				init(int argc, char **argv, t_proj *proj);
int				ft_atoi(char *nptr);
void			start(t_phil *phil);

#endif
