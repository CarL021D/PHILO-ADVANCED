/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:20 by caboudar          #+#    #+#             */
/*   Updated: 2023/01/09 19:58:22 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	destroy_mutex(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	pthread_mutex_destroy(&data->philo_has_died_mutex);
	pthread_mutex_destroy(&data->every_philo_full_mutex);
	pthread_mutex_destroy(&data->max_meal_option_mutex);
	pthread_mutex_destroy(&data->lock_print);
	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&philo->left_fork);
		pthread_mutex_destroy(&philo->total_meals_eaten_mutex);
		pthread_mutex_destroy(&philo->last_meal_time_mutex);
		philo = philo->next;
		i++;
	}
}

void	init_mutex(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	pthread_mutex_init(&data->philo_has_died_mutex, NULL);
	pthread_mutex_init(&data->every_philo_full_mutex, NULL);
	pthread_mutex_init(&data->max_meal_option_mutex, NULL);
	pthread_mutex_init(&data->lock_print, NULL);
	philo = *philo_lst;
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_init(&philo->left_fork, NULL);
		pthread_mutex_init(&philo->total_meals_eaten_mutex, NULL);
		pthread_mutex_init(&philo->last_meal_time_mutex, NULL);
		philo = philo->next;
		i++;
	}
}

void	init_struct(t_data *data, int ac, char **av)
{
	data->nb_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->philo_has_died = false;
	data->max_meal_option = false;
	data->launch_time = get_current_time();
	if (ac == 6)
	{
		data->max_nb_of_meals = ft_atoi(av[5]);
		data->max_meal_option = true;
		data->every_philo_full = false;
	}
}

static void	init_philo_struct(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	philo = (*philo_lst);
	i = 0;
	while (i < data->nb_of_philos)
	{
		philo->index = (i + 1);
		philo->last_meal_time = get_current_time();
		philo->total_meals_eaten = 0;
		philo->data = data;
		if (data->max_meal_option == true)
			philo->philo_is_full = false;
		if (data->nb_of_philos > 1 && ((i + 1) == data->nb_of_philos))
			philo->next = *philo_lst;
		else
			philo = philo->next;
		i++;
	}
}

int	init_data(t_philo **philo_lst, t_data *data, int ac, char **av)
{
	init_struct(data, ac, av);
	if (create_linked_list(data, philo_lst) == ERROR)
	{
		free_list(philo_lst);
		return (ERROR);
	}
	init_philo_struct(philo_lst, data);
	init_mutex(philo_lst, data);
	return (true);
}
