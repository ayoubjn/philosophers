/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:18:29 by ajana             #+#    #+#             */
/*   Updated: 2022/08/29 16:53:35 by ajana            ###   ########.fr       */
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

# define RESET "\e[0m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define WHT "\e[0;37m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"

struct	s_args;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				id;
	int				meals;
	int				last_meal;
	int				is_eating;
	struct s_args		*args;
}	t_philo;

typedef struct s_args
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
}	t_args;

int		eat(t_philo *philo, t_philo *next_philo);
void	get_argv(char **av, t_args *args);
void	print_lock(t_philo *philo, char *msg);
int		get_time(struct timeval start);
void	mutex_destroy(t_args *args);
void	*philos_init(t_args *args);
int		police_man(t_args *args);
void	msleep(int time_ms);
void	*routine(void *a);
void	ft_usleep(unsigned long time);
int		read_lock(int var, pthread_mutex_t *lock);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *s);

#endif
