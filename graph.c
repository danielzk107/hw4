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
Edge* init_edge(int src, int dest, float weight){
    Edge* edge = malloc(sizeof(Edge));
    if(!edge){
        printf("Unexpected problem occured whilst allocating edge\n");
        return NULL;
    }
    edge -> src = src;
    edge -> dest = dest;
    edge -> weight = weight;
    edge -> next = NULL;
    return edge;
}
void add_node(Graph* g, Node* node){
    Node* temp = g -> current;
    if(g == NULL){
        printf("The given graph does not exist\n");
        return;
    }
    printf("Adding node number %d\n", node -> id);
    if(g -> current != NULL){
        while(g -> current -> next != NULL){
            // printf("AAAAAA %d\n", g -> current ->id);
            g -> current = g -> current -> next;
        }
        g -> current -> next = node;
        g -> current = temp;
    }
    else{
        g -> current = node;
    }
    
}
Node* remove_node(Graph* g, int id){
    Node* temp = g -> current;
    Node* output;
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return NULL;
    }
    while(g -> current -> id < id-1 && g -> current != NULL){
        g -> current = g -> current -> next;
    }
    if(g -> current -> id < id-1 || g -> current == NULL){
        printf("The given node is not in the graph\n");
        return NULL;
    }
    output = g -> current -> next;
    g -> current -> next = g ->current -> next -> next;
    g -> current = temp;
    return output;
}
Node* get_node(Graph* g, int id){
    Node* temp = g -> current;
    Node* output;
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return NULL;
    }
    while(g -> current -> id < id && g -> current != NULL){
        g -> current = g -> current -> next;
    }
    if(g -> current -> id < id){
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
        printf("The source node has no connected edges\n");
        return NULL;
    }
    Edge* temp = srcnode -> edges;
    Edge* output;
    while(srcnode -> edges != NULL && srcnode -> edges -> dest != dest){
        srcnode -> edges = srcnode -> edges -> next;
    }
    if(srcnode -> edges == NULL){
        printf("The source node is not connected to the destination node\n");
        return NULL;
    }
    output = srcnode -> edges;
    srcnode -> edges = temp;
    return output;
}
void add_edge(Graph* g, Edge* edge){//Commented out the lines which add the edges to their respective nodes 
    if(g == NULL || g -> current == NULL){
        printf("The given graph does not exist or is empty\n");
        return;
    }
    // Node* srcnode = get_node(g, edge -> src);
    // Node* destnode = get_node(g, edge -> dest);
    // Edge* srctemp = srcnode -> edges;
    // Edge* desttemp = destnode -> edges;
    Edge* graphtemp = g -> edges;
    // if(srctemp == NULL){
    //     srcnode -> edges = edge;
    // }
    // else{
    //     while(srcnode -> edges -> next != NULL){
    //         srcnode -> edges = srcnode -> edges -> next; 
    //     }
    //     srcnode -> edges -> next = edge;
    //     srcnode -> edges = srctemp;
    // }
    // if(desttemp == NULL){
    //     destnode -> edges = edge;
    // }
    // else{
    //     while(destnode -> edges -> next != NULL){
    //         destnode -> edges = destnode -> edges -> next; 
    //     }
    //     destnode -> edges -> next = edge;
    //     destnode -> edges = desttemp;
    // }
    if(graphtemp == NULL){
        g -> edges = edge;
    }
    else{
        while(g -> edges -> next != NULL){
            g -> edges = g -> edges -> next;
        }
        g -> edges -> next = edge;
        g -> edges = graphtemp;
    }
}
void connect(Graph* g, int src, int dest, float weight){
    Node* srcnode = get_node(g, src);
    Node* destnode = get_node(g, dest);
    Edge* edge = init_edge(src, dest, weight);
    Edge* srctemp = srcnode -> edges;
    Edge* desttemp = destnode -> edges;
    Edge* graphtemp = g -> edges;
    if(srctemp == NULL){
        srcnode -> edges = edge;
    }
    else{
        while(srcnode -> edges -> next != NULL){
            srcnode -> edges = srcnode -> edges -> next; 
        }
        srcnode -> edges -> next = edge;
        srcnode -> edges = srctemp;
    }
    if(desttemp == NULL){
        destnode -> edges = edge;
    }
    else{
        while(destnode -> edges -> next != NULL){
            destnode -> edges = destnode -> edges -> next; 
        }
        destnode -> edges -> next = edge;
        destnode -> edges = desttemp;
    }
    if(graphtemp == NULL){
        g -> edges = edge;
    }
    else{
        while(g -> edges -> next != NULL){
            g -> edges = g -> edges -> next;
        }
        g -> edges -> next = edge;
        g -> edges = graphtemp;
    }
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
    }
    g -> current = tempnode;
    printf("Edges:\n");
    Edge* tempedge = g -> edges;
    while(g -> edges != NULL){
        printf("From %d to %d with weight of %f\n", g -> edges -> src, g -> edges -> dest, g -> edges -> weight);
    }
    g -> edges = tempedge;
}
void free_graph(Graph* g){
    while(g -> current != NULL){
        Node* temp = g -> current -> next;
        free(g -> current);
        g -> current = temp;
    }
    while(g -> edges != NULL){
        Edge* temp = g -> edges -> next;
        free(g -> edges);
        g -> edges = temp;
    }
    free(g);
}

