/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:54:43 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 16:16:02 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philosophers	*singleton(void)
{
	static t_philosophers	*ph = NULL;

	if (!ph)
	{
		ph = (t_philosophers *)malloc(sizeof(t_philosophers));
		if (!ph)
		{
			printf("%s%d: Malloc Error\n", __FILE__, __LINE__);
			return (NULL);
		}
		memset(ph, 0, sizeof(t_philosophers));
	}
	return (ph);
}

int	ft_free_all(int code)
{
	int	i;

	if (singleton())
	{
		if (singleton()->philos)
		{
			i = 0;
			while (i < singleton()->philo_nbr)
			{
				printf(B_RED "killing philo[%d] -> pid[%d]" CLR_COLOR "\n",
					i, singleton()->philos[i].pid);
				kill(singleton()->philos[i].pid, SIGKILL);
				++i;
			}
			ft_memdel((void **)&singleton()->philos);
		}
		sem_close(singleton()->sem_end);
		sem_close(singleton()->forks);
		sem_close(singleton()->sem_monitor);
		sem_unlink(_SEM_END_);
		sem_unlink(_SEM_FORKS_);
		sem_unlink(_SEM_MONITOR_);
		memset(singleton(), 0, sizeof(t_philosophers));
		free(singleton());
	}
	return (code);
}
