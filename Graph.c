#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"

/*** type definitions ***/
#define WHITE 2
#define GRAY 1
#define BLACK 0

typedef struct GraphObj{
    int order;//define the number of vertices of the graph
    int size;//define the number of edges
    int source;//define the source of the graph
    List* AdjList;//create an array of Lists for the Adjacency List
    int* parent; //array to store the parents/predecessors for every vertex
    int* distance;//array to store distance to each vertex from given source
    int* colors;//array to keep track of which vertices have been discovered
}GraphObj;

/*** Constructors-Destructors ***/
//create a new graph with n vertices
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj));
    assert(G!=NULL);
    G->order = n;//set the number of vertices
    G->size = 0;//set number of edges to 0 initially
    G->source = NIL;//set source to invalid initially
    //allocate memory for all needed arrays
    G->parent = (int*)malloc((n + 1) * sizeof(int));
    G->distance = (int*)malloc((n + 1) * sizeof(int));
    G->AdjList = (List*)malloc((n + 1) * sizeof(List));
    G->colors = (int*)(malloc((n+1) * sizeof(int)));
    //set all needed values in the arrays
    for (int i = 1; i <= n; i++) {//make sure to create enough room in arrays to be able to index all the way to n
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->colors[i] = WHITE;
        G->AdjList[i] = newList(); // Create a new List for each vertex
    }
    return G;
}

//free all memory associated with a graph pointer
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;

        // Free memory for the adjacency lists and their elements
        for (int i = 1; i <= G->order; i++) {
            freeList(&(G->AdjList[i]));
        }

        // Free other dynamically allocated arrays
        free(G->parent);
        free(G->distance);
        free(G->colors);
        free(G->AdjList);

        //free the Graph object itself
        free(G);

        // Set the pointer to NULL
        *pG = NULL;
    }
}
/*** Access functions ***/

//returns the number of Vertices in the graph
int getOrder(Graph G){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get Graph Order.\n");
        return -1;
    }
    return G->order;
}

//returns the number of edges in the graph
int getSize(Graph G){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get Graph Size.\n");
        return -1;
    }
    return G->size;
}

//return the most recent valid source vertex or return NIL/0 if the source hasnt been set
int getSource(Graph G){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get Source of graph.\n");
        return -1;
    }
    return G->source;
}

//get the parent of the given vertecy if it has been set
int getParent(Graph G, int u){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get parent of vertex %d.\n", u);
        return -1;
    }else if(u<1 || u>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Graph Error: cannot get parent because given vertex is out of bounds.\n");
        return -1;
    }
    //if parent hasn't been set for the given vertex then it will return NIL/0
    return G->parent[u];
}

//return the distance between the last used source and the given vertex
int getDist(Graph G, int u){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get parent of vertex %d.\n", u);
        return -1;
    }else if(u<1 || u>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Graph Error: cannot get distance because given vertex is out of bounds.\n");
        return -1;
    }
    //if parent hasn't been set for the given vertex then it will return INF/-1
    return G->distance[u];
}

//adds the path from source to vertex u into the List L
void getPath(List L, Graph G, int u){
    if(getSource(G)==NIL || L==NULL || G == NULL){//print error if source is undefined
        fprintf(stderr, "Path Error: cannot get path because BFS has not yet been called.\n");
        return;
    }else if(u<1 || u>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Path Error: cannot get path because given vertex is out of bounds.\n");
        return;
    }else{
        append(L, u);
        int p = G->parent[u];
        while(p!=NIL){
            prepend(L, p);
            p = G->parent[p];
        }
    }
}
/*** Manipulation procedures ***/
//deletes all edges from the graph
void makeNull(Graph G){
    if (G==NULL){
        fprintf(stderr, "Graph Error: Unable to delete edges because graph doesn't exist.\n");
        return;
    }else{
        for (int i = 1; i <= getOrder(G); i++) {//make sure to create enough room in arrays to be able to index all the way to n
            //free the original edge list and then reset it
            freeList(&G->AdjList[i]);
            G->AdjList[i] = newList(); // Create a new List for each vertex
        }
    }
}

