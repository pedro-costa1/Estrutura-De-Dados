#include "ordered_list.hpp"
#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
ordered_list::ordered_list(unsigned int capacidade) {
    this->primeiro = nullptr;
    this->tamanho = 0;
}

// Construir lista com "tamanho" cópias do valor "inicial".
ordered_list::ordered_list(unsigned int tamanho, int inicial) {
    // TODO Implementação.
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
void ordered_list::inserir(int elemento) {
    // TODO Implementação.
    no_encadeado* novo_no = new no_encadeado(elemento, this->primeiro);

    novo_no->valor = elemento;
    
    novo_no->proximo = this->primeiro->proximo;
    
    this->primeiro->proximo = novo_no;
    
    this->tamanho = tamanho++;
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
bool ordered_list::remover(int elemento) {
    // TODO Implementação.
    if (this->tamanho == 0 || !pertence(elemento)) {
        return false;
    } else {
        unsigned int indice_aux = obter_indice_de(elemento);
        
        no_encadeado* novo_no = obter_no_em(indice_aux);
        
        while (novo_no->proximo != nullptr) {
        if (novo_no->valor == elemento) {
            novo_no->proximo = novo_no->proximo->proximo;
            this->tamanho = tamanho--;
            return true;
        }
        novo_no = novo_no->proximo;
        }
        return false;
    }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool ordered_list::pertence(int elemento) {
    // TODO Implementação.
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

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool ordered_list::remover_de(unsigned int indice) {
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
int ordered_list::obter_elemento_em(unsigned int indice) {
    // TODO Implementação.
    if (indice > this->tamanho) {
        std::numeric_limits<int>::max();
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
unsigned int ordered_list::obter_indice_de(int elemento) {
    // TODO Implementação.
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
ordered_list::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
    this->valor = valor;
    this->proximo = proximo;
}

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
ordered_list::no_encadeado* ordered_list::obter_no_em(unsigned int indice) {
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
ordered_list::no_encadeado* ordered_list::obter_no_anterior_a(int valor) {
    // TODO Implementação.
    no_encadeado* no = this->primeiro;
    
    while (no != nullptr) {
        if (no->proximo->valor == valor) {
        return no;
        }
        no = no->proximo;
    }
}