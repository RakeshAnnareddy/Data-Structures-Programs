#include <iostream>
#include <vector>
 
using namespace std;
 
void DFT_Matrix(vector<vector<int> > &adjMatrix, vector<bool> &visited, int vertex) {
  visited[vertex] = true;
  cout << vertex << " ";
 
  for (int i = 0; i < adjMatrix.size(); ++i) {
      if (adjMatrix[vertex][i] == 1 && !visited[i]) {
          DFT_Matrix(adjMatrix, visited, i);
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
 
  vector<bool> visited(numVertices, false);
  cout << "DFT using Adjacency Matrix: ";
  DFT_Matrix(adjMatrix, visited, 0);  // Start from vertex 0
  return 0;
}