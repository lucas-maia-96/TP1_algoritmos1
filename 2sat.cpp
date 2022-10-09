#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj, adj_t;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
  used[v] = true;
  for (int u : adj[v]) {
    if (!used[u]) dfs1(u);
  }
  order.push_back(v);
}

void dfs2(int v, int cl) {
  comp[v] = cl;
  for (int u : adj_t[v]) {
    if (comp[u] == -1) dfs2(u, cl);
  }
}

bool solve_2SAT(int n) {
  order.clear();
  used.clear();
  comp.clear();
  assignment.clear();
  used.assign(n, false);
  for (int i = 0; i < n; ++i) {
    if (!used[i]) dfs1(i);
  }

  comp.assign(n, -1);
  for (int i = 0, j = 0; i < n; ++i) {
    int v = order[n - i - 1];
    if (comp[v] == -1) dfs2(v, j++);
  }

  assignment.assign(n / 2, false);
  for (int i = 0; i < n; i += 2) {
    if (comp[i] == comp[i + 1]) return false;
    assignment[i / 2] = comp[i] > comp[i + 1];
  }
  return true;
}

void add_disjunction(int a, bool na, int b, bool nb) {
  // na and nb signify whether a and b are to be negated
  a = 2 * a ^ na;
  b = 2 * b ^ nb;
  int neg_a = a ^ 1;
  int neg_b = b ^ 1;
  adj[neg_a].push_back(b);
  adj[neg_b].push_back(a);
  adj_t[b].push_back(neg_a);
  adj_t[a].push_back(neg_b);
}

int main() {
  ifstream entrada;
  int n_seg, n_prop;
  int a, b;
  bool na, nb;
  bool res;
  int i, j;

  entrada.open("in.txt");

  while (1) {
    entrada >> n_seg >> n_prop;
    adj.assign(2 * n_prop + 2, {});
    adj_t.assign(2 * n_prop + 2, {});

    if (n_seg == 0 || n_prop == 0) break;

    for (i = 0; i < n_seg; i++) {
      for (j = 0; j < 2; j++) {
        entrada >> a >> b;
        if (a == 0) a = b;
        if (b == 0) b = a;
        if (j == 1) {
          a *= -1;
          b *= -1;
        }
        if (a >= 0)
          na = false;
        else {
          na = true;
          a *= -1;
        }
        if (b >= 0)
          nb = false;
        else {
          nb = true;
          b *= -1;
        }
        add_disjunction(a, na, b, nb);
      }
    }
    res = solve_2SAT(2 * n_prop);
    if (res)
      cout << "sim" << endl;
    else
      cout << "nao" << endl;

    for (vector<int> v : adj) v.clear();
    for (vector<int> v : adj_t) v.clear();
    adj.clear();
    adj_t.clear();
  }

  entrada.close();
}