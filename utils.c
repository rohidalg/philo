/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:07:17 by rohidalg          #+#    #+#             */
/*   Updated: 2025/05/13 13:33:29 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	isneg;
	int	sum;

	i = 0;
	isneg = 1;
	sum = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\r' || s[i] == '\f')
		i++;
	if (s[i] == '-')
		isneg = -isneg;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
	{
		sum = sum * 10;
		sum = sum + (s[i] - '0');
		i++;
	}
	return (sum * isneg);
}

int	ft_usleep(__useconds_t time)
{
	uint64_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(data->forks);
		pthread_mutex_destroy(data->philos[i].lock);
	}
	pthread_mutex_destroy(data->print_mutex);
	pthread_mutex_destroy(data->lock);
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	return (1);
}

int	ft_malloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->tid)
		return (ft_exit(data));
	data->philos = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->philos)
		return (ft_exit(data));
	data->forks = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->forks)
		return (ft_exit(data));
	return (0);
}
