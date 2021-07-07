/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:26:57 by besellem          #+#    #+#             */
/*   Updated: 2021/07/07 17:33:34 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define _MS_CONST_ 400

void	__usleep__(int philo_id, int ms)
{
	const uint64_t	now = __current_time_ms__();

	while (is_alive(philo_id) && (__current_time_ms__() - now) < (uint64_t)ms)
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
	++singleton()->philos[philo_id].nbr_eaten;
	print_status(philo_id, STAT_EATING);
	singleton()->philos[philo_id].time2die = __current_time_ms__();
	__usleep__(philo_id, singleton()->time2eat);
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
	__usleep__(philo_id, singleton()->time2sleep);
}

int	__everyone_got_his_meals__(void)
{
	int	count;
	int	to_eat;
	int	i;

	pthread_mutex_lock(&singleton()->__monitor);
	to_eat = singleton()->nbr2eat;
	pthread_mutex_unlock(&singleton()->__monitor);
	if (0 == to_eat)
		return (FALSE);
	count = 0;
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		pthread_mutex_lock(&singleton()->__monitor);
		if (singleton()->philos[i].nbr_eaten >= to_eat)
		{
			pthread_mutex_unlock(&singleton()->__monitor);
			++count;
		}
		else
			pthread_mutex_unlock(&singleton()->__monitor);
		++i;
	}
	// printf("count[%d] philo_nbr[%d]\n", count, singleton()->philo_nbr);
	return (count == singleton()->philo_nbr);
}

int	is_alive(int philo_id)
{
	uint64_t	isdead;

	pthread_mutex_lock(&singleton()->__monitor);
	if (singleton()->died)
	{
		pthread_mutex_unlock(&singleton()->__monitor);
		return (FALSE);
	}
	pthread_mutex_unlock(&singleton()->__monitor);
	if (philo_id != EMPTY && singleton()->philos[philo_id].time2die != 0)
	{
		isdead = __current_time_ms__() - singleton()->philos[philo_id].time2die;
		if (isdead >= (uint64_t)singleton()->time2die)
		{
			print_status(philo_id, STAT_DIED);
			pthread_mutex_lock(&singleton()->__monitor);
			singleton()->died = philo_id + 1;
			pthread_mutex_unlock(&singleton()->__monitor);
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	*a_philo_life(void *content)
{
	const int	id = (int)((t_philo *)content)->id;

	singleton()->philos[id].time2die = __current_time_ms__();
	while (is_alive(id) && !__everyone_got_his_meals__())
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
		}
	}
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
	start_the_meal(singleton());
	return (ft_free_all(EXIT_SUCCESS));
}
