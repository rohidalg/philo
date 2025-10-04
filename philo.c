/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:33:26 by rohidalg          #+#    #+#             */
/*   Updated: 2025/10/04 16:49:07 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		return (printf("ft_get_time() FAILUREN\n"));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	i_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, 0);
		i++;
	}
}

int	i_data(t_data *data, int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	data->n_philos = (int)ft_atoi(argv[1]);
	data->time_to_die = (int)ft_atoi(argv[2]);
	data->time_to_eat = (int)ft_atoi(argv[3]);
	data->time_to_sleep = (int)ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = (int)ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	data->dead = 0;
	data->finish = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL)
		|| pthread_mutex_init(&data->lock, NULL))
		return (1);
	return (0);
}

int	i_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], 0);
		i++;
	}
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->n_philos - 1];
	i = 1;
	while (i < data->n_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	if (i_data(&data, argc, argv) != 0)
		return (1);
	if (ft_malloc(&data) != 0)
		return (ft_exit(&data));
	if (i_forks(&data) != 0)
		return (ft_exit(&data));
	i_philos(&data);
	if (data.n_philos == 1)
		return (one_philo(&data));
	if (i_dinner(&data) != 0)
		return (ft_exit(&data));
	ft_exit(&data);
	return (0);
}

// filosofos morir comer dormir
// [number_of_times_each_philosopher_must_eat]

// 🧠 Funciones de memoria
// memset(void *s, int c, size_t n)
// Rellena los primeros n bytes del bloque de memoria apuntado por s con el byte c.
// 👉 Se usa para inicializar arrays o estructuras.

// malloc(size_t size)
// Reserva dinámicamente size bytes de memoria en el heap y devuelve un puntero al comienzo.
// 👉 Recuerda liberar con free.

// free(void *ptr)
// Libera memoria previamente reservada con malloc, calloc o realloc.
// 👉 Evita memory leaks.

// 🖨️ Entrada / Salida
// printf(const char *format, ...)
// Imprime texto formateado en la salida estándar (normalmente la pantalla).

// write(int fd, const void *buf, size_t count)
// Escribe count bytes desde buf al descriptor de archivo fd.
// 👉 fd = 1 es stdout.

// ⏱️ Temporización
// usleep(useconds_t microseconds)
// Pausa la ejecución actual durante la cantidad de microsegundos indicada.
// 👉 usleep(1000) duerme 1 milisegundo.

// gettimeofday(struct timeval *tv, struct timezone *tz)
// Llena la estructura tv con el tiempo actual (segundos y microsegundos desde Epoch).
// 👉 Se usa para medir tiempos con precisión.

// 🧵 Funciones de hilos (pthread)
// pthread_create(pthread_t *thread,	const pthread_attr_t *attr,void *(*start_routine)(void *),
//	void *arg)
// Crea un nuevo hilo que ejecuta la función start_routine con el argumento arg.

// pthread_detach(pthread_t thread)
// Desvincula un hilo del hilo principal,permitiendo que sus recursos se liberen automáticamente cuando termine.
// 👉 Ya no se puede hacer pthread_join sobre él.

// pthread_join(pthread_t thread, void **retval)
// Espera a que termine un hilo específico. Útil para sincronizar.

// 🔒 Mutex (exclusión mutua)
// pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
// Inicializa un mutex para sincronización entre hilos.

// pthread_mutex_destroy(pthread_mutex_t *mutex)
// Libera los recursos de un mutex previamente inicializado.

// pthread_mutex_lock(pthread_mutex_t *mutex)
// Bloquea el mutex. Si otro hilo ya lo tiene, espera.

// pthread_mutex_unlock(pthread_mutex_t *mutex)
// Libera el mutex para que otros hilos puedan usarlo.

// CON EL EJEMPLO DE ./philo 2000 1000 1000 5 SE QUEDA 
// PENSANDO UN SEGUNDO ANTES DE ACABAR LO QUE SIGINIFICA QUE ESTA MAL Y ME LO PUEDEN 
// TIRAR POR ESO ASI QUE CORRIGELO CUANDO LO VEAS, SE SUPONE QUE LO PONE EN EL SUBJECT 
// DE QUE SI MUERE TIENE QUE ACABAR AL INSTANNTE