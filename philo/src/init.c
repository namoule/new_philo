/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:56:10 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 15:38:12 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_global_state *global_state)
{
	int	i;

	i = 0;
	while (i < global_state->philo_nbr)
	{
		pthread_mutex_init(&global_state->forks[i], NULL);
		if (!(&global_state->forks[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	give_forks(int i, t_global_state *global_state)
{
	if (i == 0)
	{
		global_state->philos[0].l_fork = &global_state->forks[0];
		global_state->philos[0].r_fork
			= &global_state->forks[global_state->philo_nbr - 1];
	}
	else
	{
		global_state->philos[i].l_fork = &global_state->forks[i];
		global_state->philos[i].r_fork = &global_state->forks[i - 1];
	}
	return (0);
}

int	init_philos(t_global_state *global_state)
{
	int	i;

	i = 0;
	while (i < global_state->philo_nbr)
	{
		global_state->philos[i].eat_count = 0;
		global_state->philos[i].id = i+1;
		global_state->philos[i].last_meal = 0;
		global_state->philos[i].time_to_think = time_to_think(i, global_state);
		global_state->philos[i].meal_lock = global_state->meal_check_mutex;
		global_state->philos[i].dead_lock = global_state->death_flag_mutex;
		global_state->philos[i].printf_mutex = global_state->printf_mutex;
		global_state->philos[i].global_state = global_state;
		give_forks(i, global_state);
		i++;
	}
	return (0);
}

int	clean_init(t_global_state *global_state)
{
	if (init_tabs(global_state) == 1)
		return (1);
	if (alloc_mutex(global_state) == 1)
		return (1);
	if (alloc_mutex_2(global_state) == 1)
		return (1);
	if (mutex_init(global_state) == 1)
		return (1);
	if (mutex_init_2(global_state) == 1)
		return (1);
	return (0);
}

int	init_global_state(int argc, char **argv, t_global_state *global_state)
{
	global_state->philo_nbr = ft_atoi(argv[1]);
	global_state->time_to_die = ft_atol(argv[2]);
	global_state->time_to_eat = ft_atol(argv[3]);
	global_state->time_to_sleep = ft_atol(argv[4]);
	if (global_state->time_to_die < 1 || global_state->philo_nbr < 1
		|| global_state->time_to_eat < 1 || global_state->time_to_sleep < 1)
		return (printf("don't send any negative number\n"), 1);
	if (argc == 6)
	{
		global_state->meals_nbr = ft_atoi(argv[5]);
		if (global_state->meals_nbr < 1)
			return (printf("don't send any negative number\n"), 1);
	}
	else
		global_state->meals_nbr = -1;
	global_state->start_time = 0;
	global_state->dead = false;
	clean_init(global_state);
	return (0);
}
