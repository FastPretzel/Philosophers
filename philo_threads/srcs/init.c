/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:27:02 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 13:49:42 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (ft_atoi(argv[1]) > 200)
		return (0);
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
		if (ft_atoi(argv[i]) <= 0)
			return (0);
	}
	return (1);
}

static int	init_phils(t_proj *proj)
{
	int				i;
	t_phil			*phils;

	phils = malloc(sizeof(t_phil) * proj->phils_cnt);
	if (!phils)
		return (0);
	i = -1;
	while (++i < proj->phils_cnt)
	{
		phils[i].id = i + 1;
		phils[i].left_fork = i;
		if (i != proj->phils_cnt - 1)
			phils[i].right_fork = i + 1;
		else
			phils[i].right_fork = 0;
		phils[i].eat_cnt = 0;
		phils[i].dead = 0;
		proj->args[i].phil = &phils[i];
		proj->args[i].phils_malloc = phils;
	}
	return (1);
}

static int	init_mutex(t_proj *proj)
{
	int				i;
	t_args			*args;
	pthread_mutex_t	*forks;

	args = proj->args;
	forks = malloc(sizeof(pthread_mutex_t) * proj->phils_cnt);
	if (!forks)
		return (0);
	if (pthread_mutex_init(&proj->data_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&proj->write, NULL))
		return (0);
	i = -1;
	while (++i < proj->phils_cnt)
		if (pthread_mutex_init(&forks[i], NULL))
			return (0);
	i = -1;
	while (++i < proj->phils_cnt)
		args[i].forks = forks;
	return (1);
}

static void	init_timers(char **argv, t_proj *proj)
{
	int	i;

	i = -1;
	while (++i < proj->phils_cnt)
	{
		proj->args[i].sleep_time = ft_atoi(argv[4]);
		proj->args[i].eat_time = ft_atoi(argv[3]);
		proj->args[i].time_to_die = ft_atoi(argv[2]);
		proj->args[i].p_proj = proj;
	}
}

int	init(int argc, char **argv, t_proj *proj)
{
	if ((argc != 5 && argc != 6) || !valid_argv(argc, argv))
		return (ERROR_MALLOC);
	proj->phils_cnt = ft_atoi(argv[1]);
	proj->args = malloc(sizeof(t_args) * proj->phils_cnt);
	if (!proj->args)
		return (ERROR_MALLOC);
	if (!init_mutex(proj))
		return (ERROR_MUTEX);
	if (argc == 6)
	{
		proj->num_of_eat = ft_atoi(argv[5]);
		if (proj->num_of_eat < 1)
			return (ERROR_ARGS);
	}
	else
		proj->num_of_eat = -1;
	proj->full_cnt = 0;
	proj->stop = 0;
	init_timers(argv, proj);
	if (!init_phils(proj))
		return (ERROR_PHILOS);
	return (0);
}
