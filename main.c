#include <stdio.h>
#include <stdlib.h>

typedef struct tGraph {
    int count_vertex;
    int count_ribs;
    int** matrix;
} tGraph;

tGraph* create_Graph(int n, int m) {
    tGraph* Graph = (tGraph*)malloc(sizeof(tGraph));
    if (Graph == NULL) {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    Graph->count_vertex = n;
    Graph->count_ribs = m;
    Graph->matrix = (int**)malloc(n*sizeof(int*));
    if (Graph->matrix == NULL) {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    for (int i=0; i < m; ++i) {
        Graph->matrix[i] = (int*)malloc(m*sizeof(int));
        if (Graph->matrix[i] == NULL) {
            printf("Failed to allocate memory!\n");
            return NULL;
        }
    }
    return Graph;
}

void create_matrix(tGraph* Graph) {
    printf("\nEnter the matrix:\n");
    for (int i = 0; i < Graph->count_vertex; i++) 
        for (int j = 0; j < Graph->count_ribs; j++) 
            while (scanf("%d", &(Graph->matrix[i][j])) != 1 || (Graph->matrix[i][j] != 0 && Graph->matrix[i][j] != 1))
                scanf("%*[^\n]");
}

void check_connect(tGraph* Graph) {
    int real_count_u = 0;
    for (int i = 0; i < Graph->count_vertex; ++i)
        for (int j = 0; j < Graph->count_ribs; ++j)
            if (Graph->matrix[i][j] == 1)
                ++real_count_u;

    if ((Graph->count_vertex-1)*(Graph->count_vertex-2)/2 < Graph->count_ribs)
        printf("\nThe graph IS connected\n");
    else
        printf("\nThe graph is NOT connected\n");
    return; 
}

void write_dot(const char * fname, tGraph* Graph)
{
    FILE * f;
    f = fopen(fname,"wt");
    fprintf(f, "digraph Graph {\n");
    fprintf(f, "    graph [center=1 rankdir=LR bgcolor=\"#E6E6FA\"]\n");
    fprintf(f, "   node [shape=diamond color=\"#DC143C\"];\n");
    for (int i = 0; i < Graph->count_vertex; ++i)
        for (int j = 0; j < Graph->count_ribs; ++j)
            if (Graph->matrix[i][j] == 1)
                fprintf( f, "   %d -> %d [color=\"#8B68EE\"];\n", i, j);
    fprintf(f, "}\n");
    fclose(f);

    system("dot -Tpng Graph.dot -o Graph.png");
}

int main(void)
{
    system("cls");
    system("color 70");
    system("title Graph");

    printf("Enter the size of the matrix x*u:\n");
    int count_vertex, count_ribs;
    while (scanf("%d", &count_vertex) != 1 || count_vertex < 0)
        scanf("%*[^\n]");
    while (scanf("%d", &count_ribs) != 1 || count_ribs < 0)
        scanf("%*[^\n]");
    tGraph* Graph = create_Graph(count_vertex, count_ribs); 
    if (NULL == Graph) {
        return -1;
    }

    create_matrix(Graph);

    write_dot("Graph.dot", Graph);

    check_connect(Graph);

    free(Graph);

    return 0;
}