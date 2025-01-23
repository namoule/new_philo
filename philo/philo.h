/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:09:52 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 12:02:10 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define RDM "\033[0;32m"
# define NTR "\033[0;0m"

typedef struct s_global_state	t_global_state;

typedef struct s_philo
{
	int							id;
	int							eat_count;
	int							time_to_think;
	long						last_meal;
	pthread_t					thread_philo;
	pthread_mutex_t				*r_fork;
	pthread_mutex_t				*l_fork;
	pthread_mutex_t				*printf_mutex;
	pthread_mutex_t				*dead_lock;
	pthread_mutex_t				*meal_lock;
	t_global_state				*global_state;
}								t_philo;

struct							s_global_state
{
	int							philo_nbr;
	long						time_to_die;
	long						time_to_eat;
	long						time_to_sleep;
	long						meals_nbr;
	long						start_time;
	bool						dead;
	t_philo						*philos;
	pthread_mutex_t				*forks;
	pthread_mutex_t				*death_flag_mutex;
	pthread_mutex_t				*printf_mutex;
	pthread_mutex_t				*meal_check_mutex;
	pthread_mutex_t				*start_time_mutex;
};

int								init(int argc, char **argv,
									t_global_state *global_state);
int								clean_init(t_global_state *global_state);

int								init_global_state(int argc, char **argv,
									t_global_state *global_stat);
int								init_philos(t_global_state *global_stat);
int								init_forks(t_global_state *global_stat);

int								init_tabs(t_global_state *global_state);

int								alloc_mutex(t_global_state *global_state);
int								alloc_mutex_2(t_global_state *global_state);

int								mutex_init(t_global_state *global_state);
int								mutex_init_2(t_global_state *global_state);

int								thread(t_global_state *global_state);
void							*routine(void *data);
void							*supervisor(void *data);

int								_eat(t_philo *philo);
int								_sleep(t_philo *philo);
int								_think(t_philo *philo);

void							drop_forks(t_philo *philo);

void							safe_printf(char *str, t_philo *philo);
bool							safe_check_death(t_global_state *global_state);
int								philosopher_dead(t_philo *philo);

int								ft_usleep2(long time, t_philo *philo);
int								ft_usleep(long time,
									t_global_state *global_state);
long							get_time(void);
int								time_to_think(int i,
									t_global_state *global_state);

void							destory_all(char *str,
									t_global_state *globalt_global_state);

size_t							ft_strlen(const char *str);
long							ft_atoi(const char *str);
long							ft_atol(const char *str);

# ifndef DEBUG
#  define DEBUG 0
# endif
#endif
