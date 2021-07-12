/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:38:24 by besellem          #+#    #+#             */
/*   Updated: 2021/07/12 12:16:10 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_status(t_philosophers *ph, int philo_id, int status)
{
	const uint64_t	__ms = __current_time_ms__() - ph->start_time_ms;

	if (ph->died != FALSE)
		return ;
	if (everyone_got_his_meals(ph))
		return ;
	printf("[%7" MS_FMT "] %3d %s\n", __ms, philo_id + 1, g_status[status]);
}
