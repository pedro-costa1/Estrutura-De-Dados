class list {
    private:
    // Classe que representa os componentes da lista na memória
    class no_encadeado {
    public:
        int valor;

        // Referência para o nó que vem após o atual
        no_encadeado* proximo;

        friend class list;

        // Construtor
        no_encadeado(int valor, no_encadeado* proximo = nullptr);
    };

    // Contagem da quantidade de elementos presentes na lista.
    no_encadeado* primeiro;
    unsigned int tamanho;

    public:
    // Construtores
    list();
    list(unsigned int tamanho, int inicial);

    // Métodos de "Coleção"
    unsigned int obter_tamanho() { return tamanho; }

    void inserir(int elemento);
    bool remover(int elemento);
    bool pertence(int elemento);

    // Métodos de "Lista"
    bool inserir_em(unsigned int indice, int elemento);
    bool remover_de(unsigned int indice);

    int obter_elemento_em(unsigned int indice);
    unsigned int obter_indice_de(int elemento);

    protected:
    // Métodos auxiliares
    no_encadeado* obter_no_em(unsigned int indice);
    no_encadeado* obter_no_anterior_a(int valor);
};