#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];

void initializeGraph(int vertices) {
    int i, j;
    for (i = 0; i < vertices; i++) {
        visited[i] = 0;
        for (j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int start, int end) {
    graph[start][end] = 1;
    graph[end][start] = 1; // Uncomment this line for undirected graph
}

void BFS(int start, int vertices) {
    int queue[MAX], front = -1, rear = -1, i;
    
    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        start = queue[++front];
        printf("%d ", start);

        for (i = 0; i < vertices; i++) {
            if (!visited[i] && graph[start][i] == 1) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

void DFS(int start, int vertices) {
    int i;

    visited[start] = 1;
    printf("%d ", start);

    for (i = 0; i < vertices; i++) {
        if (!visited[i] && graph[start][i] == 1) {
            DFS(i, vertices);
        }
    }
}

int main() {
    int vertices = 5; // Change this to the desired number of vertices
    initializeGraph(vertices);

    // Define the graph in matrix form
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);

    int startVertex = 0; // Change this to the desired starting vertex

    printf("BFS Traversal starting from vertex %d: ", startVertex);
    BFS(startVertex, vertices);

    // Reset visited array
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }

    printf("\nDFS Traversal starting from vertex %d: ", startVertex);
    DFS(startVertex, vertices);

    return 0;
}
