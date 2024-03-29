/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:52:50 by fluchten          #+#    #+#             */
/*   Updated: 2023/03/07 19:32:20 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->fork)
		return (print_error("malloc() fork failed."));
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (print_error("pthread_mutex_init() fork failed"));
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL))
		return (print_error("pthread_mutex_init() write failed"));
	if (pthread_mutex_init(&data->lock, NULL))
		return (print_error("pthread_mutex_init() lock failed"));
	return (1);
}
