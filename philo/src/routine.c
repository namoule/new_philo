/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:58:06 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 19:25:53 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		safe_printf("has taken a fork", philo);
		if (philo->global_state->philo_nbr == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			ft_usleep2(philo->global_state->time_to_die, philo);
			return (1);
		}
		pthread_mutex_lock(philo->l_fork);
		safe_printf("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		safe_printf("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		safe_printf("has taken a fork", philo);
	}
	return (0);
}

int	_eat(t_philo *philo)
{
	if (take_forks(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	safe_printf("is eating", philo);
	if (ft_usleep2(philo->global_state->time_to_eat, philo))
	{
		return (drop_forks(philo), 1);
	}
	drop_forks(philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->eat_count++;
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	_sleep(t_philo *philo)
{
	safe_printf("is sleeping", philo);
	if (ft_usleep2(philo->global_state->time_to_sleep, philo) == 1)
	{
		return (1);
	}
	return (0);
}

int	_think(t_philo *philo)
{
	safe_printf("is thinking", philo);
	if (ft_usleep2(philo->time_to_think, philo) == 1)
	{
		return (1);
	}
	return (0);
}
