/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:38:24 by besellem          #+#    #+#             */
/*   Updated: 2021/07/07 17:21:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*g_status[] = {
	[STAT_THINKING] = "is thinking",
	[STAT_TAKEN_FORK] = "has taken a fork",
	[STAT_EATING] = "is eating",
	[STAT_SLEEPING] = "is sleeping",
	[STAT_DIED] = B_RED "died" CLR_COLOR
};

uint64_t	__current_time_ms__(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000) + (t.tv_usec / 1000));
}

void	print_status(int philo_id, int status)
{
	const uint64_t	__ms = __current_time_ms__() - singleton()->start_time_ms;

	pthread_mutex_lock(&singleton()->__monitor);
	if (singleton()->died != FALSE)
	{
		pthread_mutex_unlock(&singleton()->__monitor);
		return ;
	}
	pthread_mutex_unlock(&singleton()->__monitor);
	if (__everyone_got_his_meals__())
		return ;
	if (STAT_EATING == status)
		printf("[%7llu] %3d %s for the %d time\n", __ms, philo_id + 1, g_status[status], singleton()->philos[philo_id].nbr_eaten);
	else
		printf("[%7llu] %3d %s\n", __ms, philo_id + 1, g_status[status]);
}
