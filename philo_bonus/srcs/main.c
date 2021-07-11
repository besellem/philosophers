/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 16:07:28 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	a_philo_life(int id)
{
	singleton()->philos[id].time2die = __current_time_ms__();
	// while (is_alive(id) && !everyone_got_his_meals())
	while (TRUE)
	{
		// if (1 == singleton()->philo_nbr)
		// {
		// 	print_status(id, STAT_TAKEN_FORK);
		// 	__usleep__(id, singleton()->time2die);
		// }
		// else
		// {
			step_eat(id);
			step_drop_forks();
			step_sleep(id);
			print_status(id, STAT_THINKING);
		// }
	}
}

// static void	start_the_meal(t_philosophers *ph)
// {
// 	int	i;

// 	i = 0;
// 	ph->start_time_ms = __current_time_ms__();
// 	while (i < ph->philo_nbr)
// 	{
// 		pthread_create(&ph->philos[i].philo, NULL, &a_philo_life,
// 			&ph->philos[i]);
// 		++i;
// 	}
// 	i = 0;
// 	while (i < ph->philo_nbr)
// 		pthread_join(ph->philos[i++].philo, NULL);
// }

int	main(int ac, char **av)
{
	if (ac < MIN_ARGS || ac > MAX_ARGS)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (FAILURE == dress_the_table(ac, av, singleton()))
		return (ft_free_all(EXIT_FAILURE));
	// start_the_meal(singleton());
	return (ft_free_all(EXIT_SUCCESS));
}
