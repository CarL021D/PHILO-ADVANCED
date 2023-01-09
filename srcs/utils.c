/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:55 by caboudar          #+#    #+#             */
/*   Updated: 2023/01/09 20:08:19 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(t_philo *philo, long time)
{
	long	current_time;

	current_time = get_current_time();
	while (((get_current_time() - current_time) * 1000) < (time * 1000))
	{
		if (philo_died(philo))
			return ;
		usleep(100);
	}
}

void	desync_action_for_even_philo_count(t_philo *philo)
{
	if (philo->index % 2)
		ft_usleep(philo, philo->data->time_to_eat);
}

void	desync_action_for_odd_philo_count(t_philo *philo)
{
	int		time;

	time = philo->data->time_to_eat;
	if (philo->index == philo->data->nb_of_philos)
		time *= 2;
	if (philo->index % 2 == 0 && philo->data->nb_of_philos != 1)
		ft_usleep(philo, time);
}

int	ft_atoi(const char *nptr)
{
	long long	res;
	int			sign;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	return (sign * res);
}
