/*
    I first start off by making a directed graph with 1000 verticies (Easy way out)
    Then I add each set of courses as an edge in the graph
    Then I check whether there is a cycle or not
    If there is then Blackboard messed up, else everything is good
*/

#include <iostream>
#include <list>
#include <limits.h>
 
using namespace std;
 
class Graph{
    int V;    // No. of vertices
    list<int> *adj;    // adjacency lists
    bool isCyclicUtil(int v, bool visited[], bool *rs);  
    
    public:
        Graph(int V);   
        void addEdge(int v, int w);   
        bool isCyclic();    
};
 
Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w){
    adj[w].push_back(v); // Add w to v’s list.
}
 
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack){
    if(visited[v] == false){
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;
 
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i){
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }
 
    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic(){
    
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++){
        visited[i] = false;
        recStack[i] = false;
    }
 
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
 
    return false;
}
 
int main(){
    
    Graph g(1000); // Easy way out
    
    int C, pairs;
    cin >> C >> pairs;
    int course1, course2;
    
    if (C == 0 || C == 1){
        cout << "Good" << endl;
        return 0;
    }

    for (int i = 0; i < pairs; i++){
        cin >> course1 >> course2;
        g.addEdge(course1, course2);
    }

    if(g.isCyclic())
        cout << "Bad" << endl;
    else
        cout << "Good" << endl;
    return 0;
}