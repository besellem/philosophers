/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:45:31 by besellem          #+#    #+#             */
/*   Updated: 2021/07/12 12:15:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	everyone_got_his_meals(t_philosophers *ph)
{
	const int	philo_nbr = ph->philo_nbr;
	const int	to_eat = ph->nbr2eat;
	int			count;
	int			i;

	if (0 == to_eat)
		return (FALSE);
	count = 0;
	i = 0;
	while (i < philo_nbr)
	{
		if (ph->philos[i++].nbr_eaten >= to_eat)
			++count;
	}
	return (count == philo_nbr);
}

int	is_alive(t_philosophers *ph, int philo_id)
{
	uint64_t	isdead;

	if (ph->died)
		return (FALSE);
	if (ph->philos[philo_id].time2die != 0)
	{
		isdead = __current_time_ms__() - ph->philos[philo_id].time2die;
		if (isdead > (uint64_t)ph->time2die)
		{
			print_status(ph, philo_id, STAT_DIED);
			ph->died = philo_id + 1;
			sem_post(ph->sem_end);
			return (FALSE);
		}
	}
	return (TRUE);
}
