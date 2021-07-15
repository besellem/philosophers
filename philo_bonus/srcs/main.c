/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/15 17:35:50 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	a_philo_life(t_philosophers *ph, int id)
{
	int	i;

	ph->philos[id].time2die = __current_time_ms__();
	while (is_alive(id) && !everyone_got_his_meals())
	{
		if (1 == ph->philo_nbr)
		{
			print_status(id, STAT_TAKEN_FORK);
			__usleep__(id, ph->time2die);
		}
		else
		{
			step_eat(id);
			step_drop_forks();
			step_sleep(id);
			print_status(id, STAT_THINKING);
			__usleep__(id, singleton()->time2eat - singleton()->time2sleep);
		}
	}
	sem_post(singleton()->sem_print);
	i = -1;
	while (++i < singleton()->philo_nbr)
		sem_post(singleton()->sem_meal);
	sem_wait(singleton()->sem_print);
}

static void	start_processes(t_philosophers *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_nbr)
	{
		ph->philos[i].pid = fork();
		if (ph->philos[i].pid < 0)
			return ;
		else if (0 == ph->philos[i].pid)
		{
			__open_semaphores__();
			a_philo_life(ph, i);
			__close_semaphores__();
		}
		++i;
	}
}

void	*monitoring(__attribute__((unused)) void *unused)
{
	int	i;

	if (0 == singleton()->nbr2eat)
		return (NULL);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		sem_wait(singleton()->sem_meal);
		++i;
	}
	ft_free_all(EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
	return (NULL);
}

static void	start_the_meal(t_philosophers *ph)
{
	ph->start_time_ms = __current_time_ms__();
	start_processes(ph);
	pthread_create(&ph->monitor, NULL, monitoring, NULL);
	pthread_join(ph->monitor, NULL);
	sem_wait(ph->__sem_glob);
}

int	main(int ac, char **av)
{
	if (ac < MIN_ARGS || ac > MAX_ARGS)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (FAILURE == dress_the_table(ac, av, singleton()))
		return (ft_free_all(EXIT_FAILURE));
	start_the_meal(singleton());
	return (ft_free_all(EXIT_SUCCESS));
}
