#ifndef graph_h
#define graph_h

typedef struct Edge Edge;
typedef struct Node Node;
typedef struct Graph Graph;

typedef struct Edge {
    float weight;
    int idnum;
    int src, dest;
    struct Edge *next;
} Edge;
typedef struct Node {
    int id;
    Edge* edges;  //Keeps only the edges going out of the node
    struct Node *next, *prev;
} Node;
typedef struct Graph {
    int size;
    int edgesize;
    Node* current;
    Edge* edges;
} Graph;

Graph* init_graph();
Node* init_node(int id);
Edge* init_edge(int src, int dest, int weight, int idnum);
void add_node(Graph* g,Node* node);
void remove_node(Graph* g,int id);
void remove_node_out_edges(Graph* g, int id);
Node* get_node(Graph* g,int id);
Edge* get_edge(Graph* g, int src, int dest);
void remove_edge(Graph* g, int edge_id);
void add_edge(Graph* g, Edge* edge);
void connect(Graph* g, int src, int dest, int weight, int idnum);
void print_graph(Graph* g);
void free_graph(Graph* g);
int shortestPath(Graph* g, int src, int dest);
int TSP(Graph* g, Node* currenttsp, int size);

#endif
