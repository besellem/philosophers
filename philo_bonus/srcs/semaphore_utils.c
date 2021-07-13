/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:51:42 by besellem          #+#    #+#             */
/*   Updated: 2021/07/13 18:47:50 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define __SEM_MODE__ 0644

// struct s_sem_open
// {
// 	char			*name;
// 	int				value;
// 	sem_t			*ptr;
// };

// int	__open_semaphores__(t_philosophers *ph)
// {
// 	struct s_sem_open	table[] = {
// 		{_SEM_FORKS_, ph->philo_nbr, ph->forks},
// 		{_SEM_MONITOR_, 1, ph->sem_monitor},
// 		{NULL, 0, NULL}
// 	};
// 	size_t				i;

// 	i = 0;
// 	while (table[i].name)
// 	{
// 		table[i].ptr = sem_open(table[i].name, O_CREAT, 0644, table[i].value);
// 		if (SEM_FAILED == table[i].ptr)
// 		{
// 			printf("%s%d: sem_open() error\n", __FILE__, __LINE__);
// 			return (FAILURE);
// 		}
// 		++i;
// 	}
// 	return (SUCCESS);
// }

int	__open_semaphores__(void)
{
	t_philosophers	*ph;
	int				check;

	ph = singleton();
	check = SUCCESS;
	ph->__sem_glob = sem_open(_SEM_GLOB_, O_CREAT, __SEM_MODE__, 0);
	if (SEM_FAILED == ph->__sem_glob)
		check = FAILURE;
	ph->forks = sem_open(_SEM_FORKS_, O_CREAT, __SEM_MODE__, ph->philo_nbr);
	if (SEM_FAILED == ph->forks)
		check = FAILURE;
	ph->sem_print = sem_open(_SEM_PRINT_, O_CREAT, __SEM_MODE__, 1);
	if (SEM_FAILED == ph->sem_print)
		check = FAILURE;
	ph->sem_meal = sem_open(_SEM_MEAL_, O_CREAT, __SEM_MODE__, 0);
	if (SEM_FAILED == ph->sem_meal)
		check = FAILURE;
	if (FAILURE == check)
		printf("%s%d: sem_open() error\n", __FILE__, __LINE__);
	return (check);
}

void	__close_semaphores__(void)
{
	sem_close(singleton()->forks);
	sem_close(singleton()->sem_print);
	sem_close(singleton()->sem_meal);
	sem_close(singleton()->__sem_glob);
}

void	__unlink_semaphores__(void)
{
	sem_unlink(_SEM_FORKS_);
	sem_unlink(_SEM_PRINT_);
	sem_unlink(_SEM_MEAL_);
	sem_unlink(_SEM_GLOB_);
}
