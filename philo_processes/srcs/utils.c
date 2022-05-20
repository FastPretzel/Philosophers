/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:14 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 15:04:35 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_log(t_phil *phil, char *str)
{
	sem_wait(phil->p_proj->write);
	printf("\e[38;5;141m%lu\e[0m \e[38;5;11m%d\e[0m %s\n", \
			ft_time() - phil->p_proj->start_time, phil->id, str);
	sem_post(phil->p_proj->write);
}

void	free_all(t_proj *proj, int exit_code)
{
	if (proj)
	{
		if (proj->phils)
			free(proj->phils);
	}
	exit(exit_code);
}

void	error(t_proj *proj, int code)
{
	if (code == ERROR_ARGS)
	{
		printf("\e[1;41mERROR ARGS\e[0m\n");
		return ;
	}
	else if (code == ERROR_PHILOS)
		printf("\e[1;41mERROR PHILOS\e[0m\n");
	else if (code == ERROR_FORK)
		printf("\e[1;41mERROR FORK\e[0m\n");
	free_all(proj, 0);
}
