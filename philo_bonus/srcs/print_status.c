/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:38:24 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 12:30:56 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

const char	*g_status[] = {
	[STAT_THINKING] = "is thinking",
	[STAT_TAKEN_FORK] = "has taken a fork",
	[STAT_EATING] = "is eating",
	[STAT_SLEEPING] = "is sleeping",
	[STAT_DIED] = B_RED "died" CLR_COLOR
};

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
	if (everyone_got_his_meals())
		return ;
	printf("[%7llu] %3d %s\n", __ms, philo_id + 1, g_status[status]);
}
