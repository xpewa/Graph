#include <stdio.h>
#include <stdlib.h>

void write_dot(const char * fname, int n, int m,  int g[n][m])
{
    FILE * fo;
    fo = fopen(fname,"wt");
    fprintf(fo, "digraph Graph {\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] == 1)
                fprintf( fo, "  %d -> %d;\n", i, j);
    fprintf(fo, "}\n");
    fclose(fo);

    system("dot -Tpng g.dot -o g.png");
}

void check_connect(int x, int u) {
    if ((x-1)*(x-2)/2 < u)
        printf("The graph IS connected");
    else
        printf("the graph is NOT connected");
    return; 
}

int main(void)
{
    printf("Enter the size of the matrix x*u:\n");
    int x, u;
    while (scanf("%d", &x) != 1 || x < 0)
        scanf("%*[^\n]");
    while (scanf("%d", &u) != 1 || u < 0)
        scanf("%*[^\n]");
    int Graph[x][u];

    printf("Enter the matrix:\n");
    for (int i = 0; i < x; i++) 
        for (int j = 0; j < u; j++) 
            while (scanf("%d", &(Graph[i][j])) != 1 || (Graph[i][j] != 0 && Graph[i][j] != 1))
                scanf("%*[^\n]");

    write_dot("g.dot", x, u, Graph);

    int real_count_u = 0;
    for (int i = 0; i < x; ++i)
        for (int j = 0; j < u; ++j)
            if (Graph[i][j] == 1)
                ++real_count_u;
    check_connect(x, real_count_u);

    return 0;
}