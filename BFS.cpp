#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
  std::vector<std::vector<int>> adj;  // lista de adjacencias
  int n = 8;                          // numero de nos
  int s;                              // no raiz
  int l;                              // vertice destino

  std::cout << "vertice raiz: ";
  std::cin >> s;
  std::cout << std::endl << "vertice destino: ";
  std::cin >> l;
  std::cout << std::endl;

  std::queue<int> q;
  std::vector<bool> used(n);
  std::vector<int> d(n), p(n);

  adj = {{},           {2, 3}, {1, 3, 4, 5}, {1, 2, 5, 7, 8}, {2, 5},
         {2, 3, 4, 6}, {5},    {3, 8},       {3, 7}};

  q.push(s);
  used[s] = true;
  p[s] = -1;
  d[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : adj[v]) {
      if (!used[u]) {
        used[u] = true;
        q.push(u);
        d[u] = d[v] + 1;
        p[u] = v;
      }
    }
  }

  if (!used[l]) {
    std::cout << "Sem Caminho!!" << std::endl;
  } else {
    std::vector<int> path;
    for (int i = l; i != -1; i = p[i]) {
      path.push_back(i);
    }
    reverse(path.begin(), path.end());
    std::cout << "Path: ";
    for (int v : path) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}