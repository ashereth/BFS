#include "List.h"

/*** type definitions ***/
typedef struct GraphObj* Graph;
#define INF -1
#define NIL 0

/*** Constructors-Destructors ***/
//create a new graph and allocate memory for everything needed
Graph newGraph(int n);
//free all memory associated with give graph pointer
void freeGraph(Graph* pG);
/*** Access functions ***/
//returns the order of the graph
int getOrder(Graph G);
//returns the number of edges in the graph
int getSize(Graph G);
//returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G);
//return the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() has not yet been called
//pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u);
//returns the distance between the source and the given vertex or INF if BFS has not been called
//pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u);
//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
//pre: getSource(G) != NIL, 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
//deletes all edges of G returning it to its original state
void makeNull(Graph G);
//adds an edge from u to v and from v to u all edges must be kept in sorted increasing order
void addEdge(Graph G, int u, int v);
//adds an edge from u to v all edges must be kept in sorted increasing order
void addArc(Graph G, int u, int v);
//runs the breadth first search algorithm on G given the source s
void BFS(Graph G, int s);
/*** Other operations ***/
//prints the vertices and edges to the given file
void printGraph(FILE* out, Graph G);
