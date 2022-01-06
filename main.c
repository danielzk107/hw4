#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"



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
            // printf("Size = %d\n", atoi(&c));
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
                printf("Initating node number %c\n",c);
                Node* n = init_node(c - 48);
                add_node(mygraph, n);  
                printf("Added node number %d\n", c - 48);
                getchar();
                char dest1 = getchar();
                if(isdigit(dest1)){    
                    getchar();
                    char weight = getchar();
                    connect(mygraph, n -> id, dest1, weight, mygraph -> edgesize);
                    printf("Connected first edge\n");
                }
                getchar();
                char dest2 = getchar();
                if(isdigit(dest2)){
                    getchar();
                    char weight  = getchar();
                    connect(mygraph, n -> id, dest2, weight, mygraph -> edgesize);
                    printf("Connected second edge\n");
                }
            }
        }
        if (c == 'B' || c == 'b'){
            //Add new node:

        }
        if(c == 'D' || c == 'd'){
            //Remove node:

        }
        if(c == 'S' || c == 's'){
            //Get shortest path:

        }
        if(c == 'T' || c == 't'){
            //Get TSP:
            printf("TSP function\n");

        }
        if(c == 'P' || c == 'p'){
            //Print graph:
            print_graph(mygraph);
        }
    }
    free_graph(mygraph);
}