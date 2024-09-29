#include <iostream>
#include <vector>
 
using namespace std;
 
void DFT_List(vector<vector<int> > &adjList, vector<bool> &visited, int vertex) {
  visited[vertex] = true;
  cout << vertex << " ";
 
  // Using traditional for loop instead of range-based for loop
  for (int i = 0; i < adjList[vertex].size(); ++i) {
      int adjVertex = adjList[vertex][i];
      if (!visited[adjVertex]) {
          DFT_List(adjList, visited, adjVertex);
      }
  }
}
 
int main() {
  int numVertices = 4;
  vector<vector<int> > adjList(numVertices);
 
  // Manually setting up the adjacency list
  adjList[0].push_back(1); adjList[0].push_back(2);
  adjList[1].push_back(0); adjList[1].push_back(2); adjList[1].push_back(3);
  adjList[2].push_back(0); adjList[2].push_back(1); adjList[2].push_back(3);
  adjList[3].push_back(1); adjList[3].push_back(2);
 
  vector<bool> visited(numVertices, false);
  cout << "DFT using Adjacency List: ";
  DFT_List(adjList, visited, 0);  // Start from vertex 0
  return 0;
}
