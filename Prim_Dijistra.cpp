#include <bits/stdc++.h>
using namespace std;
#define V 5
char Vertices[V] = {'A', 'B', 'C', 'D', 'E'};
int minKey(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}
bool lesser(pair<int, int> p1, pair<int, int> p2)
{
    return (p1.first < p2.first);
}
void printMST(int parent[], int graph[V][V])
{
    list<pair<int, int>> l;
    for (int i = 1; i < V; i++)
        l.push_back(pair<int, int>(parent[i], i));
    //sort(l.begin(), l.end(), lesser);
    //sort(l.begin(), l.end(), [](pair<int, int> p1, pair<int, int> p2) -> bool { return p1.first < p2.first; });
    for (auto iter = l.begin(); iter != l.end(); ++iter)
        cout << Vertices[iter->first] << " " << Vertices[iter->second] << endl;
}

void primMST(int graph[V][V])
{
    int parent[V];
    int key[V];
    bool mstSet[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < V - 1; count++)
    {

        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    printMST(parent, graph);
}

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[])
{
    printf("顶点 \t\t 距离\n");
    for (int i = 0; i < V; i++)
        printf("%c \t\t %d\n", Vertices[i], dist[i]);
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist);
}
int main()
{
    cout << "Prim算法构建的最小生成树为：" << endl;
    int graph1[V][V] = {{0, 8, 5, 12, 7},
                        {8, 0, 4, 0, 0},
                        {5, 4, 0, 3, 11},
                        {12, 0, 3, 0, 6},
                        {7, 0, 11, 6, 0}};

    primMST(graph1);
    cout << "Dijkstra算法构建的最短路径为：" << endl;
    int graph2[V][V] = {{0, 10, 0, 30, 100},
                        {0, 0, 50, 0, 0},
                        {0, 0, 0, 0, 10},
                        {0, 0, 20, 0, 60},
                        {0, 0, 0, 0, 0}};
    dijkstra(graph2, 0);
    return 0;
}