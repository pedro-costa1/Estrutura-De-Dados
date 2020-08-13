#include "vector.hpp"
#include <limits>
#include <iostream>
#include <algorithm>


// Construir lista vazia, mas com capacidade máxima informada.
vector::vector(unsigned int capacidade) {
    vetor = new int[capacidade];
    tamanho = 0;
    this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
vector::vector(unsigned int tamanho, int inicial) {
    vetor = new int[tamanho];
    capacidade = tamanho;
    this->tamanho = tamanho;

    for(unsigned int i = 0; i < tamanho; i++) {
        vetor[i] = inicial;
    }
}


// --- Métodos de "Coleção" ---


// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// FIXME Fazer realocação quando não houver espaço.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão que tínhamos antes...
void vector::inserir(int elemento) {
    // TODO Reorganizar o código
    if(this->tamanho < this->capacidade) {
        this->vetor[tamanho] = elemento;
        this->tamanho++;
    } else {
        // TODO Realocar o vetor e inserir "elemento"
        // duplicando a capacidade do novo vetor
        this -> vetor = (int*) realloc (this -> vetor, sizeof(int) * (this -> capacidade * 2));
        
        if (!this->vetor) {
            return;
        } else {
            //duplicando o valor da variavel capacidade
            this->capacidade *= 2;

            //inserindo o elemento
            this->vetor[tamanho] = elemento;

            //aumentando em 1 unidade o tamanho da lista
            this->tamanho++;
        }
    }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool vector::remover(int elemento) {
    // TODO Implementação.
    //caso pertença
    if (this->tamanho == 0) {
        return false;
    }

    if (pertence(elemento)) {
        //obtendo o indice do elemento que deseja remover
        int indice = obter_indice_de(elemento);

        //caso o elemento nao seja encontrado na funçao anterior
        if (indice == std::numeric_limits<unsigned int>::max()) {
            return false;
        } else {
            //caso seja
            for (unsigned int i = (indice + 1); i < this->tamanho; i++) {
                //voltando 1 casa de cada elemento a partir do indice para remover o elemento desejado
                this->vetor[i - 1] = this->vetor[i];
            }

            this->tamanho--;
            return true;
        }
    } else {
        return false;
    }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool vector::pertence(int elemento) {
    // TODO Implementação.
    if (this->tamanho == 0) {
        return false;
    }

    //percorrendo vetor
    for (unsigned int i = 0; i < this->tamanho; i++) {
        //caso encontre o elemento
        if (this->vetor[i] == elemento) {
            return true;
        }
    }

    // caso nao encontre
    return false;
}


// --- Métodos de "Lista" ---

// Inserir "elemento" na lista de forma que ele passe a constar no índice "indice".
// NOTE Necessário preservar a ordem relativa dos demais elementos.
void vector::inserir_em(unsigned int indice, int elemento) {
    // TODO Implementação.
    // caso o vetor esteja cheio
    if (this->tamanho == this->capacidade) {
        return;
    }

    int copiaIndice = indice;
    
    for (int i = this->tamanho; i >= copiaIndice; i--) {
        //voltando 1 casa ate chegar no indice desejado. assim liberando 1 espaço para o novo elemento
        this->vetor[i + 1] = this->vetor[i];
    }

    //inserindo o elemento no indice
    this->vetor[copiaIndice] = elemento;
    //aumentando em 1 unidade o tamanho
    this->tamanho++;
}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool vector::remover_de(unsigned int indice) {
    //caso o indice seja invalido ou a lista esteja vazia
    if (indice >= this->tamanho || this->tamanho == 0) {
        return false;
    }

    for (unsigned int i = (indice + 1); i < this->tamanho; i++) {
        //voltando 1 casa ate o elemento do indice para remover ele
        this->vetor[i - 1] = this->vetor[i];
    }
    //diminuindo em 1 unidade o tamnho doa lista
    this->tamanho--;

    return true;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int vector::obter_elemento_em(unsigned int indice) {
    // TODO Implementação.
    // caso o indice seja invalido(menor que zero ou maior que a quantidade de elementos)
    if (indice >= this -> tamanho || this -> tamanho == 0) {
        return std::numeric_limits<int>::max();
    }

    //retorna o elemento do indice desejado
    return this->vetor[indice];
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned int>::max()`
//      (forma de obter o maior valor representável).
unsigned int vector::obter_indice_de(int elemento) {
    // TODO Implementação.
    //caso a lista estaja vazia
    if (this->tamanho == 0) {
        return std::numeric_limits<unsigned int>::max();
    }

    //caso o elemento pertença a lista
    if (pertence(elemento)) {
        //percorre o vetor
        for (unsigned int i = 0; i < this->tamanho; i++) {
            //caso encontre o elemento
            if (this->vetor[i] == elemento) {
                return i;
            }
        }
    }

    //caso nao esteja na lista
    return std::numeric_limits<unsigned int>::max();

}    