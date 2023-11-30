#include <stdio.h>
#include <limits.h>

#define MAX 100

int graph[MAX][MAX];
int vertices;

void initializeGraph() {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int start, int end, int weight) {
    graph[start][end] = weight;
}

void dijkstra(int start, int end) {
    int dist[vertices];
    int visited[vertices];

    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int minDist = INT_MAX, minIndex;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        visited[minIndex] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[minIndex][v] && dist[minIndex] != INT_MAX &&
                dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    printf("Shortest distance from Node %d to Node %d: %d\n", start, end, dist[end]);
}

int main() {
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    initializeGraph();

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges and their weights (format: start end weight):\n");
    for (int i = 0; i < edges; i++) {
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);
        addEdge(start, end, weight);
    }

    int startNode, endNode;
    printf("Enter the start node and end node: ");
    scanf("%d %d", &startNode, &endNode);

    dijkstra(startNode, endNode);

    return 0;
}
