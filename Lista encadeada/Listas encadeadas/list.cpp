#include "list.hpp"
#include <limits>

// Construir lista vazia
list::list() {
    this->primeiro = nullptr;
    this->tamanho = 0;
}

// Construir lista com "tamanho" cópias do valor "inicial".
list::list(unsigned int tamanho, int inicial) {
    // TODO Implementação.
    this->tamanho = tamanho;

    this->primeiro = nullptr;

    for (unsigned int i = 0; i < this->tamanho; i++) {
        no_encadeado* novo_no = new no_encadeado(inicial, this->primeiro);
        this->primeiro = novo_no;
    }
}


// --- Métodos de "Coleção" ---


// Inserir "elemento" na coleção. Sempre deve executar a inserção.
void list::inserir(int elemento) {
    // TODO Implementação.
    if (tamanho == 0) {
        no_encadeado* novo_no = new no_encadeado(elemento);
        
        this->primeiro = novo_no;

        this->tamanho++;
    } else {
        no_encadeado* anterior = obter_no_em(tamanho - 1);
        
        no_encadeado* novo_no = new no_encadeado(elemento);
        
        anterior->proximo = novo_no;
        
        this->tamanho++;
    }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool list::remover(int elemento) {
    // TODO Implementação.
      if (this->tamanho == 0 || !pertence(elemento)) {
        return false;
    } else {
        int indice = obter_indice_de(elemento);
        
        no_encadeado* noRemovido = obter_no_em(indice);
        
        no_encadeado* noAnterior = obter_no_em(indice - 1);
        
        if (indice == 0) {
            this->primeiro = noRemovido->proximo;
            
            delete[] noRemovido;
            
            this->tamanho--;
            
            return true;
        } else {
            noAnterior->proximo = noRemovido->proximo;
            
            delete[] noRemovido;
            
            this->tamanho--;
            
            return true;
        }
    }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool list::pertence(int elemento) {
    // TODO Implementação.
    if (this->tamanho == 0) {
        return false;
    }

    no_encadeado* no = this->primeiro;
    
    while (no != nullptr) {
        if (no->valor == elemento) {
        return true;
        }
        no = no->proximo;
    }
    return false;
}


// --- Métodos de "Lista" ---

// Inserir "elemento" na lista de forma que ele passe a constar no índice "indice".
// NOTE Necessário preservar a ordem relativa dos demais elementos.
bool list::inserir_em(unsigned int indice, int elemento) {
    if(indice == 0) {
        no_encadeado* novo_no = new no_encadeado(elemento, this->primeiro);
        this->primeiro = novo_no;

        this->tamanho++;

        return true;
    } else {
        no_encadeado* anterior = obter_no_em(indice - 1);

        if(anterior != nullptr) {
            no_encadeado* novo_no = new no_encadeado(elemento);
            novo_no->proximo = anterior->proximo;
            anterior->proximo = novo_no;

            this->tamanho++;

            return true;
        } else {
            return false;
        }
    }
}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool list::remover_de(unsigned int indice) {
    // TODO Implementação.
    if (indice < tamanho) {
        no_encadeado* no_removido = obter_no_em(indice);
        remover(no_removido->valor);
        return true;
    } else {
        return false;
    }
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int list::obter_elemento_em(unsigned int indice) {
    // TODO Implementação.
    if (indice > this->tamanho) {
        return std::numeric_limits<int>::max();
    }

    no_encadeado* no = obter_no_em(indice);
    if (no == nullptr) {
        return std::numeric_limits<int>::max();
    } else {
        return no->valor;
    }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned int>::max()`
//      (forma de obter o maior valor representável).
unsigned int list::obter_indice_de(int elemento) {
    unsigned int indice = 0;
    no_encadeado* no = this->primeiro;

    while(no != nullptr) {
        if(no->valor == elemento) {
            return indice;
        }
        indice++;
        no = no->proximo;
    }

    return std::numeric_limits<unsigned int>::max();
}

// --- Métodos Auxiliares ---

// Construtor de um nó, onde a informação do próximo, no momento construção, é opcional
list::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
    this->valor = valor;
    this->proximo = proximo;
}

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
list::no_encadeado* list::obter_no_em(unsigned int indice) {
    // TODO Implementação.
    if (this->tamanho == 0 || indice > this->tamanho) {
        return nullptr;
    }

    no_encadeado* no = this->primeiro;

    for (unsigned int i = 0; i < indice; i++) {
        no = no->proximo;
    }
    return no;
}

// Desejamos obter o próprio nó que veja **antes** de algum com o valor informado.
// (ou seja, `anterior.proximo.valor == valor`)
// Auxilia processos que dependem de encontrar nós baseado em um valor.
// Deve retornar `nullptr` quando tal nó não existe.
list::no_encadeado* list::obter_no_anterior_a(int valor) {
    // TODO Implementação.
    no_encadeado* no = this->primeiro;
    
    while (no != nullptr) {
        if (no->proximo->valor == valor) {
        return no;
        }
        no = no->proximo;
    }
}