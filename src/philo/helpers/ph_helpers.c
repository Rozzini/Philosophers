/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 04:09:05 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/13 04:00:35 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../philo.h"

int	ft_atoi_ph(const char *str)
{
	int				i;
	unsigned long	integer;

	integer = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			integer = integer * 10 + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	return ((int)integer);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		millisec;

	gettimeofday(&time, NULL);
	millisec = time.tv_sec * 1000LL + time.tv_usec / 1000;
	return (millisec);
}

long long	get_t_pf(t_philosophy *philosophy)
{
	struct timeval	time;
	long long		cur_time;

	gettimeofday(&time, NULL);
	cur_time = time.tv_sec * 1000LL + time.tv_usec / 1000;
	return (cur_time - philosophy->start_time);
}
