/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:54:43 by besellem          #+#    #+#             */
/*   Updated: 2021/07/04 17:20:30 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosophers	*singleton(void)
{
	static t_philosophers	*ph = NULL;

	if (!ph)
	{
		ph = (t_philosophers *)malloc(sizeof(t_philosophers));
		if (!ph)
			return (NULL);
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
			ft_memdel((void **)&singleton()->philos);
		if (singleton()->forks)
		{
			i = 0;
			while (i < singleton()->philo_nbr)
				pthread_mutex_destroy(&singleton()->forks[i]);
			ft_memdel((void **)&singleton()->forks);
		}
		pthread_mutex_destroy(&singleton()->__monitor);
		memset(singleton(), 0, sizeof(t_philosophers));
		free(singleton());
	}
	return (code);
}
