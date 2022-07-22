/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 04:12:55 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 06:40:46 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../philo.h"

int	check_death(t_philosophy *ph)
{
	pthread_mutex_lock(&ph->meals_m);
	if (ph->eat_count != 0 && ph->all_ate == 1)
	{
		pthread_mutex_unlock(&ph->meals_m);
		return (1);
	}
	pthread_mutex_unlock(&ph->meals_m);
	pthread_mutex_lock(&ph->dead_m);
	if (ph->dead == 1)
	{
		pthread_mutex_unlock(&ph->dead_m);
		return (1);
	}
	pthread_mutex_unlock(&ph->dead_m);
	return (0);
}

int	try_take_forks(t_philosophy *ph, t_philo *philo)
{
	if (check_death(ph) == 1)
		return (1);
	pthread_mutex_lock(&ph->forks_mutex[philo->lf_id]);
	if (check_death(ph) == 1)
	{
		pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
		return (1);
	}
	pthread_mutex_lock(&ph->forks_mutex[philo->rf_id]);
	if (check_death(ph) == 1)
	{
		pthread_mutex_unlock(&ph->forks_mutex[philo->lf_id]);
		pthread_mutex_unlock(&ph->forks_mutex[philo->rf_id]);
		return (1);
	}
	return (0);
}

int	ft_usleep(t_philosophy *philosophy, int sleep)
{
	long long	t;

	t = get_time();
	while (get_time() - t < sleep)
	{
		if (check_death(philosophy) == 1)
			return (1);
		usleep(100);
	}
	return (0);
}

int	routine_message(t_philosophy *philosophy, t_philo *philo, int text)
{
	if (check_death(philosophy) == 1)
		return (1);
	pthread_mutex_lock(&philo->philosophy->write_m);
	if (text == 1)
		printf("%lld %d has taken a fork\n", get_t_pf(philosophy),
			philo->id + 1);
	if (text == 2)
		printf("%lld %d is eating\n", get_t_pf(philosophy), philo->id + 1);
	if (text == 3)
		printf("%lld %d is sleeping\n", get_t_pf(philosophy), philo->id + 1);
	if (text == 4)
		printf("%lld %d is thinking\n", get_t_pf(philosophy), philo->id + 1);
	pthread_mutex_unlock(&philo->philosophy->write_m);
	return (0);
}
