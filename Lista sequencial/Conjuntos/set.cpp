#include "set.hpp"
#include <limits>
#include <iostream>
#include <algorithm>

// Construir lista vazia, mas com capacidade máxima informada.
set::set(unsigned int capacidade) {
    vetor = new int[capacidade];
    tamanho = 0;
    this->capacidade = capacidade;
}

// --- Métodos de "Coleção" ---


// Inserir "elemento" na coleção.
// Retornar indicativo de sucesso da inserção.
// NOTE Deve aumentar a capacidade caso necessário.
// NOTE Observe que aumentar em apenas uma unidade não nos alivia da pressão que tínhamos antes...
bool set::inserir(int elemento) {
    // TODO Implementação.
    //verificando se o elemento ja existe
    for (unsigned int i = 0; i < this->tamanho; i++) {
        if (vetor[i] == elemento) {
            return false;
        }
    }
    
    if (this->tamanho < this->capacidade) {
        this->vetor[tamanho] = elemento;
        this->tamanho++;

        return true;
    } else {
        // duplicando a capacidade do novo vetor
        this -> vetor = (int*) realloc (this -> vetor, sizeof(int) * (this -> capacidade * 2));
        
        if (!this->vetor) {
            return false;
        } else {
            //duplicando o valor da variavel capacidade
            this->capacidade *= 2;

            //inserindo o elemento
            this->vetor[tamanho] = elemento;

            //aumentando em 1 unidade o tamanho da lista
            this->tamanho++;

            return true;
        }
    }
}


// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool set::remover(int elemento) {
    // TODO Implementação.
    if (this->tamanho == 0) {
        return false;
    }

    //caso pertença
    if (pertence(elemento)) {
        //percorre o vetor procurando o elemento
        for (unsigned int i = 0; i < this->tamanho; i++) {
            if (vetor[i] == elemento) {
                //caso ache
                for (unsigned int j = i; j < this->tamanho; j++) {
                    //volta em 1 unidade todos os elementos apos remover o elemnto desejado
                    int aux = vetor[j];
                    vetor[j] = vetor[j + 1];
                    vetor[j + 1] = aux;
                }

                this->tamanho--;
                return true;
            }
        }
    } else {
        return false;
    }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool set::pertence(int elemento) const {
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


// --- Métodos de "Conjunto" ---

// Tornar o próprio conjunto (`this`) o resultado de sua união com o outro informado.
void set::uniao_com(set const &conjunto) {
    // TODO Implementação.
    //percorrendo vetor
    for (unsigned l = 0; l < conjunto.tamanho; l++) {
        if (!pertence(conjunto.vetor[l])) {
            //caso o elemento nao pertença, chama a função inserir
            inserir(conjunto.vetor[l]);
        }
    }
}

// Tornar o próprio conjunto (`this`) o resultado de sua intersecção com o outro informado.
void set::intersecao_com(set const &conjunto) {
    // TODO Implementação.
    //caso seja vazio
    if (conjunto.tamanho == 0) {
        return;
    }

    //percorrendo o vetor
    for (unsigned l = 0; l < conjunto.tamanho; l++) {
        if (!pertence(conjunto.vetor[l])) {
            //caso o elemento nao pertença, chama a função de remover
            remover(conjunto.vetor[l]);
        }
    }
}

// Testar se este conjunto (`this`) está contido no outro informado.
bool set::esta_contido_em(set const &conjunto) const {
    // TODO Implementação.
    //caso seja vazio
    if (conjunto.tamanho == 0) {
        return true;
    }

    //variavel auxiliar
    bool contido = false;

    //percorrendo o vetor
    for (unsigned l = 0; l < conjunto.tamanho; l++) {
        //fazendo verificação
        if (pertence(conjunto.vetor[l])) {
            contido = true;
        } else {
            contido = false;
        }
    }
    return contido;
}