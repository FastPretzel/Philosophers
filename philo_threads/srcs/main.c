/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:26:57 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 16:23:31 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitoring(t_proj *proj)
{
	int		i;

	i = -1;
	while (++i < proj->phils_cnt && !proj->stop)
	{
		pthread_mutex_lock(&proj->data_mutex);
		if (proj->full_cnt == proj->phils_cnt)
		{
			pthread_mutex_lock(&proj->write);
			proj->stop = 1;
			printf("\e[38;5;141m%lu\e[0m \e[38;5;82m%s\e[0m\n", \
					ft_time() - proj->start_time, "ALL PHILOS ARE FULL");
		}
		if (proj->args[i].phil->dead)
		{
			pthread_mutex_lock(&proj->write);
			proj->stop = 1;
			printf("\e[38;5;141m%lu\e[0m \e[38;5;11m%d\e[0m \e[38;5;160m%s\e[0m\n", \
					ft_time() - proj->start_time, proj->args->phil->id, "DIED");
		}
		i == proj->phils_cnt - 1 && (i = -1);
		pthread_mutex_unlock(&proj->data_mutex);
	}
	pthread_mutex_lock(&proj->data_mutex);
	ft_usleep(1000);
}

int	main(int argc, char **argv)
{
	int			i;
	int			err_code;
	pthread_t	pthr;
	t_proj		proj;

	err_code = init(argc, argv, &proj);
	if (err_code)
	{
		error(proj.args, err_code);
		return (0);
	}
	i = -1;
	proj.start_time = ft_time();
	while (++i < proj.phils_cnt)
	{
		if (pthread_create(&pthr, NULL, start, &proj.args[i]))
		{
			error(proj.args, ERROR_PTHREAD);
			return (0);
		}
		pthread_detach(pthr);
	}
	monitoring(&proj);
	free_all(proj.args);
	return (0);
}
