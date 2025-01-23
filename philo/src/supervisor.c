/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:53:19 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 15:39:28 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	safe_check_death(t_global_state *global_state)
{
	pthread_mutex_lock(global_state->death_flag_mutex);
	if (global_state->dead == true)
	{
		pthread_mutex_unlock(global_state->death_flag_mutex);
		return (true);
	}
	pthread_mutex_unlock(global_state->death_flag_mutex);
	return (false);
}

bool	check_full(t_global_state *global_state)
{
	int	i;

	i = 0;
	while (i < global_state->philo_nbr)
	{
		pthread_mutex_lock(global_state->meal_check_mutex);
		if (global_state->philos[i].eat_count != global_state->meals_nbr)
		{
			pthread_mutex_unlock(global_state->meal_check_mutex);
			return (false);
		}
		pthread_mutex_unlock(global_state->meal_check_mutex);
		i++;
	}
	return (true);
}

void	*supervisor(void *data)
{
	t_global_state	*global_state;

	global_state = (t_global_state *)data;
	while (1)
	{
		if (safe_check_death(global_state) == true)
		{
			break ;
		}
		if (global_state->meals_nbr > -1 && check_full(global_state) == true)
		{
			pthread_mutex_lock(global_state->death_flag_mutex);
			global_state->dead = true;
			pthread_mutex_unlock(global_state->death_flag_mutex);
			break ;
		}
		if (ft_usleep(100, global_state) == 1)
		{
			break ;
		}
	}
	return (NULL);
}
