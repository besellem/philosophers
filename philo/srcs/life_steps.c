/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:51:33 by besellem          #+#    #+#             */
/*   Updated: 2021/07/08 17:51:47 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	__usleep__(philo_id, singleton()->time2eat);
	pthread_mutex_lock(&singleton()->__monitor);
	++singleton()->philos[philo_id].nbr_eaten;
	pthread_mutex_unlock(&singleton()->__monitor);
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
