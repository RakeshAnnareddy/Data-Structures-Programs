#include <iostream>
#include <queue>
#include <vector>
 
using namespace std;
 
void BFT_Matrix(vector<vector<int> > &adjMatrix, int startVertex) {
  int numVertices = adjMatrix.size();
  vector<bool> visited(numVertices, false);
  queue<int> q;
 
  visited[startVertex] = true;
  q.push(startVertex);
 
  while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      cout << vertex << " ";
 
      for (int i = 0; i < numVertices; ++i) {
          if (adjMatrix[vertex][i] == 1 && !visited[i]) {
              visited[i] = true;
              q.push(i);
          }
      }
  }
}
 
int main() {
  int numVertices = 4;
  vector<vector<int> > adjMatrix(numVertices, vector<int>(numVertices, 0));
 
  // Manually setting up the adjacency matrix
  adjMatrix[0][1] = 1; adjMatrix[0][2] = 1;
  adjMatrix[1][0] = 1; adjMatrix[1][2] = 1; adjMatrix[1][3] = 1;
  adjMatrix[2][0] = 1; adjMatrix[2][1] = 1; adjMatrix[2][3] = 1;
  adjMatrix[3][1] = 1; adjMatrix[3][2] = 1;
 
  cout << "BFT using Adjacency Matrix: ";
  BFT_Matrix(adjMatrix, 0);  // Start from vertex 0
  return 0;
}