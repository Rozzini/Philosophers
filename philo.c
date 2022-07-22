/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 05:35:35 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 03:05:14 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_philosophy	*philosophy)
{
	int	i;

	i = 0;
	while (i < philosophy->philo_count)
	{
		if (pthread_mutex_destroy(&(philosophy->forks_mutex[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&(philosophy->dead_m)) != 0)
		return (1);
	if (pthread_mutex_destroy(&(philosophy->meals_m)) != 0)
		return (1);
	if (pthread_mutex_destroy(&(philosophy->write_m)) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosophy	*philosophy;

	philosophy = malloc(sizeof(t_philosophy));
	if (init_all(argc, argv, philosophy) == 1 || (argc < 5 || argc > 6))
	{
		printf("Error\n");
		free(philosophy);
		return (0);
	}
	if (start(philosophy) == 1)
	{
		destroy_mutex(philosophy);
		free(philosophy);
		return (0);
	}
	destroy_mutex(philosophy);
	free(philosophy);
	return (0);
}
