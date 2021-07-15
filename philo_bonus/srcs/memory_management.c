/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:54:43 by besellem          #+#    #+#             */
/*   Updated: 2021/07/15 16:41:00 by besellem         ###   ########.fr       */
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
		__close_semaphores__();
		__unlink_semaphores__();
		if (singleton()->philos)
		{
			i = 0;
			while (i < singleton()->philo_nbr)
			{
				kill(singleton()->philos[i++].pid, SIGKILL);
			}
			ft_memdel((void **)&singleton()->philos);
		}
		memset(singleton(), 0, sizeof(t_philosophers));
		free(singleton());
	}
	return (code);
}
