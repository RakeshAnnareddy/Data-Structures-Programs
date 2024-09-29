#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
class Heap {
  vector<int> heap;
  bool isMinHeap;
 
  void heapifyUp(int index) {
      if (index == 0) return;
      int parent = (index - 1) / 2;
 
      if ((isMinHeap && heap[index] < heap[parent]) || (!isMinHeap && heap[index] > heap[parent])) {
          swap(heap[index], heap[parent]);
          heapifyUp(parent);
      }
  }
 
  void heapifyDown(int index) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      int extreme = index;
 
      if (left < heap.size() && ((isMinHeap && heap[left] < heap[extreme]) || (!isMinHeap && heap[left] > heap[extreme]))) {
          extreme = left;
      }
 
      if (right < heap.size() && ((isMinHeap && heap[right] < heap[extreme]) || (!isMinHeap && heap[right] > heap[extreme]))) {
          extreme = right;
      }
 
      if (extreme != index) {
          swap(heap[index], heap[extreme]);
          heapifyDown(extreme);
      }
  }
 
public:
  Heap(bool isMin = true) : isMinHeap(isMin) {}
 
  void insert(int value) {
      heap.push_back(value);
      heapifyUp(heap.size() - 1);
  }
 
  void deleteElement(int value) {
      vector<int>::iterator it = find(heap.begin(), heap.end(), value);
      if (it == heap.end()) {
          cout << "Element not found in the heap." << endl;
          return;
      }
 
      int index = distance(heap.begin(), it);
      swap(heap[index], heap.back());
      heap.pop_back();
 
      if (index < heap.size()) {
          heapifyUp(index);
          heapifyDown(index);
      }
  }
 
  void display() const {
      // Using traditional for loop instead of range-based for loop
      for (size_t i = 0; i < heap.size(); ++i) {
          cout << heap[i] << " ";
      }
      cout << endl;
  }
};
 
int main() {
  Heap minHeap(true);  // Min Heap
  Heap maxHeap(false); // Max Heap
 
  // Insert elements
  minHeap.insert(10);
  minHeap.insert(20);
  minHeap.insert(5);
  minHeap.insert(30);
  minHeap.insert(2);
 
  maxHeap.insert(10);
  maxHeap.insert(20);
  maxHeap.insert(5);
  maxHeap.insert(30);
  maxHeap.insert(2);
 
  cout << "Min Heap: ";
  minHeap.display();
 
  cout << "Max Heap: ";
  maxHeap.display();
 
  // Delete elements
  minHeap.deleteElement(20);
  maxHeap.deleteElement(20);
 
  cout << "Min Heap after deleting 20: ";
  minHeap.display();
 
  cout << "Max Heap after deleting 20: ";
  maxHeap.display();
 
  return 0;
}