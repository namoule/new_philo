/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:30:04 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 15:40:44 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->global_state->meal_check_mutex);
	if (get_time() - philo->last_meal >= philo->global_state->time_to_die)
	{
		pthread_mutex_unlock(philo->global_state->meal_check_mutex);
		safe_printf("died", philo);
		pthread_mutex_lock(philo->global_state->death_flag_mutex);
		philo->global_state->dead = true;
		pthread_mutex_unlock(philo->global_state->death_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->global_state->meal_check_mutex);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->global_state->start_time_mutex);
	if (philo->global_state->start_time == 0)
	{
		philo->global_state->start_time = get_time();
	}
	philo->last_meal = philo->global_state->start_time;
	pthread_mutex_unlock(philo->global_state->start_time_mutex);
	while (philosopher_dead(philo) == 0
		&& safe_check_death(philo->global_state) == false)
	{
		if (_eat(philo) == 1)
		{
			break ;
		}
		if (_sleep(philo) == 1)
			break ;
		if (_think(philo) == 1)
			break ;
	}
	return (0);
}

int	thread(t_global_state *global_state)
{
	int			i;
	pthread_t	superv;

	i = -1;
	if (pthread_create(&superv, NULL, &supervisor, global_state) != 0)
		destory_all("Thread creation error", global_state);
	while (++i < global_state->philo_nbr)
	{
		if (pthread_create(&global_state->philos[i].thread_philo, NULL,
				&routine, &global_state->philos[i]) != 0)
			return (0);
		ft_usleep(1, global_state);
	}
	i = -1;
	if (pthread_join(superv, NULL) != 0)
		destory_all("Thread join error", global_state);
	while (++i < global_state->philo_nbr)
	{
		if (pthread_join(global_state->philos[i].thread_philo, NULL) != 0)
			destory_all("Thread join error", global_state);
	}
	return (0);
}
