/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_stop_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:23:04 by caboudar          #+#    #+#             */
/*   Updated: 2023/01/04 23:35:57 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool		max_meal_option(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->max_meal_option_mutex);
	if (philo->data->max_meal_option == true)
	{
		pthread_mutex_unlock(&philo->data->max_meal_option_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->max_meal_option_mutex);
	return (false);
}





bool	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	if (philo->data->philo_has_died == true)
	{
		pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	return (false);
}

bool	all_philo_full(t_philo *philo)
{
	if (!max_meal_option(philo))
		return (false);
	if (philo->data->every_philo_full == true)
	{
		pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	return (false);
}

bool	kill_philo_if_possible(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	if (get_current_time() > philo->last_meal_time + philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		pthread_mutex_lock(&philo->data->philo_has_died_mutex);
		philo->data->philo_has_died = true;
		pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
		mutex_print(philo, DIE_ID, "died\n");		
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	return (false);
}

bool	try_to_set_all_philo_to_full(t_philo *philo, t_data *data)
{
	int		i;

	if (!max_meal_option(philo))
		return (false);
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_lock(&philo->total_meals_eaten_mutex);
		if (philo->total_meals_eaten < philo->data->max_nb_of_meals)
		{
			pthread_mutex_unlock(&philo->total_meals_eaten_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philo->total_meals_eaten_mutex);
		i++;
		philo = philo->next;
	}
	pthread_mutex_lock(&philo->data->every_philo_full_mutex);
	data->every_philo_full = true;
	pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	return (true);
}
