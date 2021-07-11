/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:45:31 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 15:22:50 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	everyone_got_his_meals(void)
{
	int	count;
	int	philo_nbr;
	int	to_eat;
	int	i;

	sem_wait(singleton()->sem_monitor);
	to_eat = singleton()->nbr2eat;
	philo_nbr = singleton()->philo_nbr;
	sem_post(singleton()->sem_monitor);
	if (0 == to_eat)
		return (FALSE);
	count = 0;
	i = 0;
	while (i < philo_nbr)
	{
		sem_wait(singleton()->sem_monitor);
		if (singleton()->philos[i++].nbr_eaten >= to_eat)
		{
			sem_post(singleton()->sem_monitor);
			++count;
		}
		else
			sem_post(singleton()->sem_monitor);
	}
	return (count == philo_nbr);
}

int	is_alive(int philo_id)
{
	uint64_t	isdead;

	sem_wait(singleton()->sem_monitor);
	if (singleton()->died)
	{
		sem_post(singleton()->sem_monitor);
		return (FALSE);
	}
	sem_post(singleton()->sem_monitor);
	if (singleton()->philos[philo_id].time2die != 0)
	{
		isdead = __current_time_ms__() - singleton()->philos[philo_id].time2die;
		if (isdead > (uint64_t)singleton()->time2die)
		{
			print_status(philo_id, STAT_DIED);
			sem_wait(singleton()->sem_monitor);
			singleton()->died = philo_id + 1;
			sem_post(singleton()->sem_monitor);
			return (FALSE);
		}
	}
	return (TRUE);
}
