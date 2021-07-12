/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:51:33 by besellem          #+#    #+#             */
/*   Updated: 2021/07/12 12:16:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	step_eat(t_philosophers *ph, int philo_id)
{
	sem_wait(ph->forks);
	print_status(ph, philo_id, STAT_TAKEN_FORK);
	sem_wait(ph->forks);
	print_status(ph, philo_id, STAT_TAKEN_FORK);
	print_status(ph, philo_id, STAT_EATING);
	ph->philos[philo_id].time2die = __current_time_ms__();
	__usleep__(ph, philo_id, ph->time2eat);
	++ph->philos[philo_id].nbr_eaten;
}

void	step_drop_forks(t_philosophers *ph)
{
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	step_sleep(t_philosophers *ph, int philo_id)
{
	print_status(ph, philo_id, STAT_SLEEPING);
	__usleep__(ph, philo_id, ph->time2sleep);
}
