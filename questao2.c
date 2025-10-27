/*
 * QUESTAO 02: VETOR DINAMICO
 * Incluindo as bibliotecas
 */
#include <stdio.h>
#include <stdlib.h> // Para malloc e free

// 1. Função que cria o vetor
// Recebe o tamanho 'n' e retorna o vetor (ponteiro)
int* cria_vetor(int n) {
    int* vetor;
    
    // "malloc" aloca (reserva) um espaço na memória.
    // Pedimos 'n' espaços, cada um do tamanho de um 'int'.
    vetor = (int*) malloc(n * sizeof(int));
    
    // Se 'vetor' for NULL, é porque não conseguiu alocar (ex: sem memória)
    if (vetor == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        exit(1); // Aborta o programa
    }
    
    printf("Vetor de %d posicoes criado!\n", n);
    return vetor;
}

// 2. Função que imprime o vetor
// Recebe o vetor e seu tamanho 'n'
void imprime_vetor(int* vetor, int n) {
    printf("\n--- Imprimindo Vetor ---\n");
    // "for" é um loop que vai de 0 até n-1
    for (int i = 0; i < n; i++) {
        // "vetor[i]" acessa a posição 'i' do vetor
        printf("Posicao %d: %d\n", i, vetor[i]);
    }
}

// 3. Função que libera a memória
// Recebe o vetor que foi criado com 'malloc'
void libera_vetor(int* vetor) {
    // "free" devolve a memória que 'malloc' pegou.
    // Isso é MUITO importante para não "vazar" memória.
    free(vetor);
    printf("\nMemoria liberada!\n");
}


// --- FUNÇÃO PRINCIPAL (main) ---
int main() {
    int n; // Variável para guardar o tamanho
    int* meu_vetor; // O ponteiro que vai ser o nosso vetor
    
    // Pede o tamanho
    printf("Digite o tamanho do vetor (N): ");
    scanf("%d", &n);
    
    // 1. Chama a função para criar
    meu_vetor = cria_vetor(n);
    
    // 2. Pede os valores para o usuário
    printf("\nDigite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &meu_vetor[i]); // Lê e guarda direto na posição
    }
    
    // 3. Chama a função para imprimir
    imprime_vetor(meu_vetor, n);
    
    // 4. Chama a função para liberar
    libera_vetor(meu_vetor);
    
    return 0; // Fim
}