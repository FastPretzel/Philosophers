/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:19 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 15:03:08 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	valid_argv(int argc, char **argv)
{
	int	i;
	int	j;

	if (ft_atoi(argv[1]) > 200)
		return (0);
	i = 0;
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
		phils[i].eat_cnt = 0;
		phils[i].p_proj = proj;
		proj->phils = phils;
	}
	sem_unlink("forks");
	sem_unlink("write");
	proj->forks = sem_open("forks", O_CREAT | O_EXCL, 644, proj->phils_cnt);
	proj->write = sem_open("write", O_CREAT | O_EXCL, 644, 1);
	return (1);
}

int	init(int argc, char **argv, t_proj *proj)
{
	if ((argc != 5 && argc != 6) || !valid_argv(argc, argv))
		return (ERROR_ARGS);
	proj->phils_cnt = ft_atoi(argv[1]);
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
	proj->sleep_time = ft_atoi(argv[4]);
	proj->eat_time = ft_atoi(argv[3]);
	proj->time_to_die = ft_atoi(argv[2]);
	if (!init_phils(proj))
		return (ERROR_PHILOS);
	return (0);
}
