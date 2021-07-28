#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct {
	int64_t id;
	int64_t degree;
	int64_t reverse_sum;
}
vertex_t;

int read_vertex(vertex_t *, int64_t);
int compare_vertices(const void *, const void *);
int erdos_gallai(int64_t, vertex_t *);

int main(void) {
	int64_t vertices_n, i;
	vertex_t *vertices;
	if (scanf("%"SCNi64, &vertices_n) != 1 || vertices_n < 1) {
		fprintf(stderr, "Invalid number of vertices\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	vertices = malloc(sizeof(vertex_t)*(size_t)vertices_n);
	if (!vertices) {
		fprintf(stderr, "Could not allocate memory for vertices\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	for (i = 0; i < vertices_n; i++) {
		if (!read_vertex(vertices+i, i)) {
			free(vertices);
			return EXIT_FAILURE;
		}
	}
	qsort(vertices, (size_t)vertices_n, sizeof(vertex_t), compare_vertices);
	printf("Result %d\n", erdos_gallai(vertices_n, vertices));
	fflush(stdout);
	free(vertices);
	return EXIT_SUCCESS;
}

int read_vertex(vertex_t *vertex, int64_t id) {
	vertex->id = id;
	if (scanf("%"SCNi64, &vertex->degree) != 1 || vertex->degree < 0) {
		fprintf(stderr, "Invalid vertex degree\n");
		fflush(stderr);
		return 0;
	}
	return 1;
}

int compare_vertices(const void *a, const void *b) {
	const vertex_t *vertex_a = (const void *)a, *vertex_b = (const void *)b;
	if (vertex_a->degree < vertex_b->degree) {
		return 1;
	}
	if (vertex_a->degree > vertex_b->degree) {
		return -1;
	}
	if (vertex_a->id < vertex_b->id) {
		return -1;
	}
	if (vertex_a->id > vertex_b->id) {
		return 1;
	}
	return 0;
}

int erdos_gallai(int64_t vertices_n, vertex_t *vertices) {
	int64_t degrees_sum = 0, reverse_start = vertices_n-1, i;
	for (i = vertices_n-1; i >= 0; i--) {
		vertices[i].reverse_sum = degrees_sum;
		degrees_sum += vertices[i].degree;
	}
	if (degrees_sum%2 == 1) {
		return 2;
	}
	degrees_sum = 0;
	for (i = 0; i < vertices_n; i++) {
		int64_t mins_sum = (i+1)*i;
		degrees_sum += vertices[i].degree;
		if (degrees_sum <= mins_sum) {
			return 0;
		}
		while (reverse_start > i && vertices[reverse_start].degree < i+1) {
			reverse_start--;
		}
		if (reverse_start > i) {
			mins_sum += (reverse_start-i)*(i+1)+vertices[reverse_start].reverse_sum;
		}
		else {
			mins_sum += vertices[i].reverse_sum;
		}
		if (degrees_sum > mins_sum) {
			return 1;
		}
	}
	return 0;
}
