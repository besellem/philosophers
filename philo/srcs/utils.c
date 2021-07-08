/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:56:53 by besellem          #+#    #+#             */
/*   Updated: 2021/07/08 18:13:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define _MS_CONST_ 500

void	__usleep__(int philo_id, int ms)
{
	const uint64_t	now = __current_time_ms__();

	while (is_alive(philo_id) && (__current_time_ms__() - now) < (uint64_t)ms)
		usleep(_MS_CONST_);
}

uint64_t	__current_time_ms__(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000) + (t.tv_usec / 1000));
}

void	*ft_memdel(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	min;

	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		++str;
	min = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			min = -1;
	nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		nb = nb * 10 + *str++ - 48;
	return (nb * min);
}

void	print_usage(void)
{
	printf("usage: ./" PROG_NAME " number_of_philosophers\n");
	printf("               time_to_die\n");
	printf("               time_to_eat\n");
	printf("               time_to_sleep\n");
	printf("               [number_of_times_each_philosopher_must_eat]\n");
}
