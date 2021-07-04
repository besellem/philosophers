/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_the_meal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:42:34 by besellem          #+#    #+#             */
/*   Updated: 2021/07/04 16:20:53 by besellem         ###   ########.fr       */
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
	ph->time2die = __get_arg__(av[2]) * 1000;
	ph->time2eat = __get_arg__(av[3]) * 1000;
	ph->time2sleep = __get_arg__(av[4]) * 1000;
	return (SUCCESS);
}

int	ft_do_malloc(void **ptr, size_t count, size_t size)
{
	*ptr = malloc(count * size);
	if (!*ptr)
	{
		printf("%s%d: Malloc Error\n", __FILE__, __LINE__);
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
	if (FAILURE == ft_do_malloc((void **)&ph->philos, ph->philo_nbr, sizeof(t_philo)))
		return (FAILURE);
	if (FAILURE == ft_do_malloc((void **)&ph->forks, ph->philo_nbr, sizeof(pthread_mutex_t)))
		return (FAILURE);
	i = 0;
	while (i < ph->philo_nbr)
	{
		memset(&ph->philos[i], 0, sizeof(t_philo));
		ph->philos[i].id = i + 1;
		++i;
	}
	i = 0;
	while (i < ph->philo_nbr)
		pthread_mutex_init(&ph->forks[i++], NULL);
	pthread_mutex_init(&ph->__monitor, NULL);
	return (SUCCESS);
}
