/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 04:14:54 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 04:00:20 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../philo.h"

int	start_director(t_philosophy *philosophy)
{
	pthread_t	id;

	if (pthread_create(&id, NULL, check_death_director, philosophy) != 0)
	{
		printf("Failed to create thread\n");
		return (1);
	}
	if (pthread_join(id, NULL) != 0)
	{
		printf("Failed to join thread\n");
		return (1);
	}
	return (0);
}

int	start_threads(t_philosophy *philosophy, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philosophy->philo_count)
	{
		if (pthread_create(&(philos[i].thread_id), NULL, routine, &(philos[i]))
			!= 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		usleep(50);
		i++;
	}
	if (start_director(philosophy) == 1)
		return (1);
	return (0);
}

int	start_join(t_philosophy *philosophy, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philosophy->philo_count)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
		{
			printf("Failed to join thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	start(t_philosophy *philosophy)
{
	t_philo	*philos;

	philos = philosophy->philos;
	if (start_threads(philosophy, philos) == 1)
		return (1);
	if (start_join(philosophy, philos) == 1)
		return (1);
	return (0);
}
