#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct graph *create_graph()
{
	struct graph *created = malloc(sizeof(struct graph));
	created->vertices = NULL;

	return created;
}

struct vertex *add_vertex(struct graph *graph, int value)
{
	struct vertex *next = malloc(sizeof(struct vertex));
	next->element = value;
	next->edges = NULL;
	next->next = graph->vertices;
	graph->vertices = next;

	return next;
}

void add_edge(struct vertex *vertex1, struct vertex *vertex2)
{
	struct edge *next = malloc(sizeof(struct edge));
	next->connects_to = vertex2;
	next->next = vertex1->edges;
	vertex1->edges = next;
}

void print_graph(struct graph *graph)
{
	int edge_count = 0;
	struct vertex *last_vertex = graph->vertices;
	
	while (last_vertex != NULL) {
		printf("Vertex: %d connects to: ", last_vertex->element);

		struct edge *last_edge = last_vertex->edges;

		while (last_edge != NULL) {
			if (last_edge->connects_to != NULL) {
				edge_count++;
				printf("%d, ", last_edge->connects_to->element);
			}

			last_edge = last_edge->next;
		}

		printf("\n");

		last_vertex = last_vertex->next;
	}

	printf("Total edge count: %d\n", edge_count);
}

