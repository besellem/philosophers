/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:51:33 by besellem          #+#    #+#             */
/*   Updated: 2021/07/13 18:50:10 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	step_eat(int philo_id)
{
	sem_wait(singleton()->forks);
	print_status(philo_id, STAT_TAKEN_FORK);
	sem_wait(singleton()->forks);
	print_status(philo_id, STAT_TAKEN_FORK);
	print_status(philo_id, STAT_EATING);
	singleton()->philos[philo_id].time2die = __current_time_ms__();
	__usleep__(philo_id, singleton()->time2eat);
	++singleton()->philos[philo_id].nbr_eaten;
	if (singleton()->philos[philo_id].nbr_eaten == singleton()->nbr2eat)
	{
		LOG()
		sem_post(singleton()->sem_meal);
	}
}

void	step_drop_forks(void)
{
	sem_post(singleton()->forks);
	sem_post(singleton()->forks);
}

void	step_sleep(int philo_id)
{
	print_status(philo_id, STAT_SLEEPING);
	__usleep__(philo_id, singleton()->time2sleep);
}
