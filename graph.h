#include <stdbool.h>

struct graph {
	struct vertex *vertices;
	int vertex_count;
};

struct vertex {
	int *possibilities;
	int num_possible;

	struct edge *edges;
	struct vertex *next;
};


struct edge {
	struct vertex *connects_to;
	struct edge *next;
};


struct graph *create_graph();
struct vertex *add_single_value_vertex(struct graph *graph, int value);
struct vertex *add_multiple_value_vertex(struct graph *graph, int *possible_values, int count);
void add_edge(struct vertex *vertex1, struct vertex *vertex2);
int *make_colors(int count);
void print_graph(struct graph *graph);

bool color_graph(struct vertex *vertex);
bool graph_colored(struct graph *graph);
