/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:48:56 by rohidalg          #+#    #+#             */
/*   Updated: 2025/06/30 17:56:08 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_write(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	ft_write(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_write(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = ft_get_time() + philo->data->time_to_die;
	ft_write(EATING, philo);
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}

void	ft_write(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = ft_get_time() - philo->data->start_time;
	if (philo->data->dead == 0 && ft_strcmp(DIED, str) == 0)
	{
		printf("%u %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%u %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
