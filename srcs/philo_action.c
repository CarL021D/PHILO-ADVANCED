/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:30 by caboudar          #+#    #+#             */
/*   Updated: 2023/01/05 14:09:47 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	mutex_print(t_philo *philo, int id, char *message)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->lock_print);
	current_time = get_current_time() - philo->data->launch_time;
	if (id == DIE_ID)
		printf("%ld - %d %s\n", current_time, philo->index, message);
	else if (!philo_died(philo) || !all_philo_full(philo))
		printf("%ld - %d %s\n", current_time, philo->index, message);
	pthread_mutex_unlock(&philo->data->lock_print);
}

bool	philo_is_eating(t_philo *philo)
{
	if (philo_died(philo) || all_philo_full(philo))
		return (false);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->next->left_fork);
	mutex_print(philo, ACTION_ID, "has taken a fork\n");
	mutex_print(philo, ACTION_ID, "has taken a fork\n");
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	mutex_print(philo, ACTION_ID, "is eating\n");
	pthread_mutex_lock(&philo->total_meals_eaten_mutex);
	philo->total_meals_eaten++;
	pthread_mutex_unlock(&philo->total_meals_eaten_mutex);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->next->left_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (true);
}

bool	philo_is_sleeping(t_philo *philo)
{
	if (philo_died(philo) || all_philo_full(philo))
		return (false);
	mutex_print(philo, ACTION_ID, "is sleeping\n");
	ft_usleep(philo, philo->data->time_to_sleep);
	return (true);
}

bool	philo_is_thinking(t_philo *philo)
{
	if (philo_died(philo) || all_philo_full(philo))
		return (false);
	mutex_print(philo, ACTION_ID, "is thinking\n");
	return (true);
}
