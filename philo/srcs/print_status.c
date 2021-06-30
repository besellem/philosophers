/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:38:24 by besellem          #+#    #+#             */
/*   Updated: 2021/06/30 18:22:15 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*g_status[] = {
	[STAT_THINKING] = "is thinking",
	[STAT_TAKEN_FORK] = "has taken a fork",
	[STAT_EATING] = "is eating",
	[STAT_SLEEPING] = "is sleeping",
	[STAT_TAKEN_DIED] = "died"
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

	printf("%lld %3d %s\n", __ms, philo_id, g_status[status]);
}
