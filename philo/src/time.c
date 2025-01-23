/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:58:48 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 15:37:58 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	time_to_think(int i, t_global_state *global_state)
{
	int	ret;

	ret = 0;
	if (i % 2)
		ret = (global_state->time_to_eat * 2) - global_state->time_to_sleep;
	else
		ret = global_state->time_to_eat - global_state->time_to_sleep;
	if (ret <= 0)
	{
		ret = 0;
	}
	return (ret);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() error\n", NULL));
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(long time, t_global_state *global_state)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		safe_check_death(global_state);
		usleep(50);
	}
	return (0);
}

int	ft_usleep2(long time, t_philo *philo)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (philosopher_dead(philo))
			usleep(50);
	}
	return (0);
}
