#include "graph_traversals.h"
#include "dsu.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct KruskalEdge {
    int src;
    int dest;
    int weight;
} KruskalEdge;

static int compare_edges(const void* a, const void* b) {
    return ((KruskalEdge*)a)->weight - ((KruskalEdge*)b)->weight;
}

int kruskal_mst(weightedGraph* graph) {
    if (graph == NULL || graph->V == 0) return 0;

    int V = graph->V;
    int E = 0;

    // Count edges
    for (int i = 0; i < V; i++) {
        Edge* curr = graph->array[i];
        while (curr) {
            E++;
            curr = curr->next;
        }
    }

    if (E == 0) {
        printf("The graph has no edges.\n");
        return 0;
    }

    KruskalEdge* edges = (KruskalEdge*)malloc(E * sizeof(KruskalEdge));
    if (!edges) return 0;

    int edge_idx = 0;
    for (int i = 0; i < V; i++) {
        Edge* curr = graph->array[i];
        while (curr) {
            edges[edge_idx].src = i;
            edges[edge_idx].dest = curr->destination;
            edges[edge_idx].weight = curr->weight;
            edge_idx++;
            curr = curr->next;
        }
    }

    // Sort edges by weight
    qsort(edges, E, sizeof(KruskalEdge), compare_edges);

    DSU* dsu = create_dsu(V);
    if (!dsu) {
        free(edges);
        return 0;
    }

    printf("Edges in the Minimum Spanning Tree (Kruskal's Algorithm):\n");
    printf("Source -- Destination == Weight\n");

    int mst_weight = 0;
    int edges_count = 0;

    for (int i = 0; i < E && edges_count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (find_dsu(dsu, u) != find_dsu(dsu, v)) {
            union_dsu(dsu, u, v);
            printf("%d -- %d == %d\n", u, v, edges[i].weight);
            mst_weight += edges[i].weight;
            edges_count++;
        }
    }

    if (edges_count < V - 1) {
        printf("Warning: The graph is disconnected. The MST shown is actually a Minimum Spanning Forest.\n");
    }

    printf("Total Weight of MST: %d\n", mst_weight);

    free_dsu(dsu);
    free(edges);

    return mst_weight;
}

void kruskal_demo(void) {
    int V, E;
    printf("\n--- Kruskal's MST Demo ---\n");
    if (safe_input_int(&V, "Enter number of vertices: ", 1, 1000) != 0) return;
    if (safe_input_int(&E, "Enter number of edges: ", 0, 10000) != 0) return;

    weightedGraph* graph = create_weightedGraph(V);
    if (!graph) return;

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        printf("Edge %d:\n", i + 1);
        if (safe_input_int(&u, "  Source: ", 0, V - 1) != 0) break;
        if (safe_input_int(&v, "  Destination: ", 0, V - 1) != 0) break;
        if (safe_input_int(&w, "  Weight: ", 0, 10000) != 0) break;
        
        add_edge_directed(graph, u, v, w);
        add_edge_directed(graph, v, u, w);
    }

    kruskal_mst(graph);
    free_weightedGraph(graph);
}
