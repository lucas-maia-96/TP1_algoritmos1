#include <iostream>
#include <vector>

std::vector<std::vector<int>> adj;  // lista de adjacencias
int n = 8;                          // num de vertices
std::vector<int> color;             // 0 -> unvisited, 1->visited, 2-> exited
std::vector<int> time_in, time_out;
int dfs_timer = 0;

void dfs(int v) {
  time_in[v] = dfs_timer++;
  color[v] = 1;
  for (int u : adj[v]) {
    if (color[u] == 0) {
      dfs(u);
    }
  }
  color[v] = 2;
  time_out[v] = dfs_timer++;
}

int main() {
  int s;  // no raiz
  int l;
  std::cout << "vertice raiz: ";
  std::cin >> s;
  std::cout << std::endl << "vertice destino: ";
  std::cin >> l;
  std::cout << std::endl;

  adj = {{},           {2, 3}, {1, 3, 4, 5}, {1, 2, 5, 7, 8}, {2, 5},
         {2, 3, 4, 6}, {5},    {3, 8},       {3, 7}};

  for (int i = 0; i < 9; i++) {
    color.push_back(0);
    time_in.push_back(0);
    time_out.push_back(0);
  }

  dfs(s);


  
}