/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:55:27 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 04:00:32 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../philo.h"

int	init_philo(t_philosophy *philosophy)
{
	int	i;
	int	temp;

	i = 0;
	while (i < philosophy->philo_count)
	{
		philosophy->philos[i].id = i;
		philosophy->philos[i].c_ate = 0;
		if (i == philosophy->philo_count - 1)
			philosophy->philos[i].lf_id = 0;
		else
			philosophy->philos[i].lf_id = i + 1;
		philosophy->philos[i].rf_id = i;
		if (i % 2 == 1)
		{
			temp = philosophy->philos[i].lf_id;
			philosophy->philos[i].lf_id = philosophy->philos[i].rf_id;
			philosophy->philos[i].rf_id = temp;
		}
		philosophy->philos[i].philosophy = philosophy;
		philosophy->philos[i].t_last_meal = 0;
		i++;
	}
	return (0);
}

int	init_mutex(t_philosophy *philosophy)
{
	int	i;

	i = 0;
	while (i < philosophy->philo_count)
	{
		if (pthread_mutex_init(&philosophy->forks_mutex[i], NULL) != 0)
			return (1);
		philosophy->forks_value[i] = -1;
		i++;
	}
	if (pthread_mutex_init(&philosophy->dead_m, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philosophy->meals_m, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philosophy->write_m, NULL) != 0)
		return (1);
	return (0);
}

int	check_validity(t_philosophy *philosophy)
{
	if (philosophy->philo_count < 1)
		return (1);
	if (philosophy->eat_count < 0)
		return (1);
	if (philosophy->time_death == 0)
		return (1);
	if (philosophy->time_eat == 0)
		return (1);
	if (philosophy->time_sleep == 0)
		return (1);
	return (0);
}

int	init_philosophy(int argc, char **argv, t_philosophy *philosophy)
{
	long	temp;
	int		i;

	i = 1;
	philosophy->eat_count = 0;
	while (i < argc)
	{
		temp = ft_atoi_ph(argv[i]);
		if (temp == -1)
			return (1);
		if (i == 1)
			philosophy->philo_count = temp;
		if (i == 2)
			philosophy->time_death = temp;
		if (i == 3)
			philosophy->time_eat = temp;
		if (i == 4)
			philosophy->time_sleep = temp;
		if (i == 5)
			philosophy->eat_count = temp;
		i++;
	}
	philosophy->dead = 0;
	philosophy->all_ate = 0;
	return (0);
}

int	init_all(int argc, char **argv, t_philosophy *philosophy)
{
	philosophy->start_time = get_time();
	if (init_philosophy(argc, argv, philosophy) != 0)
		return (1);
	if (check_validity(philosophy) == 1)
		return (1);
	if (init_mutex(philosophy) != 0)
		return (1);
	init_philo(philosophy);
	return (0);
}
