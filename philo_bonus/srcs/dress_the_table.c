/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dress_the_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:42:34 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 14:35:39 by besellem         ###   ########.fr       */
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
	size_t	i;

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

static int	init_semaphores(t_philosophers *ph)
{
	int	check;

	check = SUCCESS;
	sem_unlink(_SEM_END_);
	sem_unlink(_SEM_FORKS_);
	sem_unlink(_SEM_MONITOR_);
	ph->sem_end = sem_open(_SEM_END_, O_CREAT, __SEM_MODE__, 1);
	if (SEM_FAILED == ph->sem_end)
		check = FAILURE;
	ph->forks = sem_open(_SEM_FORKS_, O_CREAT, __SEM_MODE__, ph->philo_nbr);
	if (SEM_FAILED == ph->forks)
		check = FAILURE;
	ph->sem_monitor = sem_open(_SEM_MONITOR_, O_CREAT, __SEM_MODE__, 1);
	if (SEM_FAILED == ph->sem_monitor)
		check = FAILURE;
	if (FAILURE == check)
		printf("%s%d: sem_open() error\n", __FILE__, __LINE__);
	return (check);
}

static int	init_processes(t_philosophers *ph)
{
	size_t	i;

	i = 0;
	while (i < ph->philo_nbr)
	{
		ph->philos[i].pid = fork();
		if (ph->philos[i].pid < 0)
			return (FAILURE);
		else if (0 == ph->philos[i].pid)
		{
			a_philo_life(i);
		}
		else
		{
			waitpid(ph->philos[i].pid, NULL, 0);
		}
		++i;
	}
}

int	dress_the_table(int ac, char **av, t_philosophers *ph)
{
	if (NULL == singleton())
		return (FAILURE);
	if (FAILURE == check_args(ac, av, ph))
		return (FAILURE);
	if (FAILURE == init_philos(ph))
		return (FAILURE);
	if (FAILURE == init_semaphores(ph))
		return (FAILURE);
	if (FAILURE == init_processes(ph))
		return (FAILURE);
	ph->died = FALSE;
	return (SUCCESS);
}
