#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"

void print_node(Graph* g, Node* n){
    Edge* edges_temp = n -> edges;
    printf("Node number %d:\n", n -> id);
    while(n -> edges != NULL){
        printf("Edge from %d to %d\n", n -> edges -> src, n -> edges -> dest);
        n -> edges = n -> edges -> next;
    }
    n -> edges = edges_temp;
}

int main(){
    char c;
    printf("Please select an activity\n");
    Graph* mygraph;
    while(c != 'X' && c != 'x'){
        c = getchar();
        // printf("%c\n", c);
        if(c == 'A' || c == 'a'){
            getchar();//To get rid of the space
            //Create graph:
            mygraph = init_graph();
            c = getchar();
            int size = c - 48;  //each time we are getting a digit from the user, we subtract 48 from the value of the character to get the actual int value of the digit
            for(int i = 0; i< size; i++){
                getchar();
                c = getchar();
                if(c != 'n'){
                    printf("Invalid formatting, missing the letter 'n'\ngot %c instead (at round number %d)\n", c, i);
                    return -1;
                }
                getchar();
                memset(&c, 0, sizeof(c));
                c = getchar();
                Node* n = init_node(c - 48);
                add_node(mygraph, n);  
                getchar();
                c = getchar();
                if(isdigit(c)){    
                    getchar();
                    char weight = getchar();
                    connect(mygraph, n -> id, c - 48, weight - 48, mygraph -> edgesize);
                    getchar();
                    char dest2 = getchar();
                    if(isdigit(dest2)){
                        getchar();
                        char weight  = getchar();
                        connect(mygraph, n -> id, dest2 - 48, weight - 48, mygraph -> edgesize);
                    }
                }
            }
        }
        // Doesnt fully work properly
        if (c == 'B' || c == 'b'){
            //Add new node:
            getchar();
            char nodeid = getchar();
            Node* node;
            //Check if the node already exists:
            if(get_node(mygraph, nodeid - 48) != NULL){
                // print_graph(mygraph);
                node = get_node(mygraph, nodeid - 48);
                remove_node_out_edges(mygraph, nodeid);
            }
            else{
                // printf("Initiating new node\n");
                node = init_node(nodeid - 48);
                // print_graph(mygraph);
                add_node(mygraph, node);
                // print_graph(mygraph);
            }
            getchar();
            c = getchar();
            if(isdigit(c)){
                getchar();
                char weight = getchar();
                connect(mygraph, node -> id, c - 48, weight - 48, mygraph -> edgesize);
                // print_graph(mygraph);
                getchar();
                char dest2 = getchar();
                if(isdigit(dest2)){
                    getchar();
                    char weight  = getchar();
                    connect(mygraph, node -> id, dest2 - 48, weight - 48, mygraph -> edgesize);
                }
            }
            // print_graph(mygraph);
        }
        if(c == 'D' || c == 'd'){
            //Remove node:
            getchar();
            c = getchar();
            remove_node(mygraph, c - 48);
        }
        if(c == 'S' || c == 's'){
            //Get shortest path:
            getchar();
            char src = getchar();
            getchar();
            char dest = getchar();
            printf("Dijsktra shortest path: %d\n", shortestPath(mygraph, src - 48, dest - 48));
        }
        if(c == 'T' || c == 't'){
            //Get TSP:
            getchar();
            char size = getchar();
            if(size - 48 <= 0){
                printf("Incorrect size entered\n");
                break;
            }
            getchar();
            Node* list = get_node(mygraph, getchar() - 48);
            Node* temp = list;
            for(int i = 1; i < size - 48; i++){
                getchar();
                list -> next = get_node(mygraph, getchar() - 48);
                list = list -> next; 
            }
            list = temp;
            printf("TSP shortest path: %d\n", TSP(mygraph, temp, size - 48));
        }
        if(c == 'P' || c == 'p'){
            //Print graph:
            print_graph(mygraph);
            // getchar();
            // char nodeid = getchar();
            // print_node(mygraph, get_node(mygraph, nodeid - 48));
        }
    }
    if(mygraph != NULL){
        free_graph(mygraph);
    }
}