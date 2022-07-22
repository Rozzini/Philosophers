/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 04:15:14 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 05:53:43 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../philo.h"

void	check_meal_director(t_philosophy *philosophy)
{
	int	i;

	i = 0;
	while (i < philosophy->philo_count)
	{
		pthread_mutex_lock(&philosophy->meals_m);
		if (philosophy->philos[i].c_ate < philosophy->eat_count)
		{
			pthread_mutex_unlock(&philosophy->meals_m);
			break ;
		}
		pthread_mutex_unlock(&philosophy->meals_m);
		usleep(50);
		i++;
	}
	pthread_mutex_lock(&philosophy->meals_m);
	if (i == philosophy->philo_count)
		philosophy->all_ate = 1;
	pthread_mutex_unlock(&philosophy->meals_m);
}

void	death_case(t_philosophy	*philosophy, int i)
{
	pthread_mutex_lock(&philosophy->write_m);
	printf("%lld %d DIED\n", get_t_pf(philosophy), i + 1);
	pthread_mutex_unlock(&philosophy->write_m);
	pthread_mutex_lock(&philosophy->dead_m);
	philosophy->dead = 1;
	pthread_mutex_unlock(&philosophy->dead_m);
}

int	try_death_check(t_philosophy *philosophy, int i)
{
	pthread_mutex_lock(&philosophy->dead_m);
	if (get_time() - philosophy->philos[i].t_last_meal
		>= philosophy->time_death)
	{
		pthread_mutex_unlock(&philosophy->dead_m);
		death_case(philosophy, i);
		return (1);
	}
	pthread_mutex_unlock(&philosophy->dead_m);
	return (0);
}

void	*check_death_director(void *phil)
{
	int				i;
	t_philosophy	*philosophy;

	philosophy = (t_philosophy *)phil;
	i = 0;
	while (1)
	{
		if (try_death_check(philosophy, i) == 1)
			return (NULL);
		if (philosophy->eat_count != 0)
			check_meal_director(philosophy);
		pthread_mutex_lock(&philosophy->meals_m);
		if (philosophy->all_ate == 1)
		{
			pthread_mutex_unlock(&philosophy->meals_m);
			return (NULL);
		}
		pthread_mutex_unlock(&philosophy->meals_m);
		if (i == philosophy->philo_count - 1)
			i = -1;
		usleep(50);
		i++;
	}
	return (NULL);
}
