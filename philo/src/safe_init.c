/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:32:15 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 11:53:41 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_tabs(t_global_state *global_state)
{
	global_state->philos = malloc(sizeof(t_philo) * (global_state->philo_nbr
				+ 1));
	if (global_state->philos == NULL)
	{
		perror("malloc failed for global_state->philos");
		return (1);
	}
	global_state->forks = malloc(sizeof(pthread_mutex_t)
			* (global_state->philo_nbr + 1));
	if (global_state->forks == NULL)
	{
		perror("malloc failed for global_state->forks");
		free(global_state->philos);
		return (1);
	}
	return (0);
}

int	alloc_mutex(t_global_state *global_state)
{
	global_state->printf_mutex = malloc(sizeof(pthread_mutex_t));
	if (global_state->printf_mutex == NULL)
	{
		perror("malloc failed for global_state->printf_mutex");
		free(global_state->forks);
		free(global_state->philos);
	}
	global_state->death_flag_mutex = malloc(sizeof(pthread_mutex_t));
	if (global_state->death_flag_mutex == NULL)
	{
		perror("malloc failed for global_state->death_flag_mutex");
		free(global_state->printf_mutex);
		free(global_state->forks);
		free(global_state->philos);
	}
	return (0);
}

int	alloc_mutex_2(t_global_state *global_state)
{
	global_state->meal_check_mutex = malloc(sizeof(pthread_mutex_t));
	if (global_state->meal_check_mutex == NULL)
	{
		perror("malloc failed for global_state->meal_check_mutex");
		free(global_state->death_flag_mutex);
		free(global_state->printf_mutex);
		free(global_state->forks);
		return (free(global_state->philos), 1);
	}
	global_state->start_time_mutex = malloc(sizeof(pthread_mutex_t));
	if (global_state->start_time_mutex == NULL)
	{
		perror("malloc failed for global_state->start_time_mutex");
		free(global_state->meal_check_mutex);
		free(global_state->death_flag_mutex);
		free(global_state->printf_mutex);
		free(global_state->forks);
		return (free(global_state->philos), 1);
	}
	return (0);
}

int	mutex_init(t_global_state *global_state)
{
	if (pthread_mutex_init(global_state->printf_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init failed for global_state->printf_mutex");
		free(global_state->start_time_mutex);
		free(global_state->meal_check_mutex);
		free(global_state->death_flag_mutex);
		free(global_state->printf_mutex);
		free(global_state->forks);
		return (free(global_state->philos), 1);
	}
	if (pthread_mutex_init(global_state->death_flag_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init failed for global_state->death_flag_mutex");
		pthread_mutex_destroy(global_state->printf_mutex);
		free(global_state->start_time_mutex);
		free(global_state->meal_check_mutex);
		free(global_state->death_flag_mutex);
		free(global_state->printf_mutex);
		free(global_state->forks);
		return (free(global_state->philos), 1);
	}
	return (0);
}

int	mutex_init_2(t_global_state *global_state)
{
	if (pthread_mutex_init(global_state->meal_check_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init failed for global_state->meal_check_mutex");
		pthread_mutex_destroy(global_state->printf_mutex);
		pthread_mutex_destroy(global_state->death_flag_mutex);
		free(global_state->start_time_mutex);
		free(global_state->meal_check_mutex);
		free(global_state->death_flag_mutex);
		free(global_state->printf_mutex);
		free(global_state->forks);
		return (free(global_state->philos), 1);
	}
	if (pthread_mutex_init(global_state->start_time_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init failed for global_state->start_time_mutex");
		pthread_mutex_destroy(global_state->printf_mutex);
		pthread_mutex_destroy(global_state->death_flag_mutex);
		pthread_mutex_destroy(global_state->meal_check_mutex);
		free(global_state->start_time_mutex);
		free(global_state->meal_check_mutex);
		free(global_state->death_flag_mutex);
		free(global_state->printf_mutex);
		return (free(global_state->forks), free(global_state->philos), 1);
	}
	return (0);
}
