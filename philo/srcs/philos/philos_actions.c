/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:36:48 by fluchten          #+#    #+#             */
/*   Updated: 2023/03/09 17:07:05 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, 1);
	if (philo->data->nb_philos == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, 1);
}

static void	eat(t_philo *philo)
{
	print_msg(philo, 2);
	pthread_mutex_lock(&philo->data->lock);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->lock);
	ft_usleep(philo->data->time_to_eat);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->lock);
	print_msg(philo, 3);
	ft_usleep(philo->data->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_msg(philo, 4);
}

void	actions_loop(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data->lock);
	is_dead = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->lock);
	while (!is_dead)
	{
		take_forks(philo);
		if (philo->data->nb_philos == 1)
			break ;
		eat(philo);
		drop_forks(philo);
		think(philo);
		pthread_mutex_lock(&philo->data->lock);
		is_dead = philo->data->is_dead;
		pthread_mutex_unlock(&philo->data->lock);
	}
}
