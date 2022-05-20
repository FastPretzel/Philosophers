/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:26:51 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 16:17:59 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	est(t_args *args)
{
	t_phil	*phil;

	phil = args->phil;
	pthread_mutex_lock(&args->forks[phil->left_fork]);
	print_log(args, "has taken a fork");
	pthread_mutex_lock(&args->forks[phil->right_fork]);
	print_log(args, "has taken a fork");
	print_log(args, "is eating");
	pthread_mutex_lock(&args->p_proj->data_mutex);
	args->death_time = ft_time() + args->time_to_die;
	pthread_mutex_unlock(&args->p_proj->data_mutex);
	args->phil->eat_cnt++;
	ft_usleep(args->eat_time);
	pthread_mutex_lock(&args->p_proj->data_mutex);
	if (args->p_proj->num_of_eat == args->phil->eat_cnt)
		args->p_proj->full_cnt++;
	pthread_mutex_unlock(&args->p_proj->data_mutex);
	pthread_mutex_unlock(&args->forks[phil->left_fork]);
	pthread_mutex_unlock(&args->forks[phil->right_fork]);
	print_log(args, "is sleeping");
	ft_usleep(args->sleep_time);
	print_log(args, "is thinking");
}

static void	*check_death(void *args)
{
	t_args	*curr_args;

	curr_args = (t_args *)args;
	while (!curr_args->phil->dead)
	{
		pthread_mutex_lock(&curr_args->p_proj->data_mutex);
		if (ft_time() > curr_args->death_time)
			curr_args->phil->dead = 1;
		pthread_mutex_unlock(&curr_args->p_proj->data_mutex);
	}
	return (0);
}

void	*start(void *args)
{
	t_args		*curr_args;
	pthread_t	pthr;
	int			stop;

	stop = 0;
	curr_args = (t_args *)args;
	if (curr_args->phil->id % 2 == 0)
		usleep(500);
	curr_args->death_time = ft_time() + curr_args->time_to_die;
	pthread_create(&pthr, NULL, check_death, args);
	pthread_detach(pthr);
	while (!stop)
	{
		pthread_mutex_lock(&curr_args->p_proj->data_mutex);
		stop = curr_args->p_proj->stop;
		pthread_mutex_unlock(&curr_args->p_proj->data_mutex);
		est(curr_args);
	}
	return (0);
}
