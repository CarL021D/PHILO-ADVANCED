/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:19:40 by caboudar          #+#    #+#             */
/*   Updated: 2023/01/09 20:08:35 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_data		data;

	if (exit_if_args_errors(ac, av) == ERROR)
		return (1);
	if (init_data(&philo, &data, ac, av) == ERROR)
		return (1);
	launch_philo_routine(&philo, &data);
	stop_routine_if_philo_dead_or_full(&philo, &data);
	if (destroy_threads(&philo, &data) == ERROR)
		return (1);
	destroy_mutex(&philo, &data);
	free_linked_list(&philo, &data);
}
