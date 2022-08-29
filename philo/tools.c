/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:38:09 by ajana             #+#    #+#             */
/*   Updated: 2022/08/29 16:53:15 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int	a;
	int	sign;
	int	i;

	a = 0;
	i = 0;
	sign = 1;
	while (s[i])
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		a = a * 10 + (s[i] - 48);
		i++;
	}
	return (sign * a);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] == s2[i]) && (s1[i] && s2[i]))
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	get_time(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * 1000 + (end.tv_usec / 1000))
		- (start.tv_sec * 1000 + (start.tv_usec / 1000)));
}

void	print_lock(t_philo *philo, char *msg)
{
	int	time;

	time = get_time(philo->args->start);
	if (pthread_mutex_lock(&(philo->args->p_lock)))
		return ;
	printf(WHT "%d %d %s", time, philo->id, msg);
	if (ft_strcmp(msg, RED "died\n"))
	{
		if (pthread_mutex_unlock(&(philo->args->p_lock)))
			return ;
		return ;
	}
}

void	mutex_destroy(t_args *args)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(args->p_lock));
	pthread_mutex_destroy(&(args->wr_lock));
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&((*args->philos_arr).fork));
		i++;
	}
}
