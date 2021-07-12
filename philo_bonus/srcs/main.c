/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/12 12:18:27 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	a_philo_life(t_philosophers *ph, int id)
{
	ph->philos[id].time2die = __current_time_ms__();
	while (is_alive(ph, id) && !everyone_got_his_meals(ph))
	// while (TRUE)
	{
		// if (1 == ph->philo_nbr)
		// {
		// 	print_status(id, STAT_TAKEN_FORK);
		// 	__usleep__(ph, id, ph->time2die);
		// }
		// else
		// {
			step_eat(ph, id);
			step_drop_forks(ph);
			step_sleep(ph, id);
			print_status(ph, id, STAT_THINKING);
		// }
	}
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
			ph->start_time_ms = __current_time_ms__();
			WARN()
			__open_semaphores__(ph);
			WARN()
			a_philo_life(ph, i);
			WARN()
			__close_semaphores__(ph);
			ft_free_all(SUCCESS);
		}
		// else
		// 	waitpid(ph->philos[i].pid, NULL, 0);
		++i;
	}
}

void	*monitoring(__attribute__((unused)) void *unused)
{
	ERR()
	sem_wait(singleton()->sem_end);
	ERR()
	return (NULL);
}

static void	start_the_meal(t_philosophers *ph)
{
	ph->start_time_ms = __current_time_ms__();
	pthread_create(&ph->monitor, NULL, monitoring, NULL);
	pthread_join(ph->monitor, NULL);
	LOG()
	start_processes(ph);
	ERR()
	ERR()
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
