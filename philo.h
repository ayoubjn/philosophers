/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:18:29 by ajana             #+#    #+#             */
/*   Updated: 2022/08/02 19:29:59 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdatomic.h>

# define reset "\e[0m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define WHT "\e[0;37m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define BLK "\e[0;30m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"

struct args;

typedef struct philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				id;
	int				meals;
	int				last_meal;
	int				is_eating;
	struct args		*args;
} t_philo;

typedef	struct args
{
	int				num_of_philos;
	int				time_to_sleep;
	int				num_of_meals;
	int				time_to_die;
	int				time_to_eat;
	t_philo			*philos_arr;
	pthread_mutex_t	wr_lock;
	pthread_mutex_t	p_lock;
	struct timeval	start;
} t_args;

int		eat(t_philo *philo, t_philo *next_philo);
void	get_argv(char **av, t_args *args);
void	print_lock(t_philo *philo, char *msg);
int		get_time(struct timeval start);
void	mutex_destroy(t_args *args);
void	*philos_init(t_args *args);
void	*police_man(t_args *args);
void	msleep(int time_ms);
void	*routine(void *a);

#endif