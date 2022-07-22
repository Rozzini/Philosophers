/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 05:35:50 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/15 03:50:30 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_philosophy;

typedef struct s_philo
{
	int						id;
	int						c_ate;
	int						lf_id;
	int						rf_id;
	long long				t_last_meal;
	struct s_philosophy		*philosophy;
	pthread_t				thread_id;
}							t_philo;

typedef struct s_philosophy
{
	int					philo_count;
	int					eat_count;
	long long			time_death;
	long long			time_eat;
	long long			time_sleep;
	int					dead;
	int					all_ate;
	long long			start_time;
	pthread_mutex_t		dead_m;
	pthread_mutex_t		meals_m;
	pthread_mutex_t		write_m;
	pthread_mutex_t		forks_mutex[250];
	int					forks_value[250];
	t_philo				philos[250];
}						t_philosophy;

int			ft_atoi_ph(const char *str);
long long	get_time(void);
long long	get_t_pf(t_philosophy *philosophy);

int			init_philo(t_philosophy *philosophy);
int			init_mutex(t_philosophy *philosophy);
int			init_philosophy(int argc, char **argv, t_philosophy *philosophy);
int			init_all(int argc, char **argv, t_philosophy *philosophy);

int			check_death(t_philosophy *ph);
int			ft_usleep(t_philosophy *philosophy, int sleep);
int			routine_message(t_philosophy *philosophy, t_philo *philo, int text);
int			try_take_forks(t_philosophy *philosophy, t_philo *philo);

int			routine_solo(t_philosophy *philosophy, t_philo *philo);
int			routine_eat(t_philosophy *ph, t_philo *philo);
int			routine_try_eat(t_philosophy *ph, t_philo *philo);
void		*routine(void *phil);

void		check_meal_director(t_philosophy *philosophy);
void		*check_death_director(void *phil);

int			start_threads(t_philosophy *philosophy, t_philo *philos);
int			start_join(t_philosophy *philosophy, t_philo *philos);
int			start(t_philosophy *philosophy);

#endif