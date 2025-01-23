/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:59:01 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 12:01:33 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (-2);
		i++;
	}
	return (0);
}

void	safe_printf(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->global_state->printf_mutex);
	pthread_mutex_lock(philo->global_state->start_time_mutex);
	time = get_time() - philo->global_state->start_time;
	pthread_mutex_unlock(philo->global_state->start_time_mutex);
	if (ft_strcmp(str, "is eating") == 0 && philosopher_dead(philo) == true)
	{
		str = "died";
		pthread_mutex_unlock(philo->global_state->printf_mutex);
		drop_forks(philo);
		pthread_mutex_lock(philo->global_state->printf_mutex);
	}
	pthread_mutex_lock(philo->global_state->death_flag_mutex);
	if (ft_strcmp("died", str) == 0 && philo->global_state->dead == 0)
	{
		printf("%ld %d %s\n", time, philo->id, str);
		philo->global_state->dead = 1;
	}
	if (!philo->global_state->dead)
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->global_state->death_flag_mutex);
	pthread_mutex_unlock(philo->global_state->printf_mutex);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
	{
		printf("don't send any negative nb...\n");
		exit(EXIT_FAILURE);
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (i > 10)
	{
		printf("too long!\n");
		exit(EXIT_FAILURE);
	}
	return (nb);
}

long	ft_atol(const char *str)
{
	int			i;
	int			neg;
	long long	result;

	neg = 0;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - '0';
	if (neg)
		result = -result;
	return (result);
}
