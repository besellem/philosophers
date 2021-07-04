/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/04 17:40:53 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	__eat__(int philo_id)
{
	const int	left = philo_id;
	const int	right = (philo_id + 1) % singleton()->philo_nbr;

	if (0 == (philo_id % 2))
	{
		pthread_mutex_lock(&singleton()->forks[left]);
		print_status(philo_id, STAT_TAKEN_FORK);
		pthread_mutex_lock(&singleton()->forks[right]);
		print_status(philo_id, STAT_TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(&singleton()->forks[right]);
		print_status(philo_id, STAT_TAKEN_FORK);
		pthread_mutex_lock(&singleton()->forks[left]);
		print_status(philo_id, STAT_TAKEN_FORK);
	}
	print_status(philo_id, STAT_EATING);
	usleep(singleton()->time2eat);
}

void	drop_forks(int philo_id)
{
	const int	left = philo_id;
	const int	right = (philo_id + 1) % singleton()->philo_nbr;

	if (0 == (philo_id % 2))
	{
		pthread_mutex_unlock(&singleton()->forks[right]);
		pthread_mutex_unlock(&singleton()->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&singleton()->forks[left]);
		pthread_mutex_unlock(&singleton()->forks[right]);
	}
}

void	__sleep__(int philo_id)
{
	print_status(philo_id, STAT_SLEEPING);
	usleep(singleton()->time2sleep);
}

void	__think__(t_philo *philo)
{
	print_status(philo->id, STAT_THINKING);
	// pthread_mutex_lock(&singleton()->__monitor);
	philo->time2die = __current_time_ms__();
	// pthread_mutex_unlock(&singleton()->__monitor);
}

static void	*__philo_process_(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	while (FALSE == singleton()->died)
	{
		__eat__(philo->id);
		drop_forks(philo->id);
		__sleep__(philo->id);
		__think__(philo);
		if ((__current_time_ms__() - philo->time2die) >= (uint64_t)singleton()->time2die)
		{
			print_status(philo->id, STAT_DIED);
			singleton()->died = TRUE;
			// exit(1);
			break ;
		}
	}
	return (NULL);
}

void	start_the_meal(t_philosophers *ph)
{
	int	i;

	i = 0;
	ph->start_time_ms = __current_time_ms__();
	while (i < ph->philo_nbr)
	{
		pthread_create(&ph->philos[i].philo, NULL, &__philo_process_, &ph->philos[i]);
		++i;
	}

	// host()

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
	if (NULL == singleton())
	{
		printf("%s%d: Malloc Error\n", __FILE__, __LINE__);
		return (EXIT_FAILURE);
	}
	if (FAILURE == init_the_meal(ac, av, singleton()))
		return (ft_free_all(EXIT_FAILURE));
	
	__print_struct__(singleton());
	
	start_the_meal(singleton());
	return (ft_free_all(EXIT_SUCCESS));
}
