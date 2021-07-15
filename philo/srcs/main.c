/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/15 16:10:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*a_philo_life(void *content)
{
	const int	id = (int)((t_philo *)content)->id;

	singleton()->philos[id].time2die = __current_time_ms__();
	while (is_alive(id) && !everyone_got_his_meals())
	{
		if (1 == singleton()->philo_nbr)
		{
			print_status(id, STAT_TAKEN_FORK);
			__usleep__(id, singleton()->time2die);
		}
		else
		{
			step_eat(id);
			step_drop_forks(id);
			step_sleep(id);
			print_status(id, STAT_THINKING);
			__usleep__(id, singleton()->time2eat - singleton()->time2sleep);
		}
	}
	return (NULL);
}

static void	start_the_meal(t_philosophers *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_nbr)
		pthread_mutex_init(&ph->forks[i++], NULL);
	pthread_mutex_init(&ph->__monitor, NULL);
	i = 0;
	ph->start_time_ms = __current_time_ms__();
	while (i < ph->philo_nbr)
	{
		pthread_create(&ph->philos[i].philo, NULL, &a_philo_life,
			&ph->philos[i]);
		++i;
	}
	i = 0;
	while (i < ph->philo_nbr)
		pthread_join(ph->philos[i++].philo, NULL);
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
