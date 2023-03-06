/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:36:48 by fluchten          #+#    #+#             */
/*   Updated: 2023/03/06 21:56:43 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, 1);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, 1);
}

static void	eat(t_philo *philo)
{
	print_msg(philo, 2);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->t_eat);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->lock);
	philo->meal_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	print_msg(philo, 3);
}

static void	think(t_philo *philo)
{
	ft_usleep(philo->data->t_sleep);
	print_msg(philo, 4);
}

void	actions_loop(t_philo *philo)
{
	while (philo->data->is_dead == 0)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		think(philo);
	}
}
