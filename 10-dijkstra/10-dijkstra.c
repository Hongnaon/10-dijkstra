#include <stdio.h>
#include <limits.h>

#define V 10  // ������ ����
#define INF INT_MAX  // ���Ѵ� ��

// �׷��� ����ü ����
typedef struct {
    int num_vertices;         // ���� ��
    int adj_matrix[V][V];     // ������ ����ġ ���
} Graph;

// �׷��� �ʱ�ȭ �Լ�
void InitializeGraph(Graph* graph) {
    graph->num_vertices = 10;

    int edges[10][10] = {
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF },
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF },
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF },
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 },
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 },
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF },
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF },
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 },
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 },
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }
    };

    // ����ġ ��Ŀ� ����
    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = 0; j < graph->num_vertices; j++) {
            graph->adj_matrix[i][j] = edges[i][j];
        }
    }
}

// ���ͽ�Ʈ�� �˰��� ����
void Dijkstra(Graph* graph, int start_vertex) {
    int dist[V];  // �ִ� �Ÿ� �迭
    int visited[V];   // �湮 ���� �迭
    int visit_order[V];  // �湮 ����
    int order_index = 0;  // �湮 ���� �ε���

    // �ʱ�ȭ
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        visit_order[i] = -1;
    }

    dist[start_vertex] = 0;

    // �ʱ� ���� ���
    printf("distance:  ");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("* ");
        }
        else {
            printf("%2d ", dist[i]);
        }
    }
    printf("\n");

    printf("found:     ");
    for (int i = 0; i < V; i++) {
        printf(i == start_vertex ? "1 " : "0 ");
    }
    printf("\n\n");

    // �˰��� ����
    for (int step = 0; step < V; step++) {
        int min = INF, u = -1;

        // �ּ� �Ÿ��� ���� ã��
        for (int j = 0; j < V; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break;  // ó���� ������ ������ ����

        visited[u] = 1;
        visit_order[order_index++] = u + 1;

        // �Ÿ� ������Ʈ
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph->adj_matrix[u][v] != INF &&
                dist[u] + graph->adj_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adj_matrix[u][v];
            }
        }

        // �Ÿ� ���
        printf("distance:  ");
        for (int i = 0; i < V; i++) {
            printf(dist[i] == INF ? "* " : "%2d ", dist[i]);
        }
        printf("\n");

        // �湮 ���� ���
        printf("found:     ");
        for (int i = 0; i < V; i++) {
            printf("%d ", visited[i]);
        }
        printf("\n\n");
    }

    // �湮 ���� ���
    printf("Found Order: ");
    for (int i = 0; i < order_index; i++) {
        printf("%d ", visit_order[i]);
    }
    printf("\n");
}

int main() {
    Graph g;
    InitializeGraph(&g);  // �׷��� �ʱ�ȭ

    Dijkstra(&g, 0);  // 0�� �������� ���ͽ�Ʈ�� ����

    return 0;
}
