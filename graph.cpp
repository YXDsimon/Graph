#include <iostream>
#include <vector>
#include <list>
#define size 5
using namespace std;
//以下代码中含有新用法，c++17以下的编译器可能无法通过
char node[size] = {'A', 'B', 'C', 'D', 'E'};

void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
}
void printGraph(vector<int> adj[], int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << node[v];
        for (auto x : adj[v])
            cout << "-> " << node[x];
        printf("\n");
    }
}
class Graph
{
    int V;
    list<int> *adj;
    void DFSUtil(int v, int visited[]);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int v);
    void BFS(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, int visited[])
{
    visited[v] = 1;
    cout << node[v] << " ";
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
        {
            DFSUtil(*i, visited);
        }
}
void Graph::DFS(int v)
{
    int visited[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }
    DFSUtil(v, visited);
}
void Graph::BFS(int s)
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    list<int> queue;
    visited[s] = true;
    queue.push_back(s);
    list<int>::iterator i;

    while (!queue.empty())
    {
        s = queue.front();
        cout << node[s] << " ";
        queue.pop_front();
        for (i = adj[s].begin(); i != adj[s].end(); ++i) //这里要c++17及以上的编译器才能通过
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}
int main()
{
    cout << "邻接矩阵法输出：" << endl;
    int m[size][size] = {0}; //邻接矩阵法
    m[0][3] = 1;
    m[1][0] = 1;
    m[1][3] = 1;
    m[2][1] = 1;
    m[3][2] = 1;
    m[3][4] = 1;
    m[4][0] = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (m[i][j] == 1)
                cout << node[i] << " -> " << node[j] << endl;
        }
    }

    vector<int> adj[size]; //邻接列表法
    addEdge(adj, 0, 3);
    addEdge(adj, 1, 0);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 1);
    addEdge(adj, 3, 2);
    addEdge(adj, 4, 0);
    addEdge(adj, 3, 4);
    cout << "邻接列表法输出：" << endl;
    printGraph(adj, size);

    Graph g(size); //深度,广度优先遍历
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(1, 3);
    g.addEdge(2, 1);
    g.addEdge(3, 2);
    g.addEdge(4, 0);
    g.addEdge(3, 4);
    cout << "深度优先遍历的结果是：" << endl;
    g.DFS(0);

    cout << endl
         << "深度优先遍历的结果是：" << endl;
    g.BFS(0);
    cout << endl;
    return 0;
}