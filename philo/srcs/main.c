/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/06 18:26:17 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define _MS_CONST_ 500

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

void	__usleep__(int ms)
{
	const uint64_t	now = __current_time_ms__();

	while (__current_time_ms__() - now < (uint64_t)ms)
		usleep(_MS_CONST_);
}

void	step_eat(int philo_id)
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
	singleton()->philos[philo_id].time2die = __current_time_ms__();
	__usleep__(singleton()->time2eat);
}

void	step_drop_forks(int philo_id)
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

void	step_sleep(int philo_id)
{
	print_status(philo_id, STAT_SLEEPING);
	__usleep__(singleton()->time2sleep);
}

void	*host(__attribute__((unused)) void *none)
{
	while (TRUE)
	{
		pthread_mutex_lock(&singleton()->__monitor);
		if (FALSE != singleton()->died)
		{
			pthread_mutex_unlock(&singleton()->__monitor);
			break ;
		}
		pthread_mutex_unlock(&singleton()->__monitor);
	}
	return (NULL);
}

static void	*a_philo_life(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	while (FALSE == singleton()->died)
	{
		step_eat(philo->id);
		step_drop_forks(philo->id);
		step_sleep(philo->id);
		print_status(philo->id, STAT_THINKING);
		if ((__current_time_ms__() - philo->time2die) >= (uint64_t)singleton()->time2die)
		{
			pthread_mutex_lock(&singleton()->__monitor);
			if (FALSE == singleton()->died)
				print_status(philo->id, STAT_DIED);
			singleton()->died = philo->id;
			pthread_mutex_unlock(&singleton()->__monitor);
			// exit(1);
			break ;
		}
	}
	// printf(B_RED "philo_id -> [%d]" CLR_COLOR "\n", philo->id + 1);
	return (NULL);
}

void	start_the_meal(t_philosophers *ph)
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
	
	// host(NULL);

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
	if (FAILURE == init_the_meal(ac, av, singleton()))
		return (ft_free_all(EXIT_FAILURE));
	// __print_struct__(singleton());
	start_the_meal(singleton());
	return (ft_free_all(EXIT_SUCCESS));
}
