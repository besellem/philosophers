/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:45:31 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 14:24:16 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	everyone_got_his_meals(void)
{
	int	count;
	int	philo_nbr;
	int	to_eat;
	int	i;

	pthread_mutex_lock(&singleton()->__monitor);
	to_eat = singleton()->nbr2eat;
	philo_nbr = singleton()->philo_nbr;
	pthread_mutex_unlock(&singleton()->__monitor);
	if (0 == to_eat)
		return (FALSE);
	count = 0;
	i = 0;
	while (i < philo_nbr)
	{
		pthread_mutex_lock(&singleton()->__monitor);
		if (singleton()->philos[i++].nbr_eaten >= to_eat)
		{
			pthread_mutex_unlock(&singleton()->__monitor);
			++count;
		}
		else
			pthread_mutex_unlock(&singleton()->__monitor);
	}
	return (count == philo_nbr);
}

// int	is_alive(int philo_id)
// {
// 	uint64_t	isdead;

// 	pthread_mutex_lock(&singleton()->__monitor);
// 	if (singleton()->died)
// 	{
// 		pthread_mutex_unlock(&singleton()->__monitor);
// 		return (FALSE);
// 	}
// 	pthread_mutex_unlock(&singleton()->__monitor);
// 	if (singleton()->philos[philo_id].time2die != 0)
// 	{
// 		isdead = __current_time_ms__() - singleton()->philos[philo_id].time2die;
// 		if (isdead > (uint64_t)singleton()->time2die)
// 		{
// 			print_status(philo_id, STAT_DIED);
// 			pthread_mutex_lock(&singleton()->__monitor);
// 			singleton()->died = philo_id + 1;
// 			pthread_mutex_unlock(&singleton()->__monitor);
// 			return (FALSE);
// 		}
// 	}
// 	return (TRUE);
// }

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
	if (singleton()->philos[philo_id].time2die != 0)
	{
		isdead = __current_time_ms__() - singleton()->philos[philo_id].time2die;
		if (isdead > (uint64_t)singleton()->time2die)
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
