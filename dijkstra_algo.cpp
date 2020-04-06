
#include <stdio.h>
#include <limits.h>


#define VERTEX 9

/* find the vertex with minimum distance value  from the set of
 *  vertices not yet included in shortest path tree(SPT)
 * */
int min_dist(const int *dist, const bool *spt_set)
{
    int min = INT_MAX, min_idx = 0;

    for (unsigned i = 1; i < VERTEX; i++)
        if (spt_set[i] == false && min > dist[i]) {
            min     = dist[i];
            min_idx = i;
        }

    return min_idx;
}

/* print path from source v using parent array */
void print_path(const int *parent, int v)
{
    /* TODO: for large array  stack is better choice */
    if (parent[v] == -1) {
        printf("%d ", v);
        return ;
    }
    print_path(parent, parent[v]);
    printf("%d ", v);
}

void print_spt(const int *dist, int src, const int *parent)
{
    puts("  Vertex    Distance     Path");
    for (unsigned i = 0; i < VERTEX; i++) {
        printf(" %2d -> %2d      %2d         ", src, i, dist[i]);
        print_path(parent, i);
        putchar('\n');
    }
}

/* time compl. of this implementation is O(V^2)  (due to matrix) */
void dijkstra(const int graph[VERTEX][VERTEX], int src)
{
    /* dist[] will hold the shortest distance sourced src */
    int dist[VERTEX];
    /* Shortest Path Tree Set  true if a vertex in included in SPT
     *  or shortest distance from src to i is finalized
     * */
    bool spt_set[VERTEX];

    /* parent array to store shortest path tree */
    int parent[VERTEX];
    parent[src]  = -1;            /* assuming source have no parent */

    for (unsigned i = 0; i < VERTEX; i++) {
        dist[i]    = INT_MAX;       /* unreachable */
        spt_set[i] = false;         /* not in SPT set */
    }

    /* distance of source vertex to itself always 0 */
    dist[src] = 0;

    /* find shortest path for all vertices */
    for (unsigned i = 0; i < VERTEX-1; i++) {
        /* pick minimum vertex of those vertices not processed
         *  u is always equal to src in the first call of min_dist()
         *  */
        int u = min_dist(dist, spt_set);

        /* mark the picked vertex as processed */
        spt_set[u] = true;

        /* if current unprocessed vertex is unreachable
         *  for those disconnected vertex
         * */
        if (dist[u] == INT_MAX) continue;

        /* update dist[] of adjacent vertices of the picked vertex */
        for (unsigned v = 0; v < VERTEX; v++)
            /* update dist[v] only if
             *  1) there is a edge from u to v
             *  2) it's not in spt_set[]
             *  3) distance of path from src to v through u
             *    is smaller than current value of dist[v]
             * */
            if (graph[u][v] && spt_set[v] == false &&
                    dist[u] + graph[u][v] < dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    /* print the constructed distance array */
    print_spt(dist, src, parent);
}

int main(void)
{

    int graph[VERTEX][VERTEX] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0},
    };

    puts("Dijkstra of vertex 0");
    dijkstra(graph, 0);

    return 0;
}
