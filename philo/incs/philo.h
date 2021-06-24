/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:21:25 by besellem          #+#    #+#             */
/*   Updated: 2021/06/25 01:07:46 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** -- INCLUDES --
*/
# include <string.h>   /* memset */
# include <stdio.h>    /* printf */
# include <stdlib.h>   /* malloc, free */
# include <unistd.h>   /* write, usleep */
# include <sys/time.h> /* gettimeofday */

/*
** pthread_create
** pthread_detach
** pthread_join
** pthread_mutex_init
** pthread_mutex_destroy
** pthread_mutex_lock
** pthread_mutex_unlock
*/
# include <pthread.h>

/*
** -- DEFINES --
*/
# define PROG_NAME "philo"
# define MIN_ARGS 5
# define MAX_ARGS 6

# define TRUE  1
# define FALSE 0

/*
** -- DATA STRUCTURES --
*/
typedef struct s_philosophers
{
	unsigned int	philo_nbr;
	unsigned int	time2die;
	unsigned int	time2eat;
	unsigned int	time2sleep;
	unsigned int	nbr2eat;
	pthread_t		*philos;
}	t_philosophers;

/*
** -- PROTOTYPES --
*/
/* Utils */
void	*ft_memdel(void **ptr);
int		ft_atoi(const char *str);

/* Memory Management */
int		ft_free_all(t_philosophers *ph, int code);

#endif
