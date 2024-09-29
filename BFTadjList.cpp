#include <iostream>
#include <queue>
#include <vector>
 
using namespace std;
 
void BFT_List(vector<vector<int> > &adjList, int startVertex) {
  int numVertices = adjList.size();
  vector<bool> visited(numVertices, false);
  queue<int> q;
 
  visited[startVertex] = true;
  q.push(startVertex);
 
  while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      cout << vertex << " ";
 
      // Using traditional for loop instead of range-based for loop
      for (int i = 0; i < adjList[vertex].size(); ++i) {
          int adjVertex = adjList[vertex][i];
          if (!visited[adjVertex]) {
              visited[adjVertex] = true;
              q.push(adjVertex);
          }
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
 
  cout << "BFT using Adjacency List: ";
  BFT_List(adjList, 0);  // Start from vertex 0
  return 0;
}