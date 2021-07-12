/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dress_the_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:42:34 by besellem          #+#    #+#             */
/*   Updated: 2021/07/12 11:26:06 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	__get_arg__(char *arg)
{
	int		_atoi;
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9') || i > UINT32_MAXLEN)
			return (INVALID);
		++i;
	}
	_atoi = ft_atoi(arg);
	if (_atoi <= 0)
		return (INVALID);
	return (_atoi);
}

static int	check_args(int ac, char **av, t_philosophers *ph)
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
		printf("Arguments Error\n");
		print_usage();
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_philos(t_philosophers *ph)
{
	int	i;

	ph->philos = malloc(ph->philo_nbr * sizeof(t_philo));
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
		++i;
	}
	return (SUCCESS);
}

int	dress_the_table(int ac, char **av, t_philosophers *ph)
{
	if (NULL == singleton())
		return (FAILURE);
	if (FAILURE == check_args(ac, av, ph))
		return (FAILURE);
	if (FAILURE == init_philos(ph))
		return (FAILURE);
	__unlink_semaphores__();
	if (FAILURE == __open_semaphores__(ph))
		return (FAILURE);
	ph->died = FALSE;
	return (SUCCESS);
}
