#include <iostream>
#include <vector>

using namespace std;

struct AdjList{
    int destination;
    int weight;
    AdjList *next;
};

class Graph{
    int vertex;
    vector<AdjList*> list;
    public:
    Graph(int v){
        vertex = v;
        list.resize(v);
    }
    AdjList* make_node(int d, int w){
        AdjList *new_node = (AdjList*)malloc(sizeof(AdjList));
        new_node->destination=d;
        new_node->weight=w;
        new_node->next=NULL;
        return new_node;
    }
    void add_edge(int v, int d, int w){
        if(!list[v]){
            list[v] = make_node(d, w);
        }
        else{
            AdjList *temp = list[v];
            while(temp->next != NULL){
                temp=temp->next;
            }
            temp->next = make_node(d, w);
        }
    }
    void print(){
        for(int i=0; i<vertex; i++){
            if(!list[i]) continue;
            AdjList *temp = list[i];
            while(temp){
                cout<<i<<" "<<temp->destination<<" "<<temp->weight<<endl;
                temp=temp->next;
            }
        }
    }
};

int main(){
    Graph g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(0, 3, 3);
    g.add_edge(0, 2, 2);
    g.add_edge(2, 3, 1);
    g.print();
    return 0;
}