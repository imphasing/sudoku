#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


// determine is a vertex is constrained to only a single given color
bool vertex_must_be(struct vertex *vertex, int color)
{
	if (vertex->num_possible == 1 && vertex->possibilities[0] == color)
		return true;

	return false;
}


// determine whether a vertex's edges would disallow a given color to be chosen
bool edges_disallow_color(struct vertex *vertex, int color)
{
	bool in_edge = false;
	struct edge *last_edge = vertex->edges;

	while (last_edge != NULL) {
		if (last_edge->connects_to != NULL) {
			struct vertex *connected = last_edge->connects_to;
			in_edge = vertex_must_be(connected, color);
		}

		if (in_edge == true)
			return true;

		last_edge = last_edge->next;
	}

	return in_edge;
}


// Pick a color for a vertex to try next
int choose_color(struct vertex *vertex)
{
	if (vertex->num_possible == 1)
		return 0;
	else {
		int chosen_index;
		for (chosen_index = 0; chosen_index < vertex->num_possible; chosen_index++) {
			if (edges_disallow_color(vertex, vertex->possibilities[chosen_index]))
				continue;
			else
				return chosen_index;
		}
	}

	return -1;
}


int *remove_possibility(int *possibilities, int count, int color)
{
	int *new_possible = malloc(sizeof(int) * (count - 1));
	
	int i, j;
	for (j = 0, i = 0; i < count; i++) {
		if (possibilities[i] == color)
			continue;

		new_possible[j] = possibilities[i];
		j++;
	}

	return new_possible;
}


bool color_graph(struct vertex *vertex)
{
	if (vertex == NULL)
		return true;

	int original_count = vertex->num_possible;

	if (original_count == 1)
		return color_graph(vertex->next);
	
	while (vertex->num_possible > 1) {
		int *saved_possible = vertex->possibilities;
		int saved_num = vertex->num_possible;

		int next_candidate = choose_color(vertex);

		if (next_candidate == -1)
			return false;

		int *next_color = malloc(sizeof(int));
		*next_color = saved_possible[next_candidate];

		vertex->possibilities = next_color;
		vertex->num_possible = 1;

		bool success = color_graph(vertex->next);

		if (success == false)
		{
			int *new_possible = remove_possibility(
				saved_possible, 
				saved_num,
				*next_color);

			vertex->possibilities = new_possible;
			vertex->num_possible = saved_num - 1;
		}
		else
			return true;
	}

	return false;
}


// check if each of the vertices has only a single color possibility, meaning it's colored
bool graph_colored(struct graph *graph)
{
	struct vertex *next_vertex = graph->vertices;
	while (next_vertex != NULL) {
		if (next_vertex->num_possible > 1)
			return false;

		next_vertex = next_vertex->next;
	}

	return true;
}


