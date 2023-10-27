#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char * argv[]){
    // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }
    //open infile for reading
    FILE *infile = fopen(argv[1], "r");
    //open outfile for writing
    FILE *outfile = fopen(argv[2], "w");
    char line[100];
    int size;

    //get the size of the graph from the first line
    if (fgets(line, sizeof(line), infile) != NULL) {
        // Use atoi to convert the line to an integer
        size = atoi(line);
    }else {
        // Handle the case where the file is empty or the first line is not an integer
        printf("Unable to read a size from the file.\n");
        fclose(infile);
        fclose(outfile);
        return 0;
    }
    //initialize the graph after getting the size from the first line
    Graph G = newGraph(size);
    //read all edges and populate graphs edges
    int num1, num2;
    while (fscanf(infile, "%d %d", &num1, &num2) == 2) {
        //break once you get to 2 0s
        if (num1 == 0 && num2 ==0){
            break;
        }
        // Process num1 and num2
        addEdge(G, num1, num2);
    }
    printGraph(outfile, G);
    fprintf(outfile, "\n");
    //get needed paths
    List path = newList();
    while (fscanf(infile, "%d %d", &num1, &num2) == 2) {
        //break once you get to 2 0s
        if (num1 == 0 && num2 ==0){
            break;
        }
        BFS(G, num1);
        if (getDist(G, num2)>-1){
            fprintf(outfile, "\nThe distance from %d to %d is %d\n", num1, num2, getDist(G, num2));
            getPath(path, G, num2);
            fprintf(outfile, "A shortest %d-%d path is: ", num1, num2);
            printList(outfile, path);
            clear(path);
            fprintf(outfile, "\n");
        }else{
            fprintf(outfile, "\nThe distance from %d to %d is infinity\n", num1, num2);
            getPath(path, G, num2);
            fprintf(outfile, "No %d-%d path exists", num1, num2);
            clear(path);
            fprintf(outfile, "\n");
        }
        
    }
    //close files and free memory
    freeGraph(&G);
    freeList(&path);
    fclose(infile);
    fclose(outfile);
}