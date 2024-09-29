#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility> // For std::pair
 
using namespace std;
 
class Graph {
  int V;  // Number of vertices
  vector<int> *adj;  // Adjacency list
  vector<vector<int> > biconnectedComponents;  // List to store bi-connected components
  int time;
 
  // Utility function to find bi-connected components using DFS
  void BCCUtil(int u, int parent[], int disc[], int low[], stack<pair<int, int> > &st);
 
public:
  Graph(int V);
  void addEdge(int v, int w);  // Function to add an edge
  void findBCC();  // Function to find bi-connected components
};
 
Graph::Graph(int V) {
  this->V = V;
  adj = new vector<int>[V];  // Dynamically allocate the adjacency list
  time = 0;
}
 
void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);  // Since the graph is undirected
}
 
void Graph::BCCUtil(int u, int parent[], int disc[], int low[], stack<pair<int, int> > &st) {
  // Initialize discovery time and low value
  disc[u] = low[u] = ++time;
  int children = 0;
 
  // Iterate through all vertices adjacent to this
  for (int i = 0; i < adj[u].size(); ++i) {
      int v = adj[u][i];  // v is current adjacent of u
 
      // If v is not visited yet, then make it a child of u in DFS tree and recurse for it
      if (disc[v] == -1) {
          children++;
          parent[v] = u;
 
          // Store the edge in the stack
          st.push(make_pair(u, v));
          BCCUtil(v, parent, disc, low, st);
 
          // Check if the subtree rooted at v has a connection back to one of the ancestors of u
          low[u] = min(low[u], low[v]);
 
          // If u is an articulation point, pop all edges from stack till (u, v)
          if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
              vector<int> component;
              while (st.top() != make_pair(u, v)) {
                  component.push_back(st.top().first);
                  component.push_back(st.top().second);
                  st.pop();
              }
              component.push_back(st.top().first);
              component.push_back(st.top().second);
              st.pop();
              biconnectedComponents.push_back(component);
          }
      }
      // Update low value of u for parent function calls.
      else if (v != parent[u] && disc[v] < disc[u]) {
          low[u] = min(low[u], disc[v]);
          st.push(make_pair(u, v));
      }
  }
}
 
void Graph::findBCC() {
  int *parent = new int[V];
  int *disc = new int[V];
  int *low = new int[V];
  stack<pair<int, int> > st;
 
  // Initialize parent and visited arrays
  for (int i = 0; i < V; i++) {
      disc[i] = -1;
      low[i] = -1;
      parent[i] = -1;
  }
 
  // Call the recursive helper function to find BCCs
  for (int i = 0; i < V; i++) {
      if (disc[i] == -1) {
          BCCUtil(i, parent, disc, low, st);
 
          // If stack is not empty, pop all edges
          vector<int> component;
          while (!st.empty()) {
              component.push_back(st.top().first);
              component.push_back(st.top().second);
              st.pop();
          }
          if (!component.empty()) {
              biconnectedComponents.push_back(component);
          }
      }
  }
 
  // Print all bi-connected components
  cout << "Bi-Connected Components:" << endl;
  for (int i = 0; i < biconnectedComponents.size(); i++) {
      for (int j = 0; j < biconnectedComponents[i].size(); j++) {
          cout << biconnectedComponents[i][j] << " ";
      }
      cout << endl;
  }
 
  delete[] parent;
  delete[] disc;
  delete[] low;
}
 
int main() {
  Graph g(7);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 3);
  g.addEdge(2, 4);
  g.addEdge(3, 4);
  g.addEdge(1, 5);
  g.addEdge(0, 6);
  g.addEdge(5, 6);
 
  g.findBCC();
 
  return 0;
}