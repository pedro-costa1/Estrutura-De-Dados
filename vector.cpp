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
    if(tamanho < capacidade) {
        vetor[tamanho] = elemento;
        tamanho++;
    } else {
        // TODO Realocar o vetor e inserir "elemento"
        // duplicando a capacidade do novo vetor
        int* vetorDuplicado = new int[capacidade * 2];
        // passando os elementos do vetor anteriro para o novo vetor
        for (unsigned int i = 0; i < tamanho; i++) {
            vetorDuplicado[i] = vetor[1];
        }

        //inserindo o elemento
        vetorDuplicado[capacidade] = elemento;

        //deletando o vetor anterior
        delete[] vetor;
        //assumindo o novo vetor
        vetor = vetorDuplicado;
        //aumentando o tamanho em 1 unidade
        tamanho++;
        //duplicando o valor da variavel capacidade
        capacidade *= 2; 
    }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool vector::remover(int elemento) {
    // TODO Implementação.
    //caso pertença
    if (pertence(elemento)) {
        for (unsigned int i = 0; i < tamanho; i++) {
            //caso ache o elemento
            if (vetor[i] == elemento) {
                for (unsigned int j = i; j < tamanho; j++) {
                    //invertendo posiçoes ate o elemento encontrado va para ultimo
                    int aux = vetor[j];
                    vetor[j] = vetor[j + 1];
                    vetor[j + 1] = aux;
                }
                //diminuindo tamanho em 1 unidade e eliminando o ultimo elemento
                tamanho--;
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool vector::pertence(int elemento) {
    // TODO Implementação.
    ///percorrendo o vetor
    for (unsigned int i = 0; i < tamanho; i++) {
        //caso ache o vator
        if (vetor[i] == elemento) {
            return true;
        }
    }

    //caso nao ache
    return false;
}


// --- Métodos de "Lista" ---

// Inserir "elemento" na lista de forma que ele passe a constar no índice "indice".
// NOTE Necessário preservar a ordem relativa dos demais elementos.
void vector::inserir_em(unsigned int indice, int elemento) {
    // TODO Implementação.
    // caso o vetor esteja cheio
    if (tamanho == capacidade) {
        return;
    } else {
        //caso nao esteja
        tamanho++;
        for (unsigned int i = tamanho - 1; i > indice; i--) {
            //passando os elementos 1 posiçao a frente apos indice desejado
            vetor[i + 1] = vetor[i];
            vetor[i] = vetor[i - 1];
        }
        //inserindo elemento desejado
        vetor[indice] = elemento;
    }
}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool vector::remover_de(unsigned int indice) {
    if(indice >= tamanho) {
        return false;
    }

    for(unsigned int i = indice+1; i < tamanho; i++) {
        vetor[i-1] = vetor[i];
    }
    tamanho--;
    return true;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int vector::obter_elemento_em(unsigned int indice) {
    // TODO Implementação.
    // caso o indice seja invalido(menor que zero ou maior que a quantidade de elementos)
    if (indice <= 0 || indice >= tamanho) {
        return std::numeric_limits<int>::max();
    } else {
        //caso seja valido retorna o elemento do indice desejado
        return vetor[indice];
    }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned int>::max()`
//      (forma de obter o maior valor representável).
unsigned int vector::obter_indice_de(int elemento) {
    // TODO Implementação.
    //percorrendo vetor
    for (unsigned int i = 0; i < tamanho; i++) {
        //caso ache o elemento desejado
        if (vetor[i] == elemento) {
            //retorna indice
            return i;
        }
    }

    return std::numeric_limits<unsigned int>::max();
}