/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:51:33 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 15:52:41 by besellem         ###   ########.fr       */
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
	// sem_wait(singleton()->sem_monitor);
	++singleton()->philos[philo_id].nbr_eaten;
	// sem_post(singleton()->sem_monitor);
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
