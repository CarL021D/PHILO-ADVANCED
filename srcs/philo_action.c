/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:30 by caboudar          #+#    #+#             */
/*   Updated: 2022/12/31 05:29:05 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// void	mutex_print(t_philo *philo, char *message)
void	mutex_print(t_philo *philo, int id, char *message)
{
	long	current_time;
	
	// (void)id;

	// pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	// if (philo->data->philo_has_died)
	// {
	// 	pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
	// pthread_mutex_lock(&philo->data->lock_print);
	// current_time = get_current_time() - philo->data->launch_time;
	// printf("%ld - %d %s\n", current_time, philo->index, message);
	// pthread_mutex_unlock(&philo->data->lock_print);



	pthread_mutex_lock(&philo->data->lock_print);
	current_time = get_current_time() - philo->data->launch_time;
	if (id == DIE_ID)
		printf("%ld - %d %s\n", current_time, philo->index, message);
	else if (!philo_died(philo) || !all_philo_full(philo))		
		printf("%ld - %d %s\n", current_time, philo->index, message);
	pthread_mutex_unlock(&philo->data->lock_print);



	// pthread_mutex_lock(&philo->data->lock_print);
	// current_time = get_current_time() - philo->data->launch_time;
	// printf("%ld - %d %s\n", current_time, philo->index, message);
	// pthread_mutex_unlock(&philo->data->lock_print);
}

bool	philo_is_eating(t_philo *philo)
{
	// int     time;
	// printf("\n\n%d  ERROR\n\n\n", philo->index);
	
	if (philo_died(philo))
		return (true);
		
	// if (!philo_died(philo))
	// {
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->next->left_fork);
	mutex_print(philo, ACTION_ID,"has taken a fork\n");
	mutex_print(philo, ACTION_ID, "has taken a fork\n");
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	philo->last_meal_time = get_current_time() /* - philo->data->launch_time*/;
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	mutex_print(philo, ACTION_ID, "is eating\n");
	pthread_mutex_lock(&philo->total_meals_eaten_mutex);
	philo->total_meals_eaten++;
	pthread_mutex_unlock(&philo->total_meals_eaten_mutex);
	// usleep(philo->data->time_to_eat);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->next->left_fork);
	pthread_mutex_unlock(&philo->left_fork);
	// }
	return (false);



	// time = philo->data->time_to_eat;
	// pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	// if (!philo->data->philo_has_died)
	// {
	// 	pthread_mutex_lock(&philo->data->every_philo_full_mutex);
	// 	if (philo->philo_is_full == true)
	// 	{
	// 		pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	// 		return ;		
	// 	}
	// 	pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	// 	pthread_mutex_lock(&philo->left_fork);
	// 	pthread_mutex_lock(&philo->next->left_fork);
		
	// 	mutex_print(philo, ACTION_ID,"has taken a fork\n");
	// 	mutex_print(philo, ACTION_ID, "has taken a fork\n");
	// 	mutex_print(philo, ACTION_ID, "is eating\n");

	// 	// mutex_print(philo, "has taken a fork\n");
	// 	// mutex_print(philo, "has taken a fork\n");
	// 	// mutex_print(philo, "is eating\n");

		
	// 	philo->last_meal_time = get_current_time();
	// 	usleep(time * 1000);
	// 	pthread_mutex_unlock(&philo->next->left_fork);
	// 	pthread_mutex_unlock(&philo->left_fork);
	// }
	// pthread_mutex_lock(&philo->data->every_philo_full_mutex);
	// if (philo->data->max_meal_option == true)
	// {
	// 	philo->total_meals_eaten++;
	// 	if (philo->total_meals_eaten == philo->data->max_nb_of_meals)
	// 		philo->philo_is_full = true;
	// }
	// pthread_mutex_unlock(&philo->data->every_philo_full_mutex);
	// pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
}

bool    philo_is_sleeping(t_philo *philo)
{
	if (philo_died(philo))
		return (true);
	// if (!philo_died(philo))
	// {
	mutex_print(philo, ACTION_ID, "is sleeping\n");
	ft_usleep(philo, philo->data->time_to_sleep);
	// }
	return (false);



	// int     time;
	// int		option;

	// time = philo->data->time_to_sleep;
	// option = philo->data->max_meal_option;
	// pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	// if (!philo->data->philo_has_died || (option && !philo->philo_is_full))
	// {
	// 	mutex_print(philo, ACTION_ID, "is sleeping\n");
	// 	// mutex_print(philo, "is sleeping\n");
		
	// 	// usleep(time * 1000);
	// 	ft_usleep(philo->data->time_to_sleep);
	// }
	// pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
}

bool	philo_is_thinking(t_philo *philo)
{
	// int		option;
	// pthread_mutex_lock(&philo->data->philo_has_died_mutex);
	// if (!philo->data->philo_has_died || (option && !philo->philo_is_full))
	if (philo_died(philo))
		return (true);
	// if (!philo_died(philo))	
	// {
		mutex_print(philo, ACTION_ID, "is thinking\n");
	// }
		return (false);
		// mutex_print(philo, "is thinking\n");
	// pthread_mutex_unlock(&philo->data->philo_has_died_mutex);
}

// printf("\n\nERROR\n\n\n");