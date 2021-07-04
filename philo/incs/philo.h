/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:21:25 by besellem          #+#    #+#             */
/*   Updated: 2021/07/04 16:25:50 by besellem         ###   ########.fr       */
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

# define MIN_ARGS          5
# define MAX_ARGS          6

# define TRUE              1
# define FALSE             0

# define SUCCESS           0
# define FAILURE           1

# define INVALID           (-1)

# define UINT32_MAXLEN     11

/* struct s_philo `status' */
# define STAT_THINKING      1
# define STAT_TAKEN_FORK    2
# define STAT_EATING        3
# define STAT_SLEEPING      4
# define STAT_DIED          5

# define FORK_AVAILABLE     (-1)

/*
** -- DATA STRUCTURES --
*/
typedef struct s_philo
{
	int				id;
	int				nbr_eaten;	// OPTION  5
	uint64_t		time2die;
	pthread_t		philo;
}	t_philo;

typedef struct s_philosophers
{
	int				philo_nbr;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				nbr2eat;
	int				died;
	uint64_t		start_time_ms;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	__monitor;
}	t_philosophers;

/*
** -- PROTOTYPES --
*/
/* Utils */
void			*ft_memdel(void **ptr);
int				ft_atoi(const char *str);

/* Memory Management */
t_philosophers	*singleton(void);
int				ft_free_all(int code);

/* status */
uint64_t		__current_time_ms__(void);
void			print_status(int philo_id, int status);

/* General */
void			print_usage(void);
int				init_the_meal(int ac, char **av, t_philosophers *ph);

#endif
