/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/06/25 01:09:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	start_the_meal(t_philosophers *ph)
// {
// 	pthread_t		philo;
// 	pthread_attr_t	attr;

// 	pthread_create(&philo, &attr, NULL, NULL);
// }

void	__print_struct__(t_philosophers *ph)
{
	printf("{\n");
	printf("    ph->philo_nbr :  [%u]\n", ph->philo_nbr);
	printf("    ph->time2die :   [%u]\n", ph->time2die);
	printf("    ph->time2eat :   [%u]\n", ph->time2eat);
	printf("    ph->time2sleep : [%u]\n", ph->time2sleep);
	printf("    ph->nbr2eat :    [%u]\n", ph->nbr2eat);
	printf("    ph->philos :     [%p]\n", ph->philos);
	printf("}\n");
}

int	init_the_meal(int ac, char **av, t_philosophers *ph)
{
	memset(ph, 0, sizeof(t_philosophers));
	ph->philo_nbr = ft_atoi(av[1]);
	ph->time2die = ft_atoi(av[2]);
	ph->time2eat = ft_atoi(av[3]);
	ph->time2sleep = ft_atoi(av[4]);
	if (6 == ac)
		ph->nbr2eat = ft_atoi(av[5]);
	ph->philos = (pthread_t *)malloc(ph->philo_nbr * sizeof(pthread_t));
	if (!ph->philos)
		return (FALSE);
	__print_struct__(ph);
	return (TRUE);
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av)
{
	t_philosophers	ph;

	if (ac < MIN_ARGS || ac > MAX_ARGS)
	{
		printf("usage: ./%s number_of_philosophers time_to_die time_to_eat " \
			"time_to_sleep  [number_of_times_each_philosopher_must_eat]\n",
			PROG_NAME);
		return (EXIT_FAILURE);
	}
	if (FALSE == init_the_meal(ac, av, &ph))
	{
		printf("%s%d: Malloc Error\n", __FILE__, __LINE__);
		ft_free_all(&ph, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}

	// start_the_meal(&ph);

	ft_free_all(&ph, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
