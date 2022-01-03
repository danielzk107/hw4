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
        getchar();//To get rid of the space
        printf("%c\n", c);
        if(c == 'A' || c == 'a'){
            //Create graph:
            mygraph = init_graph();
            c = getchar();
            // printf("Size = %d\n", atoi(&c));
            int size = atoi(&c);
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
                Node* n = init_node(atoi(&c));
                add_node(mygraph, n);
                getchar();
                char src = getchar();
                if(!isdigit(src)){
                    printf("Finished initiating graph\n");
                    break;
                }
                printf("%c\n", c);
                //Placeholder:
                getchar();
                char dest = getchar();
                printf("%c\n", dest);

                getchar();
                char wtens = getchar();
                printf("%c\n", wtens);

                getchar();
                char wones = getchar();
                printf("%c\n", wones);
                Edge* edge = init_edge(src, dest, (atoi(&wtens)*10 + atoi(&wones)));
                add_edge(mygraph, edge);
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

        }
        if(c == 'P' || c == 'p'){
            //Print graph:
            print_graph(mygraph);
        }
    }
    free_graph(mygraph);
}