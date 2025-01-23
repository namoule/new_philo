/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_dishes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:40:38 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 11:59:32 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destory_all(char *str, t_global_state *global_state)
{
	int	i;

	if (str)
		(write(2, str, ft_strlen(str)), write(2, "\n", 1));
	pthread_mutex_destroy(global_state->printf_mutex);
	pthread_mutex_destroy(global_state->meal_check_mutex);
	pthread_mutex_destroy(global_state->death_flag_mutex);
	i = -1;
	while (++i < global_state->philo_nbr)
		pthread_mutex_destroy(&global_state->forks[i]);
	free(global_state->philos);
	free(global_state->forks);
}
