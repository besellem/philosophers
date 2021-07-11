/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 00:21:25 by besellem          #+#    #+#             */
/*   Updated: 2021/07/11 15:52:47 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** -- INCLUDES --
*/
# include <stdint.h>
# include <string.h>   /* memset */
# include <stdio.h>    /* printf */
# include <stdlib.h>   /* malloc, free, exit */
# include <unistd.h>   /* write, fork, usleep */
# include <signal.h>   /* kill */
# include <sys/time.h> /* gettimeofday */
# include <sys/wait.h> /* waitpid */

/*
** pthread_create
** pthread_detach
** pthread_join
*/
# include <pthread.h>

/*
** sem_open
** sem_close
** sem_post
** sem_wait
** sem_unlink
*/
# include <semaphore.h>

/*
** -- DEFINES --
*/
# define PROG_NAME "philo_bonus"

# define MIN_ARGS          5
# define MAX_ARGS          6

# define TRUE              1
# define FALSE             0

# define SUCCESS           0
# define FAILURE           1

# define INVALID           (-1)

# define UINT32_MAXLEN     11

/* path names for sem_open() */
# define __SEM_MODE__      0660
# define _SEM_END_         "sem_end"
# define _SEM_FORKS_       "sem_forks"
# define _SEM_MONITOR_     "sem_monitor"

/* used in struct s_philo `status' */
# define STAT_THINKING     1
# define STAT_TAKEN_FORK   2
# define STAT_EATING       3
# define STAT_SLEEPING     4
# define STAT_DIED         5

/* color codes */
# define B_BLACK    "\e[1;30m"
# define B_RED      "\e[1;31m"
# define B_GREEN    "\e[1;32m"
# define B_YELLOW   "\e[1;33m"
# define B_BLUE     "\e[1;34m"
# define B_PURPLE   "\e[1;35m"
# define B_CYAN     "\e[1;36m"
# define B_GRAY     "\e[1;37m"

# define CLR_COLOR  "\e[0m"

/*
** -- DATA STRUCTURES --
*/
typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				nbr_eaten;
	uint64_t		time2die;
}	t_philo;

typedef struct s_philosophers
{
	int			philo_nbr;
	int			time2die;
	int			time2eat;
	int			time2sleep;
	int			nbr2eat;
	int			died;
	uint64_t	start_time_ms;
	t_philo		*philos;
	pthread_t	monitor;
	sem_t		*forks;
	sem_t		*sem_end;
	sem_t		*sem_monitor;
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
void			__usleep__(int philo_id, int ms);
void			print_status(int philo_id, int status);

/* General */
void			print_usage(void);
int				dress_the_table(int ac, char **av, t_philosophers *ph);
void			a_philo_life(int id);

/* Philo borring life steps */
void			step_eat(int philo_id);
void			step_drop_forks(void);
void			step_sleep(int philo_id);

/* Checks */
int				everyone_got_his_meals(void);
int				is_alive(int philo_id);

#endif
