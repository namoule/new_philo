/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:10:25 by jealefev          #+#    #+#             */
/*   Updated: 2025/01/23 14:47:39 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void free_global_state(t_global_state *global_state)
{
	free(global_state->printf_mutex);
	free(global_state->death_flag_mutex);
	free(global_state->meal_check_mutex);
	free(global_state->start_time_mutex);
	free(global_state->philos);
	free(global_state->forks);
}

int	init(int argc, char **argv, t_global_state *global_state)
{
	if (init_global_state(argc, argv, global_state) == 1)
		return (1);
	if (init_forks(global_state) == 1)
		return (1);
	if (init_philos(global_state) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_global_state	global_state;

	if (argc != 5 && argc != 6)
		return (0);
	init(argc, argv, &global_state);
	thread(&global_state);
	free_global_state(&global_state);
	return (0);
}
