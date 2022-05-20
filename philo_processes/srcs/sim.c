/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:22 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 15:01:27 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	est(t_phil *phil)
{
	sem_wait(phil->p_proj->forks);
	print_log(phil, "has taken a fork");
	sem_wait(phil->p_proj->forks);
	print_log(phil, "has taken a fork");
	print_log(phil, "is eating");
	phil->death_time = ft_time() + phil->p_proj->time_to_die;
	phil->eat_cnt++;
	ft_usleep(phil->p_proj->eat_time);
	sem_post(phil->p_proj->forks);
	sem_post(phil->p_proj->forks);
	if (phil->p_proj->num_of_eat == phil->eat_cnt)
		exit(FULL);
	print_log(phil, "is sleeping");
	ft_usleep(phil->p_proj->sleep_time);
	print_log(phil, "is thinking");
}

static void	*check_death(void *phil)
{
	t_phil	*curr_phil;

	curr_phil = (t_phil *)phil;
	while (1)
	{
		if (ft_time() > curr_phil->death_time)
		{
			curr_phil->p_proj->stop = 1;
			sem_wait(curr_phil->p_proj->write);
			printf("\e[38;5;141m%lu\e[0m \e[38;5;11m%d\e[0m \e[38;5;160m%s\e[0m\n", \
					ft_time() - curr_phil->p_proj->start_time, \
					curr_phil->id, "IS DEAD");
			exit(DEAD);
		}
	}
	return (0);
}

void	start(t_phil *phil)
{
	pthread_t	pthr;
	int			stop;

	stop = 0;
	phil->death_time = ft_time() + phil->p_proj->time_to_die;
	pthread_create(&pthr, NULL, check_death, phil);
	pthread_detach(pthr);
	while (!stop)
	{
		stop = phil->p_proj->stop;
		est(phil);
	}
}
