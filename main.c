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
                print_graph(mygraph);
                node = get_node(mygraph, nodeid - 48);
                Edge* new_edge_list;
                while(mygraph -> edges != NULL && mygraph -> edges -> src == node -> id){  //Delete all of the existing node's (entering) edges
                    Edge* e = mygraph -> edges -> next;
                    print_graph(mygraph);
                    free(mygraph -> edges);
                    mygraph -> edges = NULL;
                    mygraph -> edges = e;
                }
                new_edge_list = mygraph -> edges;
                Edge* new_edge_list_temp = mygraph -> edges;
                if(mygraph -> edges !=NULL){
                    mygraph -> edges = mygraph -> edges -> next;
                }
                while(mygraph -> edges != NULL){
                    print_graph(mygraph);
                    if(mygraph -> edges -> src == node -> id){
                        Edge* e = mygraph -> edges -> next;
                        free(mygraph -> edges);
                        mygraph -> edges = NULL;
                        mygraph -> edges = e;
                    }
                    else{
                        new_edge_list -> next = mygraph -> edges;
                        new_edge_list -> next -> next = NULL;
                        mygraph -> edges = mygraph -> edges -> next;
                        new_edge_list = new_edge_list -> next;
                    }
                }
                print_graph(mygraph);
                mygraph -> edges = new_edge_list_temp;
                print_graph(mygraph);
            }
            else{
                printf("Initiating new node\n");
                node = init_node(nodeid - 48);
                print_graph(mygraph);
                add_node(mygraph, node);
                print_graph(mygraph);
            }
            getchar();
            c = getchar();
            if(isdigit(c)){
                getchar();
                char weight = getchar();
                connect(mygraph, node -> id, c - 48, weight - 48, mygraph -> edgesize);
                print_graph(mygraph);
                getchar();
                char dest2 = getchar();
                if(isdigit(dest2)){
                    getchar();
                    char weight  = getchar();
                    connect(mygraph, node -> id, dest2 - 48, weight - 48, mygraph -> edgesize);
                }
            }
            print_graph(mygraph);
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
            printf("Dijsktra shortest path: %f\n", shortestPath(mygraph, src - 48, dest - 48));
        }
        if(c == 'T' || c == 't'){
            //Get TSP:
            printf("TSP shortest path: \n");

        }
        if(c == 'P' || c == 'p'){
            //Print graph:
            // print_graph(mygraph);
            getchar();
            char nodeid = getchar();
            print_node(mygraph, get_node(mygraph, nodeid - 48));
        }
    }
    if(mygraph != NULL){
        free_graph(mygraph);
    }
}