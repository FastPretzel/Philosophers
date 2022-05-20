/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:16 by cgoth             #+#    #+#             */
/*   Updated: 2022/04/15 15:03:17 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	monitoring(t_proj *proj)
{
	int	status;

	while (1)
	{
		waitpid(-1, &status, 0);
		status = status >> 8;
		if (status == DEAD)
		{
			return ;
		}
		if (status == FULL)
		{
			proj->full_cnt++;
		}
		if (proj->full_cnt == proj->phils_cnt)
		{
			sem_wait(proj->write);
			printf("\e[38;5;141m%lu\e[0m \e[38;5;82m%s\e[0m\n", \
					ft_time() - proj->start_time, "ALL PHILOS ARE FULL");
			return ;
		}
	}
}

void	forking(t_proj *proj)
{
	int		i;
	pid_t	pid;

	i = -1;
	proj->start_time = ft_time();
	while (++i < proj->phils_cnt)
	{
		pid = fork();
		if (!pid)
			start(&proj->phils[i]);
		else if (pid > 0)
			proj->phils[i].pid = pid;
		else
			error(proj, ERROR_FORK);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		err_code;
	t_proj	proj;

	err_code = init(argc, argv, &proj);
	if (err_code)
	{
		error(&proj, err_code);
		return (0);
	}
	forking(&proj);
	monitoring(&proj);
	i = -1;
	while (++i < proj.phils_cnt)
		kill(proj.phils[i].pid, 9);
	free_all(&proj, 0);
	return (0);
}
