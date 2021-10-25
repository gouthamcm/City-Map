#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct AdjList
{
    int destination;
    int weight;
    AdjList *next;
};

class Graph
{
    int vertex;
    int destination;
    vector<AdjList *> list;
    vector<int> distance;
    vector<bool> visited;
    vector<int> parent;

public:
    Graph(int v)
    {
        vertex = v;

        list.resize(v);
        distance.resize(v);
        visited.resize(v);
        parent.resize(v);
    }
    AdjList *make_node(int d, int w)
    {
        AdjList *new_node = (AdjList *)malloc(sizeof(AdjList));
        new_node->destination = d;
        new_node->weight = w;
        new_node->next = NULL;
        return new_node;
    }
    void add_edge(int v, int d, int w)
    {
        if (!list[v])
        {
            list[v] = make_node(d, w);
        }
        else
        {
            AdjList *temp = list[v];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = make_node(d, w);
        }
    }
    void print()
    {
        for (int i = 0; i < vertex; i++)
        {
            if (!list[i])
                continue;
            AdjList *temp = list[i];
            while (temp)
            {
                cout << i << " " << temp->destination << " " << temp->weight << endl;
                temp = temp->next;
            }
        }
    }
    void dijsktra()
    {
        // parent[destination]=-1;
        for (int i = 0; i < vertex; i++)
        {
            parent[i] = -1;
            visited[i] = false;
            distance[i] = INT_MAX;
        }
        distance[destination] = 0;
        parent[destination] = -1;
        for (int i = 0; i < vertex - 1; i++)
        {
            int u = min_distance(distance, visited);
            visited[u] = true;
            AdjList *temp=list[u];
            while(temp){
                
                int v=temp->destination;
                if(!visited[v]){
                    if(parent[v]!=-1){
                        parent[v]=min(parent[v], u);
                    }else{
                        parent[v]=u;
                    }
                    distance[v] = min(distance[v], distance[u]+temp->weight);
                }
                temp=temp->next;
            }
        }
    }
    int min_distance(vector<int> distance, vector<bool> visited)
    {
        int min_dis = INT_MAX, min_pos;
        for (int i = 0; i < vertex; i++)
        {
            if (!visited[i])
            {
                if (distance[i] < min_dis)
                {
                    min_dis = distance[i];
                    min_pos = i;
                }
            }
        }
        return min_pos;
    }
    int min(int a, int b){
        return a<b?a:b;
    }
};

int main()
{
    Graph g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(0, 3, 3);
    g.add_edge(0, 2, 2);
    g.add_edge(2, 3, 1);
    g.print();
    return 0;
}