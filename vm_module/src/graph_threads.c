/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:02:57 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/23 18:21:30 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "corewar.h"
#include "graph.h"

void *func_thread_game(void *arg)
{
	t_core *c = (t_core*)arg;
	the_game(c);
	pthread_exit(NULL);
}

void *func_thread_ctrl(void *arg)
{
	t_core *c = (t_core*)arg;

	while(1)
	{
		refresh_all_wins(c);
		print_process(c->graph, c->process);
		if(controls(c->graph))
			pthread_exit(NULL);
		if (!c->graph->pause)
			print_infos(c);
	}
	pthread_exit(NULL);
}

int		init_thread(t_core *c)
{
	pthread_t thread_ctrl;
	pthread_t thread_game;

	//printf("Avant la création du thread.\n");

	if (pthread_create(&thread_ctrl, NULL, func_thread_ctrl, c))
		return 1; //CREER ERREUR
	if (pthread_create(&thread_game, NULL, func_thread_game, c))
		return 1;
	if (pthread_join(thread_ctrl, NULL))
		return 1;
	//if (pthread_join(thread_game, NULL))
	//	return 1;

	//printf("Après la création du thread.\n");

	return (0);
}
