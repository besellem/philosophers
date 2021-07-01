/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:38:24 by besellem          #+#    #+#             */
/*   Updated: 2021/07/01 18:25:41 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*g_status[] = {
	[STAT_THINKING] = "is thinking",
	[STAT_TAKEN_FORK] = "has taken a fork",
	[STAT_EATING] = "is eating",
	[STAT_SLEEPING] = "is sleeping",
	[STAT_DIED] = "died"
};

uint64_t	__current_time_ms__(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000) + (t.tv_usec / 1000));
}

void	ft_putnbr_fd(long long n, int fd)
{
	long long	nb;
	long long	tmp;

	nb = (long long)n;
	if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
	}
	if (nb / 10 > 0)
		ft_putnbr_fd(nb / 10, fd);
	tmp = nb % 10 + 48;
	write(fd, &tmp, 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	print_status(int philo_id, int status)
{
	const uint64_t	__ms = __current_time_ms__() - singleton()->start_time_ms;

	// write(STDOUT_FILENO, "[", 1);
	// ft_putnbr_fd(__ms, STDOUT_FILENO);
	// write(STDOUT_FILENO, "] ", 2);
	// ft_putnbr_fd(philo_id, STDOUT_FILENO);
	// write(STDOUT_FILENO, " ", 1);
	// write(STDOUT_FILENO, g_status[status], ft_strlen(g_status[status]));
	// write(STDOUT_FILENO, "\n", 1);

	printf("[%11llu] %3d %s\n", __ms, philo_id, g_status[status]);
}
