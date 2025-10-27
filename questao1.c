/* * QUESTAO 01: AGENDA DE CONTATOS
 * Vamos incluir as bibliotecas que precisamos:
 * stdio.h - para ler (scanf) e escrever (printf)
 * stdlib.h - para alocar memória (malloc) e limpar a tela (system)
 * string.h - para comparar e copiar textos (strings)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---
// O enunciado pediu para criar uma estrutura para a Data
typedef struct {
    int dia;
    int mes;
} Data;

// E uma estrutura para o Contato
typedef struct {
    char nome[40];
    char telefone[15];
    char celular[15];
    char email[40];
    Data dataAniversario;
} Contato;

// E, finalmente, o "elo" da nossa corrente (lista)
// Cada elemento tem um Contato e um ponteiro para o próximo
typedef struct elemento {
    Contato info; // Os dados do contato
    struct elemento* prox; // Onde está o próximo?
} Elemento;


// --- FUNÇÕES ---

// 1. cria_agenda
// Apenas cria uma lista vazia, que é representada por NULL (nada)
Elemento* cria_agenda() {
    return NULL;
}

// Função auxiliar para limpar o "enter" que fica no teclado
// Depois de ler um número, o "enter" ( \n ) fica sobrando.
// Usamos isso para limpar e não atrapalhar a leitura de texto.
void limparBufferTeclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 2. insere_contato
// Insere um novo contato no FIM da lista
Elemento* insere_contato(Elemento* lista) {
    // 1. Alocar espaço na memória para o novo "elo"
    Elemento* novo_elemento = (Elemento*) malloc(sizeof(Elemento));
    
    // 2. Pedir os dados do usuário
    printf("\n--- Novo Contato ---\n");
    printf("Nome: ");
    // " %39[^\n]" lê até 39 caracteres ou até o usuário apertar ENTER
    // O espaço no começo ignora "enters" que sobraram de antes
    scanf(" %39[^\n]", novo_elemento->info.nome); 
    
    printf("Telefone: ");
    scanf(" %14[^\n]", novo_elemento->info.telefone);
    
    printf("Celular: ");
    scanf(" %14[^\n]", novo_elemento->info.celular);
    
    printf("Email: ");
    scanf(" %39[^\n]", novo_elemento->info.email);
    
    printf("Aniversario (DD MM): ");
    scanf("%d %d", &novo_elemento->info.dataAniversario.dia, &novo_elemento->info.dataAniversario.mes);
    
    // 3. O novo "elo" será o último, então ele aponta para NADA (NULL)
    novo_elemento->prox = NULL;
    
    // 4. Ligar o novo "elo" na lista
    
    // Se a lista está vazia, o novo elemento é o começo da lista
    if (lista == NULL) {
        printf("Contato salvo!\n");
        return novo_elemento; 
    }
    
    // Se a lista NÃO está vazia, temos que andar até o fim
    Elemento* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox; // Vai para o próximo
    }
    
    // 'atual' agora é o último. Fazemos ele apontar para o novo.
    atual->prox = novo_elemento;
    
    printf("Contato salvo!\n");
    return lista; // O começo da lista não mudou
}

// 3. lista_contatos
// Exibe todos os contatos
void lista_contatos(Elemento* lista) {
    // Se a lista está vazia
    if (lista == NULL) {
        printf("\nAgenda vazia.\n");
        return; // Sai da função
    }
    
    Elemento* atual = lista; // Começa pelo primeiro
    
    printf("\n--- Lista de Contatos ---\n");
    // "while (atual != NULL)" significa "enquanto eu não chegar no fim"
    while (atual != NULL) {
        // Imprime os dados do contato atual
        printf("Nome: %s\n", atual->info.nome);
        printf("Telefone: %s\n", atual->info.telefone);
        printf("Celular: %s\n", atual->info.celular);
        printf("Email: %s\n", atual->info.email);
        printf("Aniversario: %d/%d\n", atual->info.dataAniversario.dia, atual->info.dataAniversario.mes);
        printf("---------------------------\n");
        
        // Vai para o próximo contato
        atual = atual->prox; 
    }
}

// 4. busca_contato
// Procura um contato pelo nome
Elemento* busca_contato(Elemento* lista, char* nome_busca) {
    Elemento* atual = lista; // Começa pelo primeiro
    
    // Enquanto não chegar no fim
    while (atual != NULL) {
        // "strcmp" compara duas strings. Se forem iguais, retorna 0.
        if (strcmp(atual->info.nome, nome_busca) == 0) {
            // Achamos! Retorna o endereço de memória do "elo"
            return atual;
        }
        // Se não achou, vai para o próximo
        atual = atual->prox;
    }
    
    // Se saiu do "while", é porque não achou ninguém.
    return NULL; 
}

// 5. remove_contato
// Deleta um contato da lista
// (Essa é a mais complicadinha, pois temos que "ligar" o elo anterior ao próximo)
Elemento* remove_contato(Elemento* lista) {
    char nome_busca[40];
    printf("\nQual nome deseja remover? ");
    scanf(" %39[^\n]", nome_busca);
    
    Elemento* anterior = NULL;   // O elo anterior
    Elemento* atual = lista; // O elo que estamos olhando
    
    // 1. Anda pela lista procurando o nome
    while (atual != NULL && strcmp(atual->info.nome, nome_busca) != 0) {
        anterior = atual;       // Guarda o anterior
        atual = atual->prox;    // Anda para o próximo
    }
    
    // 2. Se 'atual' é NULL, o nome não foi encontrado
    if (atual == NULL) {
        printf("Erro: Contato '%s' nao encontrado.\n", nome_busca);
        return lista; // A lista não muda
    }
    
    // 3. Se achou, vamos remover!
    
    // Caso 1: O contato a remover é o PRIMEIRO da lista
    if (anterior == NULL) {
        lista = atual->prox; // O começo da lista agora é o segundo
    } 
    // Caso 2: O contato está no meio ou no fim
    else {
        // Faz o anterior "pular" o atual e apontar para o próximo
        anterior->prox = atual->prox;
    }
    
    // 4. Apaga o contato da memória (para não vazar memória)
    free(atual);
    printf("Contato '%s' removido com sucesso!\n", nome_busca);
    
    return lista; // Retorna o novo começo da lista (pode ter mudado)
}

// 6. atualiza_contato
// Edita os dados de um contato
void atualiza_contato(Elemento* lista) {
    char nome_busca[40];
    printf("\nQual nome deseja editar? ");
    scanf(" %39[^\n]", nome_busca);
    
    // Usa a função que já criamos para buscar
    Elemento* contato_encontrado = busca_contato(lista, nome_busca);
    
    // Se não achou...
    if (contato_encontrado == NULL) {
        printf("Erro: Contato '%s' nao encontrado.\n", nome_busca);
        return; // Sai da função
    }
    
    // Se achou, pede todos os dados de novo
    printf("Editando contato: %s\n", contato_encontrado->info.nome);
    printf("Novo Nome: ");
    scanf(" %39[^\n]", contato_encontrado->info.nome);
    
    printf("Novo Telefone: ");
    scanf(" %14[^\n]", contato_encontrado->info.telefone);
    
    printf("Novo Celular: ");
    scanf(" %14[^\n]", contato_encontrado->info.celular);
    
    printf("Novo Email: ");
    scanf(" %39[^\n]", contato_encontrado->info.email);
    
    printf("Novo Aniversario (DD MM): ");
    scanf("%d %d", &contato_encontrado->info.dataAniversario.dia, &contato_encontrado->info.dataAniversario.mes);
    
    printf("Contato atualizado com sucesso!\n");
}


// --- FUNÇÃO PRINCIPAL (main) ---
// Onde o programa realmente começa
int main() {
    Elemento* minha_agenda = cria_agenda(); // Cria a lista vazia
    int opcao = 0;
    
    // "do-while" faz o menu repetir até o usuário escolher 6 (Sair)
    do {
        // 1. Mostra o menu
        printf("\n--- AGENDA TELEFONICA ---\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Remover Contato\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        
        // 2. Lê a escolha
        scanf("%d", &opcao);
        limparBufferTeclado(); // Limpa o "enter" que sobrou

        // 3. "switch" decide o que fazer
        switch(opcao) {
            case 1:
                // Como 'insere_contato' pode mudar o começo da lista
                // (se ela estiver vazia), guardamos o resultado de volta.
                minha_agenda = insere_contato(minha_agenda);
                break;
            
            case 2:
                lista_contatos(minha_agenda);
                break;
                
            case 3: { // Chaves {} são necessárias para declarar variáveis dentro do case
                char nome_busca[40];
                printf("Qual nome deseja buscar? ");
                scanf(" %39[^\n]", nome_busca);
                
                Elemento* contato_encontrado = busca_contato(minha_agenda, nome_busca);
                
                if (contato_encontrado != NULL) {
                    printf("\n--- Contato Encontrado ---\n");
                    printf("Nome: %s\n", contato_encontrado->info.nome);
                    printf("Telefone: %s\n", contato_encontrado->info.telefone);
                    printf("Celular: %s\n", contato_encontrado->info.celular);
                    // ... (pode imprimir o resto se quiser)
                } else {
                    printf("Contato '%s' nao encontrado.\n", nome_busca);
                }
                break;
            }
                
            case 4:
                atualiza_contato(minha_agenda);
                break;
                
            case 5:
                // 'remove_contato' também pode mudar o começo da lista
                minha_agenda = remove_contato(minha_agenda);
                break;
                
            case 6:
                printf("Saindo... Tchau!\n");
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 6) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Pausa o programa
        }
        
    } while (opcao != 6);
    
    // (O certo seria liberar toda a memória da lista aqui antes de sair,
    // mas para um iniciante, focar nas funções pedidas é o principal)

    return 0; // Fim do programa
}