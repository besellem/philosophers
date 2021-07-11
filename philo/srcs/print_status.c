/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:38:24 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 15:01:17 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#if defined(__APPLE__) && defined(__MACH__)
# define MS_FMT "llu"
#else
# define MS_FMT "lu"
#endif

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
	pthread_mutex_lock(&singleton()->__monitor);
	printf("[%7" MS_FMT "] %3d %s\n", __ms, philo_id + 1, g_status[status]);
	pthread_mutex_unlock(&singleton()->__monitor);
}
