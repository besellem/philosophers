/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:45:31 by besellem          #+#    #+#             */
/*   Updated: 2021/07/13 13:00:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	everyone_got_his_meals(void)
{
	const int	philo_nbr = singleton()->philo_nbr;
	const int	to_eat = singleton()->nbr2eat;
	int			count;
	int			i;

	if (0 == to_eat)
		return (FALSE);
	count = 0;
	i = 0;
	while (i < philo_nbr)
	{
		if (singleton()->philos[i++].nbr_eaten >= to_eat)
			++count;
	}
	return (count == philo_nbr);
}

int	is_alive(int philo_id)
{
	uint64_t	isdead;

	if (singleton()->died)
		return (FALSE);
	if (singleton()->philos[philo_id].time2die != 0)
	{
		isdead = __current_time_ms__() - singleton()->philos[philo_id].time2die;
		if (isdead > (uint64_t)singleton()->time2die)
		{
			sem_post(singleton()->__sem_glob);
			print_status(philo_id, STAT_DIED);
			sem_wait(singleton()->sem_print);
			singleton()->died = philo_id + 1;
			return (FALSE);
		}
	}

	// printf(B_RED "GOT THEIR MEALS: %d" CLR_COLOR "\n", everyone_got_his_meals());

	// if (everyone_got_his_meals())
	// {
	// 	sem_post(singleton()->__sem_glob);
	// 	sem_wait(singleton()->sem_print);
	// 	singleton()->died = philo_id + 1;
	// 	return (FALSE);
	// }

	return (TRUE);
}
