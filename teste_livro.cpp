#include <iostream>

class No {
 private:
  int id;
  No* edgeto;
  No* prox;
  std::string cor;

 public:
  No();
  ~No();

  friend class Fila;
};

class Lista {
  Lista();
  ~Lista();
};

class Fila {
  Fila();
  int GetTamanho() { return tamanho; };
  bool Vazia() { return tamanho == 0; };
  void Enfileira(No* item);
  No Desenfileira();
  ~Fila();

 protected:
  int tamanho;

 private:
  No* head;
  No* tail;
};

Fila::Fila() {
  tamanho = 0;
  head = nullptr;
  tail = head;
}

Fila::~Fila() {
  delete head;
  delete tail;
}

void Fila::Enfileira(No* item) {
  if (tamanho == 0) {
    head = item;
    tail = item;
    tamanho++;
  } else {
    tail = item;
    tamanho++;
  }
}

No Fila::Desenfileira() {
  No aux = *head;
  if (tamanho > 1) head = head->prox;
  if (tamanho == 1) {
    head == nullptr;
    tail = nullptr;
  }
  return aux;
}