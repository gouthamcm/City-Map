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
    int destination_final_city;
    vector<AdjList *> list;
    vector<int> distance;
    vector<bool> visited;
    vector<int> parent;

public:
    Graph(int v)
    {
        vertex = v;
        // destination = 0; // comment it out later
        list.resize(v);
        distance.resize(v);
        visited.resize(v);
        parent.resize(v);
    }
    void set_destination(int des){
        destination_final_city = des;
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
        if (!list[d])
        {
            list[d] = make_node(v, w);
        }
        else
        {
            AdjList *temp = list[d];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = make_node(v, w);
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
        distance[destination_final_city] = 0;
        parent[destination_final_city] = -1;
        for (int i = 0; i < vertex - 1; i++)
        {
            int u = min_distance(distance, visited);
            visited[u] = true;
            AdjList *temp = list[u];
            while (temp)
            {

                int v = temp->destination;
                if (!visited[v] && (distance[u]+temp->weight <= distance[v]))
                {
                    if (parent[v] != -1)
                    {
                        parent[v] = min(parent[v], u);
                    }
                    else
                    {
                        parent[v] = u;
                    }
                    // parent[v]=u;
                    distance[v] = min(distance[v], distance[u] + temp->weight);
                }
                temp = temp->next;
            }
        }
        print_paths(distance, vertex, parent);
    }
    void print_paths(vector<int> distance, int n, vector<int> parent)
    {
        for (int i = 0; i < n; i++)
        {
            if(i==destination_final_city) continue;
            cout << destination_final_city << " ";
            print_p(parent, i);
            cout << endl;
        }
    }
    void print_p(vector<int> parent, int k)
    {
        if (parent[k] == -1)
        {
            return;
        }

        print_p(parent, parent[k]);
        cout << k << " ";
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
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
};

int main()
{
    Graph g(9);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 2, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(2, 3, 7);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(3, 5, 14);
    g.add_edge(4, 5, 10);
    g.add_edge(5, 6, 2);
    g.add_edge(6, 7, 1);
    g.add_edge(7, 8, 7);
    g.add_edge(6, 8, 6);
    g.set_destination(0);
    g.dijsktra();
    // g.print();
    return 0;
}