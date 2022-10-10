#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj,
    adj_t;  // Lista de adjacencia e a transposta(ordem das arestas invertida)
vector<bool>
    used;  // vetor para registrar se o vertice ja foi visitado (na dfs)
vector<int> order;  // order: vetor que registra a ordem de saida dos vertices
                    // IMPORTANTE para rodar a segunda DFS na ordem descescente
                    // de tempo de saida.
vector<int> comp;   // comp: vetor para registrar a qual componente fortemente
                    // conectado cada vertice pertence (importante para saber a
                    // existencia de solucao do problema)
vector<bool> assignment;  // vetor para registrar se a proposta deve ser aceita
                          // ou nao (util para encontrar uma solucao, mas como
                          // queremos apenas saber a existencia esse vetor se
                          // torna nao necessario, de forma que sua retirada nao
                          // afeta na resolucao do trabalho. Decidi manter pois,
                          // para saber uma solucao de um problema, basta
                          // imprimir esse vetor) ATENCAO: numero grande de
                          // propostas geram um output igualmente grande

void dfs1(int v) {  // DFS simples, busca em profundidade e registramos apenas a
                    // ordem de saida
  used[v] = true;
  for (int u : adj[v]) {
    if (!used[u]) dfs1(u);
  }
  order.push_back(v);
}

void dfs2(int v,
          int cl) {  // DFS simples, porem como é a segunda, seguindo a ordem
                     // topologia e no grafo transposto, conseguimos registrar
                     // as componentes fortemente conectados de cada vertice
  comp[v] = cl;
  for (int u : adj_t[v]) {
    if (comp[u] == -1) dfs2(u, cl);
  }
}

bool solve_2SAT(int n) {  // Algoritmo que vai encontrar a solucao
  order.clear();
  used.clear();
  comp.clear();
  assignment.clear();  // Limpamos todos os vetores, pois no trabalho calculamos
                       // a solucao para varios problemas e para evitar qualquer
                       // possivel influencia
  used.assign(
      n,
      false);  // inicializacao do vetor used com todos os vertices como false
  for (int i = 0; i < n; ++i) {
    if (!used[i])
      dfs1(i);  // roda dfs no grafo, vertices ja vistos nao sao revisitados
  }

  comp.assign(n, -1);  // inicializa o vetor que registra a componente
                       // formetemte conectado de cada vertice.
  for (int i = 0, j = 0; i < n; ++i) {
    int v = order[n - i - 1];
    if (comp[v] == -1)
      dfs2(v, j++);  // calcula o compentente fortemente conctado de cada
                     // vertice com a segunda DFS, seguindo a ordem topologica e
                     // e no grafo trasnposto.
  }

  assignment.assign(
      n / 2, false);  // vetor que registra uma solucao para cada proporta de
                      // campanha (vetor nao necessario para o trabalho, mas de
                      // interesse em manter no programa)
  for (int i = 0; i < n; i += 2) {
    if (comp[i] == comp[i + 1])
      return false;  // *** PARTE IMPORTANTE *** ASSIM QUE ENCONTRA UMA PROPOSTA
                     // E SUA NEGACAO NA MESMA COMPONENTE FORTEMENTE CONECTADO,
                     // O PROBLEMA JA NAO TEM SOLUCAO!!!
    assignment[i / 2] = comp[i] > comp[i + 1];
  }
  return true;  // caso nenhuma contradicao seja encontrada no for anterior,
                // entao o problema tem solucao
}

void add_disjunction(int a, bool na, int b, bool nb) {
  // na e nb sao booleanos para marcar quando é a negacao da proporta a ou b
  // aqui é feita as transformacoes para colocar a->2a e !a->2a+1
  // alem disso, ja é criado junto o grafo transposto
  int neg_a;
  int neg_b;

  a = 2 * a;
  b = 2 * b;

  if (na) {
    neg_a = a;
    a += 1;
  } else {
    neg_a = a + 1;
  }

  if (nb) {
    neg_b = b;
    b += 1;
  } else {
    neg_b = b + 1;
  }

  adj[neg_a].push_back(b);
  adj[neg_b].push_back(a);
  adj_t[b].push_back(neg_a);
  adj_t[a].push_back(neg_b);
}

int main() {
  int n_seg, n_prop;  // numero de seguidores e numero de propostas de
                      // propaganda
  int a, b;           // propostas escolhidas pelos seguidores
  bool na, nb;  // usar true quando for as escolhas que o seguidor NAO quer
  bool res;     // resposta se o problema tem solucao ou nao
  int i, j;     // variaveis para iterar os loops

  while (1) {
    cin >> n_seg >> n_prop;
    adj.assign(2 * n_prop + 2,
               {});  // alocacao dos grafos: é o dobro + 2 porque uso a X
                     // proposta com o indice 2*X e !X como 2*X + 1 e pulo o
                     // indice 0 (e consequentemente 1) do vetor;
    adj_t.assign(2 * n_prop + 2, {});

    if (n_seg == 0 || n_prop == 0) break;  // condicao de parada do loop

    for (i = 0; i < n_seg; i++) {
      for (j = 0; j < 2; j++) {  // leitura das escolhas dos seguidores
        cin >> a >> b;
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
        if (a == 0 and b == 0) continue;
        add_disjunction(a, na, b, nb);  // coloca as escolhas nos grafos
      }
    }
    res = solve_2SAT(2 * n_prop);  // resolve o problema
    if (res)
      cout << "sim" << endl;
    else
      cout << "nao" << endl;

    /*  for (bool resp : assignment) cout << resp << " ";   ***** IMPRESSAO DA
        cout << endl; */
    for (vector<int> v : adj) v.clear();
    for (vector<int> v : adj_t) v.clear();
    adj.clear();
    adj_t.clear();
  }
}