/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:58:48 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 18:42:56 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

	start = get_time() ;
	while ((get_time() - start) < time)
	{
		safe_check_death(global_state);
		usleep(100);
	}
	return (0);
}

int	ft_usleep2(long time, t_philo *philo)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (philosopher_dead(philo) || safe_check_death(philo->global_state))
			return (1);
		else
			usleep(100);
	}
	return (0);
}
