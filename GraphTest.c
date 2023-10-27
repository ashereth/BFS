#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {
    // Create a new graph with a specified number of vertices
    Graph G = newGraph(7);
    List L = newList();
    List path = newList();
    printf("Number of vertices = %d\n", getOrder(G));
    printf("Number of edges = %d\n", getSize(G));
    printf("Source = %d\n", getSource(G));
    getPath(L, G, 6);//this should print the getPath error message
    addEdge(G, 1, 4);
    addEdge(G, 1, 5);
    addEdge(G, 4, 5);
    addEdge(G, 2, 3);
    addEdge(G, 2, 6);
    addEdge(G, 3, 7);
    addEdge(G, 6, 7);
    printf("Number of edges = %d\n", getSize(G));
    printGraph(stdout, G);

    BFS(G, 2);
    printf("\nSource = %d\n", getSource(G));
    printf("\ndistance between %d and %d is: %d\n", 7, 2, getDist(G, 7));
    getPath(path, G, 7);
    printf("path from 3 to %d is: ", 7);
    printList(stdout, path);
    clear(path);
    BFS(G, 3);
    printf("\nSource = %d\n", getSource(G));
    printf("\ndistance between %d and %d is: %d\n", 6, 3, getDist(G, 6));
    getPath(path, G, 6);
    printf("path from 3 to %d is: ", 6);
    printList(stdout, path);
    clear(path);
    BFS(G, 1);
    printf("\nSource = %d\n", getSource(G));
    printf("\ndistance between %d and %d is: %d\n", 7, 1, getDist(G, 7));
    getPath(path, G, 7);
    printf("path from 3 to %d is: ", 7);
    printList(stdout, path);
    
    freeList(&L);
    freeList(&path);
    freeGraph(&G);
    return 0;
}
