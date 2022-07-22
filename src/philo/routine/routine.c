/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 04:12:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 06:42:53 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../philo.h"

int	routine_solo(t_philosophy *philosophy, t_philo *philo)
{
	if (philo->id % 2 == 1)
		usleep(100);
	if (philosophy->philo_count == 1)
	{
		while (1)
		{
			if (check_death(philosophy) == 1)
				return (1);
		}
	}
	return (0);
}

int	routine_eat(t_philosophy *ph, t_philo *philo)
{
	if (routine_message(ph, philo, 2) == 3)
	{
		pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
		pthread_mutex_unlock(&ph->forks_mutex[philo->rf_id]);
		return (1);
	}
	pthread_mutex_lock(&ph->meals_m);
	philo->t_last_meal = get_time();
	philo->c_ate++;
	pthread_mutex_unlock(&ph->meals_m);
	if (ft_usleep(ph, ph->time_eat) == 1)
	{
		pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
		pthread_mutex_unlock(&ph->forks_mutex[philo->rf_id]);
		return (1);
	}
	ph->forks_value[philo->lf_id] = philo->id;
	ph->forks_value[philo->rf_id] = philo->id;
	pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
	pthread_mutex_unlock(&ph->forks_mutex[philo->rf_id]);
	return (0);
}

int	routine_try_eat(t_philosophy *ph, t_philo *philo)
{
	while (1)
	{
		if (try_take_forks(ph, philo) == 1)
			return (1);
		if (check_death(ph) == 1)
		{
			pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
			pthread_mutex_unlock(&ph->forks_mutex[philo->rf_id]);
			return (1);
		}
		if (ph->forks_value[philo->lf_id] != philo->id
			&& ph->forks_value[philo->rf_id] != philo->id)
		{
			routine_message(ph, philo, 1);
			if (routine_eat(ph, philo) == 1)
				return (1);
			break ;
		}
		pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
		pthread_mutex_unlock(&ph->forks_mutex[philo->rf_id]);
		if (check_death(ph) == 1)
			return (1);
	}
	return (0);
}

void	*routine(void *phil)
{
	t_philo			*philo;
	t_philosophy	*philosophy;

	philo = (t_philo *)phil;
	philosophy = philo->philosophy;
	philo->t_last_meal = get_time();
	if (routine_solo(philosophy, philo) == 1)
		return (NULL);
	while (1)
	{
		if (routine_try_eat(philosophy, philo) == 1)
			return (NULL);
		if (routine_message(philosophy, philo, 3) == 1)
			return (NULL);
		if (ft_usleep(philosophy, philosophy->time_sleep) == 1)
			return (NULL);
		if (routine_message(philosophy, philo, 4) == 3)
			return (NULL);
		if (check_death(philosophy) == 1)
			return (NULL);
	}
	return (NULL);
}
