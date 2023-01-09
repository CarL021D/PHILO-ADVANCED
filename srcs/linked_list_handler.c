/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:53:41 by caboudar          #+#    #+#             */
/*   Updated: 2023/01/09 20:09:18 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*create_node(void)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

int	create_linked_list(t_data *data, t_philo **philo_lst)
{
	t_philo		*philo;
	int			i;

	i = 1;
	philo = create_node();
	if (!philo)
		return (ERROR);
	*philo_lst = philo;
	while (i < data->nb_of_philos)
	{
		philo = *philo_lst;
		while (philo->next)
			philo = philo->next;
		philo->next = create_node();
		if (!philo)
			return (ERROR);
		i++;
	}
	return (1);
}

void	free_linked_list(t_philo **philo_lst, t_data *data)
{
	t_philo		*philo;
	int			i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		philo = (*philo_lst)->next;
		free(*philo_lst);
		*philo_lst = philo;
		i++;
	}
}

void	free_list(t_philo **philo)
{
	t_philo	*node;

	while (*philo)
	{
		node = (*philo)->next;
		free(*philo);
		*philo = node;
	}
}
