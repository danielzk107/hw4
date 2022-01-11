#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* init_graph(){
    Graph* g = malloc(sizeof(Graph));
    if(!g){
        printf("Unexpected problem occured whilst allocating graph\n");
        return NULL;
    }
    g -> size = 0;
    g -> current = NULL;
    g -> edges = NULL;
    g -> edgesize = 0;
    return g;
}
Node* init_node(int id){
    Node* node = malloc(sizeof(Node));
    if(!node){
        printf("Unexpected problem occured whilst allocating node\n");
        return NULL;
    }
    node -> id = id;
    node -> edges = NULL;
    node -> next = NULL;
    return node;
}
Edge* init_edge(int src, int dest, float weight, int idnum){
    Edge* edge = malloc(sizeof(Edge));
    if(!edge){
        printf("Unexpected problem occured whilst allocating edge\n");
        return NULL;
    }
    edge -> src = src;
    edge -> dest = dest;
    edge -> weight = weight;
    edge -> idnum = idnum;
    edge -> next = NULL;
    return edge;
}
void add_node(Graph* g, Node* node){
    Node* temp = g -> current;
    if(g == NULL){
        printf("The given graph does not exist\n");
        return;
    }
    if(g -> current != NULL){
        while(g -> current -> next != NULL){
            g -> current = g -> current -> next;
        }
        g -> current -> next = node;
        g -> current = temp;
    }
    else{
        g -> current = node;
    }
    g -> size += 1;
}
void remove_node(Graph* g, int id){ //Doesnt remove edges from the graph yet
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return;
    }
    int removed = -1;
    if(g -> current -> id == id){
        Node* n = g -> current -> next;
        free(g -> current);
        g -> current = NULL;
        removed = 1;
        // printf("Removed node %d, current node is %d\n", id, n -> id);
        g -> current = n;
        if(n == NULL){
            return;
        }
    }
    Node* new_node_list = g -> current;
    g -> current = g -> current -> next;
    Node* new_node_list_temp = new_node_list;
    while(g -> current != NULL){
        if(g -> current -> id == id){
            Node* n = g -> current -> next;
            free(g -> current);
            g -> current = NULL;
            removed = 1;
            // printf("Removed node %d, current node is %d\n", id, n -> id);
            g -> current = n;
        }
        else{
            new_node_list -> next = g -> current;
            g -> current = g -> current -> next;
            new_node_list = new_node_list -> next;
        }
    }
    g -> current = new_node_list_temp;
    if(removed != 1){
        printf("The given node is not in the graph\n");
        return;
    }
    Edge* new_edge_list;
    while(g -> edges != NULL && (g -> edges -> src == id || g -> edges -> dest == id)){
        Edge* e = g -> edges -> next;
        free(g -> edges);
        g -> edges = NULL;
        g -> edges = e;
    }
    new_edge_list = g -> edges;
    Edge* new_edge_list_temp = g -> edges;
    if(g -> edges == NULL){
        return;
    }
    g -> edges = g -> edges -> next;
    while(g -> edges != NULL){
        if(g -> edges -> src == id || g -> edges -> dest == id){
            Edge* e = g -> edges -> next;
            // printf("%d\n", g -> edges -> idnum);
            free(g -> edges);
            g -> edges = NULL;
            g -> edges = e;
        }
        else{
                new_edge_list -> next = g -> edges;
                new_edge_list -> next -> next = NULL;
                g -> edges = g -> edges -> next;
                new_edge_list = new_edge_list -> next;
        }
    }
    g -> edges = new_edge_list_temp;
    g -> size -=1;
}
Node* get_node(Graph* g, int id){
    Node* temp = g -> current;
    Node* output;
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return NULL;
    }
    while(g -> current != NULL && g -> current -> id != id){
        g -> current = g -> current -> next;
    }
    if(g -> current != NULL && g -> current -> id != id){
        printf("The given node is not in the graph\n");
        return NULL;
    }
    output = g -> current;
    g -> current = temp;
    return output;
}
Edge* get_edge(Graph* g, int src, int dest){
    Node* srcnode = get_node(g, src);
    if(srcnode -> edges == NULL){
        // printf("The source node has no connected edges\n");
        return NULL;
    }
    Edge* temp = srcnode -> edges;
    Edge* output;
    while(srcnode -> edges != NULL && srcnode -> edges -> dest != dest){
        srcnode -> edges = srcnode -> edges -> next;
    }
    if(srcnode -> edges == NULL){
        // printf("The source node is not connected to the destination node\n");
        return NULL;
    }
    output = srcnode -> edges;
    srcnode -> edges = temp;
    return output;
}
void add_edge(Graph* g, Edge* edge){
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return;
    }
    Node* srcnode = get_node(g, edge -> src);
    Edge* srctemp = srcnode -> edges;
    Edge* graphtemp = g -> edges;
    if(srctemp == NULL){
        srcnode -> edges = edge;
        srcnode -> edges -> next = NULL;
    }
    else{
        while(srcnode -> edges -> next != NULL){
            srcnode -> edges = srcnode -> edges -> next;
        }
        srcnode -> edges -> next = edge;
        // printf("Added edge %d to node %d\n", edge -> idnum, srcnode -> id);
        srcnode -> edges -> next -> next = NULL;
        srcnode -> edges = srctemp;        
    }
    if(graphtemp == NULL){
        g -> edges = edge;
    }
    else{
        int errorcounter = 0;
        while(g -> edges -> next != NULL && errorcounter < (g -> edgesize)*2){
            g -> edges = g -> edges -> next;
            errorcounter++;
        }
        if(errorcounter >= (g -> edgesize)*2){
            printf("There has been a problem while cycling through the edges in the graph.\n");
        }
        g -> edges -> next = edge;
        g -> edges -> next -> next = NULL;
        g -> edges = graphtemp;
    }
    g -> edgesize += 1;
}
void connect(Graph* g, int src, int dest, float weight, int idnum){
    Edge* edge = init_edge(src, dest, weight, idnum);
    add_edge(g, edge);
}
void print_graph(Graph* g){
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return;
    }
    printf("Nodes:\n");
    Node* tempnode = g -> current;
    while(g -> current != NULL){
        printf("  %d  ", g -> current -> id);
        g -> current = g -> current -> next;
    }
    printf("\n");
    g -> current = tempnode;
    printf("Edges:\n");
    Edge* tempedge = g -> edges;
    while(g -> edges != NULL){
        printf("From %d to %d with weight of %f\n", g -> edges -> src, g -> edges -> dest, g -> edges -> weight);
        if(g -> edges -> next != NULL && g -> edges -> idnum == g -> edges -> next -> idnum){
            return;
        }
        g -> edges = g -> edges -> next;
    }
    g -> edges = tempedge;
}
void remove_edge(Graph* g, int edge_id){
    int removed = -1;
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return;
    }
    if(g -> edges -> idnum == edge_id){
        // printf("AAAAA\n");
        Edge* e = g -> edges -> next;
        free(g -> edges);
        // printf("BBBBBBBBB\n");
        g -> edges = NULL;
        removed = 1;
        // printf("Removed edge %d, current edge is %d\n", edge_id, e -> idnum);
        g -> edges = e;
        if(e == NULL){
            return;
        }
    }
    Edge* new_edge_list = g -> edges;
    g -> edges = g -> edges -> next;
    Edge* new_edge_list_temp = new_edge_list;
    while(g -> edges != NULL){
        if(g -> edges -> idnum == edge_id){
            Edge* e = g -> edges -> next;
            free(g -> edges);
            g -> edges = NULL;
            removed = 1;
            // printf("Removed edge %d, current edge is %d\n", edge_id, e -> idnum);
            g -> edges = e;
        }
        else{
            new_edge_list -> next = g -> edges;
            g -> edges = g -> edges -> next;
            new_edge_list = new_edge_list -> next;
        }
    }
    if(removed == -1){
        printf("edge %d not found\n", edge_id);
    }
    g -> edges = new_edge_list_temp;
}
void free_graph(Graph* g){
    while(g -> current != NULL){
        Node* temp = g -> current -> next;
        free(g -> current);
        g -> current = NULL;
        g -> current = temp;
    }
    while(g -> edges != NULL){
        Edge* temp = g -> edges -> next;
        free(g -> edges);
        g -> edges = NULL;
        g -> edges = temp;
    }
    free(g);
}
float shortestPath(Graph* g, int src, int dest){
    //Floyd-Warshall (might not be as efficient as Dijkstra's, but it more convinient)
    float distances[g -> size][g -> size];
    for(int i=0; i< g -> size; i++){
        for (int j = 0; j < g -> size; j++)
        {
            Edge* edge = get_edge(g, i, j);
            if(edge == NULL){
                distances[i][j] = __INT_MAX__/2;
            }
            else{
                distances[i][j] = edge -> weight;
            }
        }
    }
    for (int i = 0; i < g -> size; i++)
    {
        for (int j = 0; j < g -> size; j++)
        {
            for (int k = 0; k < g -> size; k++)
            {
                if(distances[j][i] + distances[i][k] < distances[j][k]){
                    distances[j][k] = distances[j][i] + distances[i][k];
                }
            }
        }
    }
    if(distances[src][dest] >= __INT_MAX__/2){
        return -1;
    }
    return distances[src][dest];
}
