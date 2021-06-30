/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:56:53 by besellem          #+#    #+#             */
/*   Updated: 2021/06/30 15:43:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
