/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:34:40 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 13:46:34 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned long time_of_sleep)
{
	unsigned long	time_of_start;

	time_of_start = ft_time();
	while (ft_time() - time_of_start < time_of_sleep)
		usleep(500);
}

void	print_log(t_args *args, char *str)
{
	pthread_mutex_lock(&args->p_proj->write);
	printf("\e[38;5;141m%lu\e[0m \e[38;5;11m%d\e[0m %s\n", \
			ft_time() - args->p_proj->start_time, args->phil->id, str);
	pthread_mutex_unlock(&args->p_proj->write);
}

void	free_all(t_args *args)
{
	if (args)
	{
		if (args->phils_malloc)
			free(args->phils_malloc);
		if (args->forks)
			free(args->forks);
		free(args);
	}
}

void	error(t_args *args, int code)
{
	if (code == ERROR_ARGS)
		printf("\e[1;41mERROR ARGS\e[0m\n");
	else if (code == ERROR_PHILOS)
		printf("\e[1;41mERROR PHILOS\e[0m\n");
	else if (code == ERROR_MUTEX)
		printf("\e[1;41mERROR MUTEX\e[0m\n");
	else if (code == ERROR_PTHREAD)
		printf("\e[1;41mERROR PTHREAD\e[0m\n");
	else if (code == ERROR_MALLOC)
	{
		printf("\e[1;41mERROR MALLOC\e[0m\n");
		return ;
	}
	free_all(args);
}
