#include <iostream>
#include <vector>
#define MAXN 6
int n = 6;
bool used[MAXN];
std::vector<int> comp;

std::vector<int> g[MAXN] = {{1, 3}, {0, 2, 3}, {1, 3}, {0, 1, 2}, {3, 5}, {4}};

void dfs(int v) {
  used[v] = true;
  comp.push_back(v);
  for (size_t i = 0; i < (int)g[v].size(); i++) {
    int to = g[v][i];
    if (!used[to]) dfs(to);
  }
}

void find_comps() {
  for (int i = 0; i < n; i++) {
    used[i] = false;
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      comp.clear();
      dfs(i);
      std::cout << "Component: ";
      for (size_t j = 0; j < comp.size(); j++) {
        std::cout << ' ' << comp[j];
      }
      std::cout << std::endl;
    }
  }
}

int main() { find_comps(); }
