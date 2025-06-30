/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:25:54 by rohidalg          #+#    #+#             */
/*   Updated: 2025/06/30 18:15:51 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	data->start_time = ft_get_time();
	if (pthread_create(&data->tid[0], 0, &actions, &data->philos[0]))
		return (ft_exit(data));
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

void	*manager(void *data_pointer)
{
	t_data	*data;
	int		i;

	data = ((t_philo *)data_pointer)->data;
	while (1)
	{
		i = -1;
		data->philos_done = 0;
		while (++i < data->n_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if (data->philos[i].meals_eaten >= data->meals_required)
				data->philos_done++;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
		}
		if (data->philos_done == data->n_philos)
		{
			pthread_mutex_lock(&data->print_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
// NECESITO HACER QUE SEA UNA LINEA MENOS Y ESTOY PENSANDO EN BORRAR USSLEEP.

void	*waiter(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (ft_get_time() >= philo->time_to_die && philo->eating == 0)
		{
			ft_write(DIED, philo);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(100);
	}
	return (NULL);
}

void	*actions(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->time_to_die + ft_get_time();
	if (pthread_create(&philo->waiter, 0, &waiter, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		ft_write(THINKING, philo);
	}
	if (pthread_join(philo->waiter, 0))
		return ((void *)1);
	return ((void *)0);
}

int	i_dinner(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = 0;
	data->start_time = ft_get_time();
	if (data->meals_required > 0)
	{
		if (pthread_create(&t0, 0, &manager, &data->philos[0]))
			return (ft_exit(data));
	}
	while (i < data->n_philos)
	{
		if (pthread_create(&data->tid[i], 0, &actions, &data->philos[i]))
			return (ft_exit(data));
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->tid[i], 0))
			return (ft_exit(data));
		i++;
	}
	return (0);
}