//add an edge v to the adjacency list of u and visca versa
void addEdge(Graph G, int u, int v){
    if (G==NULL){
        fprintf(stderr, "Graph Error: Unable to add edge because graph doesn't exist.\n");
        return;
    }else if(u<1 || u>G->order || v<1 || v>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Path Error: cannot add edge because given vertex is out of bounds.\n");
        return;
    }
    //increment the size of the graph
    G->size++;
    //add u to adjlist v
    List Lv = G->AdjList[v];
    int added = 0;//keep track if edge has been added
    if(length(Lv)==0){//if list is empty just insert u
        append(Lv, u);
    }else{
        moveFront(Lv);
        //while u>curser element and curser isnt at the end
        while(u>get(Lv)){
            //if we are at the end of the List append to the end
            if(index(Lv)==length(Lv)-1){
                append(Lv, u);
                added++;
            }
            moveNext(Lv);
        }
        //once u is less than curser element add u before curser
        if(added==0){
            insertBefore(Lv, u);
            added+=1;
        }
        
    }
    //add v to adjlist u
    List Lu = G->AdjList[u];
    added = 0;
    if(length(Lu)==0){//if list is empty just insert u
        append(Lu, v);
    }else{
        moveFront(Lu);
        //while u>curser element and curser isnt at the end
        while(v>get(Lu)){
            //if we are at the end of the List append to the end
            if(index(Lu)==length(Lu)-1){
                append(Lu, v);
                added++;
            }
            moveNext(Lu);
        }
        //once u is less than curser element add u before curser
        if(added==0){
            insertBefore(Lu, v);
            added+=1;
        }
        
        return;
    }
}

//add a directed edge from u to v
void addArc(Graph G, int u, int v){
    if (G==NULL){
        fprintf(stderr, "Graph Error: Unable to add edge because graph doesn't exist.\n");
        return;
    }else if(u<1 || u>G->order || v<1 || v>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Path Error: cannot add edge because given vertex is out of bounds.\n");
        return;
    }
    //increment the size of the graph
    G->size++;
    //add v to adjlist of u
    List Lu = G->AdjList[u];
    if(length(Lu)==0){//if list is empty just insert u
        append(Lu, v);
    }else{
        moveFront(Lu);
        //while u>curser element and curser isnt at the end
        while(v>get(Lu)){
            //if we are at the end of the List append to the end
            if(index(Lu)==length(Lu)-1){
                append(Lu, v);
                return;
            }
            moveNext(Lu);
        }
        //once u is less than curser element add u before curser
        insertBefore(Lu, v);
        return;
    }
}

//implimentation of BFS on graph G given source s
void BFS(Graph G, int s){
    //set source of G to s
    G->source = s;

    //for x in all edges
    for(int x = 1; x<=G->order; x++){
        //exclude source
        if(x!=s){
            G->colors[x] = WHITE;
            G->distance[x] = INF;
            G->parent[x] = NIL;
        }
    }
    G->colors[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    //make a List to be used as a queue
    List Q = newList();
    append(Q, s);
    while(length(Q)!=0){
        //dequeue using list Q
        int x = front(Q);
        deleteFront(Q);
        //loop through all edges of x
        moveFront(G->AdjList[x]);
        for (int i = 0; i<length(G->AdjList[x]); i++){
            
            int y = get(G->AdjList[x]);//set y
            if(G->colors[y]==WHITE){
                G->colors[y] = GRAY;
                G->distance[y] = G->distance[x]+1;
                G->parent[y] = x;
                //enqueue y into Q
                append(Q, y);
            }
            //increment to next edge
            moveNext(G->AdjList[x]);
        }
        G->colors[x] = BLACK;
    }
    freeList(&Q);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if (out == NULL || G == NULL) {
        fprintf(stderr, "Error: Invalid file pointer or NULL list reference\n");
        return;
    }
    for (int i = 1; i<=getOrder(G); i++){
        fprintf(out, "%d: ", i);//print out each vertex
        printList(out, G->AdjList[i]);//then print out each edge of that vertex
        if(i<getOrder(G)){
            fprintf(out, "\n");
        }
    }
}
