/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_the_meal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:42:34 by besellem          #+#    #+#             */
/*   Updated: 2021/06/30 17:42:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	__get_arg__(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9') || i > UINT32_MAXLEN)
			return (INVALID);
		++i;
	}
	return (ft_atoi(arg));
}

static int	__check_args__(int ac, char **av, t_philosophers *ph)
{
	ph->philo_nbr = __get_arg__(av[1]);
	ph->time2die = __get_arg__(av[2]);
	ph->time2eat = __get_arg__(av[3]);
	ph->time2sleep = __get_arg__(av[4]);
	if (MAX_ARGS == ac)
		ph->nbr2eat = __get_arg__(av[5]);
	if (INVALID == ph->philo_nbr
		|| INVALID == ph->time2die
		|| INVALID == ph->time2eat
		|| INVALID == ph->time2sleep
		|| INVALID == ph->nbr2eat)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_the_meal(int ac, char **av, t_philosophers *ph)
{
	int	i;

	memset(ph, 0, sizeof(t_philosophers));
	if (FAILURE == __check_args__(ac, av, ph))
	{
		printf("Arguments Error\n");
		print_usage();
		return (FAILURE);
	}
	ph->philos = (t_philo *)malloc(ph->philo_nbr * sizeof(t_philo));
	if (!ph->philos)
	{
		printf("%s%d: Malloc Error\n", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < ph->philo_nbr)
	{
		memset(&ph->philos[i], 0, sizeof(t_philo));
		ph->philos[i].id = i;
		ph->philos[i].left = 1;
		ph->philos[i].right = 1;
		++i;
	}
	return (SUCCESS);
}
