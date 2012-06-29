#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct graph *create_graph()
{
	struct graph *created = malloc(sizeof(struct graph));
	created->vertices = NULL;
	created->vertex_count = 0;

	return created;
}

struct vertex *add_single_value_vertex(struct graph *graph, int value)
{
	struct vertex *next = malloc(sizeof(struct vertex));
	next->possibilities = malloc(sizeof(int));
	*next->possibilities = value;
	next->num_possible = 1;
	next->edges = NULL;
	next->next = graph->vertices;
	graph->vertices = next;
	graph->vertex_count++;

	return next;
}

struct vertex *add_multiple_value_vertex(struct graph *graph, int *possible_values, int count)
{
	struct vertex *next = malloc(sizeof(struct vertex));

	next->possibilities = possible_values;
	next->num_possible = count;
	next->edges = NULL;
	next->next = graph->vertices;
	graph->vertices = next;
	graph->vertex_count++;

	return next;
}

void add_edge(struct vertex *vertex1, struct vertex *vertex2)
{
	struct edge *next = malloc(sizeof(struct edge));
	next->connects_to = vertex2;
	next->next = vertex1->edges;
	vertex1->edges = next;
}

// create a new array of colors
int *make_colors(int count)
{
	int *possible_values = malloc(sizeof(int) * count);

	int c = 1;
	for (c = 1; c <= count; c++)
		possible_values[c - 1] = c;
	
	return possible_values;
}

void print_graph(struct graph *graph)
{
	int edge_count = 0;
	struct vertex *last_vertex = graph->vertices;
	
	while (last_vertex != NULL) {
		printf("Vertex [");
		int i = 0;
		for (i = 0; i < last_vertex->num_possible; i++)
			printf("%d, ", last_vertex->possibilities[i]);
		printf("] connects to vertices: ");

		struct edge *last_edge = last_vertex->edges;

		while (last_edge != NULL) {
			if (last_edge->connects_to != NULL) {
				edge_count++;

				int j = 0;
				printf("[");
				for (j = 0; j < last_edge->connects_to->num_possible; j++)
					printf("%d, ", last_edge->connects_to->possibilities[j]);
				printf("], ");
			}

			last_edge = last_edge->next;
		}

		printf("\n");

		last_vertex = last_vertex->next;
	}

	printf("Total edge count: %d\n", edge_count);
}

