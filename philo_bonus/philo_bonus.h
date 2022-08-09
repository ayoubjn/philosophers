/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:18:29 by ajana             #+#    #+#             */
/*   Updated: 2022/08/09 22:36:08 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <string.h>
# include <signal.h>

# define reset "\e[0m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define WHT "\e[0;37m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"


struct args;

typedef struct philo
{
	int				id;
	int				meals;
	int				last_meal;
	int				pid;
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
	sem_t			*forks;
	sem_t			*print_sem;
	struct timeval	start;
} t_args;

int		eat(t_philo *philo);
void	get_argv(char **av, t_args *args);
void	print_lock(t_philo *philo, char *msg);
int		get_time(struct timeval start);
void	mutex_destroy(t_args *args);
void	*philos_init(t_args *args);
int		police_man(t_args *args);
void	msleep(int time_ms);
void	routine(t_philo *philo);
void	ft_usleep(unsigned long time);

#endif
