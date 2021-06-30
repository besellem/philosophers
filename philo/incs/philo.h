/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:21:25 by besellem          #+#    #+#             */
/*   Updated: 2021/06/30 18:21:45 by besellem         ###   ########.fr       */
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

# define MIN_ARGS      5
# define MAX_ARGS      6

# define TRUE          1
# define FALSE         0

# define SUCCESS       0
# define FAILURE       1

# define INVALID       (-1)

# define UINT32_MAXLEN 11

/* struct s_philo `status' */
# define STAT_THINKING   0
# define STAT_TAKEN_FORK 1
# define STAT_EATING     2
# define STAT_SLEEPING   3
# define STAT_TAKEN_DIED 4

/* status messages */
# define MSG_THINKING    " is thinking\n"
# define MSG_TAKEN_FORK  " has taken a fork\n"
# define MSG_EATING      " is eating\n"
# define MSG_SLEEPING    " is sleeping\n"
# define MSG_DIED        " died\n"

/*
** -- DATA STRUCTURES --
*/
typedef struct s_philo
{
	unsigned int	left : 2;
	unsigned int	right : 2;
	int				id;
	unsigned int	status;
	pthread_t		philo;
}	t_philo;

typedef struct s_philosophers
{
	int			philo_nbr;
	int			time2die;
	int			time2eat;
	int			time2sleep;
	int			nbr2eat;
	uint64_t	start_time_ms;
	t_philo		*philos;
}	t_philosophers;

// 200 100
// 1 2 3 4

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
