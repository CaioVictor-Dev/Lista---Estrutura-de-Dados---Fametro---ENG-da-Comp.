/*
 * QUESTAO 03: AVALIADOR RPN (PILHA)
 * Bibliotecas necessárias:
 * stdio.h - I/O
 * stdlib.h - malloc, free, atof (converte string para double), exit
 * string.h - strtok (divide string), strcmp (compara string)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS DA PILHA ---

// O "elo" da nossa pilha (um prato)
typedef struct node {
    double value; // O número que ele guarda
    struct node* prox; // O prato de baixo
} Node;

// O controlador da pilha (a pilha inteira)
typedef struct {
    Node* topo; // Quem está no topo?
} Stack;


// --- FUNÇÕES DA PILHA ---

// 1. createStack
// Cria uma pilha nova e vazia
Stack* createStack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->topo = NULL; // Topo aponta para nada (vazio)
    return stack;
}

// 2. isEmpty
// Verifica se a pilha está vazia
int isEmpty(Stack* stack) {
    if (stack->topo == NULL) {
        return 1; // 1 = Verdadeiro (está vazia)
    } else {
        return 0; // 0 = Falso (tem coisa)
    }
    // (Poderia ser "return stack->topo == NULL;")
}

// 3. push
// Coloca um valor no topo da pilha
void push(Stack* stack, double value) {
    // 1. Cria um novo "elo" (prato)
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    
    // 2. O prato de baixo ("prox") é o antigo topo
    new_node->prox = stack->topo;
    
    // 3. O novo topo é o novo "elo"
    stack->topo = new_node;
}

// 4. pop
// Remove e retorna o valor do topo
// O enunciado pede para terminar o programa se tentar tirar de uma pilha vazia
double pop(Stack* stack) {
    // 1. Verifica se está vazia
    if (isEmpty(stack)) {
        printf("Erro: Tentativa de pop em pilha vazia (expressao malformada).\n");
        exit(1); // Aborta o programa
    }
    
    // 2. Guarda quem é o topo atual
    Node* temp = stack->topo;
    double valor_retorno = temp->value;
    
    // 3. O topo agora é o de baixo
    stack->topo = temp->prox;
    
    // 4. Libera o topo antigo da memória
    free(temp);
    
    // 5. Retorna o valor
    return valor_retorno;
}

// 5. freeStack
// Libera toda a memória da pilha
void freeStack(Stack* stack) {
    // Enquanto a pilha não estiver vazia, joga fora o prato do topo
    while (!isEmpty(stack)) {
        pop(stack); // A função 'pop' já faz o 'free' do 'Node'
    }
    // No final, libera a estrutura da pilha em si
    free(stack);
}


// --- O AVALIADOR ---

// A função principal da lógica
double evaluateRPN(char* expression) {
    // 1. Cria a pilha
    Stack* pilha = createStack();
    
    // 2. "strtok" é uma função que quebra a string em "tokens"
    // Vamos quebrar usando o espaço " " como separador
    // "10 5 +" vira "10", depois "5", depois "+"
    char* token = strtok(expression, " ");
    
    // 3. Loop "enquanto houver tokens (pedaços)"
    while (token != NULL) {
        
        // 4. Verifica se o token é um operador
        // "strcmp" compara duas strings. Retorna 0 se forem iguais.
        if (strcmp(token, "+") == 0) {
            // Operador +
            // (A ordem importa: o segundo operando é o primeiro a sair)
            double val2 = pop(pilha);
            double val1 = pop(pilha);
            push(pilha, val1 + val2); // Empilha o resultado
            
        } else if (strcmp(token, "-") == 0) {
            // Operador -
            double val2 = pop(pilha);
            double val1 = pop(pilha);
            push(pilha, val1 - val2); // (val1 - val2)
            
        } else if (strcmp(token, "*") == 0) {
            // Operador *
            double val2 = pop(pilha);
            double val1 = pop(pilha);
            push(pilha, val1 * val2);
            
        } else if (strcmp(token, "/") == 0) {
            // Operador /
            double val2 = pop(pilha);
            double val1 = pop(pilha);
            
            // Tratamento de erro: Divisão por zero
            if (val2 == 0) {
                printf("Erro: Tentativa de divisao por zero.\n");
                exit(1); // Aborta
            }
            push(pilha, val1 / val2);
            
        } else {
            // 5. Se não é um operador, é um NÚMERO
            // "atof" converte uma string (ex: "12.5") para double (12.5)
            double valor = atof(token);
            push(pilha, valor); // Empilha o número
        }
        
        // 6. Pega o próximo "pedaço" (token) da string
        token = strtok(NULL, " ");
    }
    
    // 7. No final, o resultado final deve ser a única coisa na pilha
    double resultado_final = pop(pilha);
    
    // 8. Se a pilha não ficou vazia, a expressão estava errada
    if (!isEmpty(pilha)) {
        printf("Erro: Expressao malformada (operandos demais).\n");
        exit(1);
    }
    
    // 9. Libera a memória da pilha
    freeStack(pilha);
    
    // 10. Retorna o resultado
    return resultado_final;
}


// --- FUNÇÃO PRINCIPAL (main) ---
// 'argc' é a contagem de argumentos
// 'argv' são os argumentos (um vetor de strings)
// Ex: ./avaliador "10 5 +"
// argc = 2
// argv[0] = "./avaliador"
// argv[1] = "10 5 +"
int main(int argc, char* argv[]) {
    
    // Verifica se o usuário passou exatamente 1 argumento (a expressão)
    if (argc != 2) {
        printf("Erro: Use o formato: %s \"<expressao>\"\n", argv[0]);
        printf("Exemplo: %s \"10 5 +\"\n", argv[0]);
        return 1; // Retorna 1 (código de erro)
    }
    
    // argv[1] é a string da expressão, ex: "10 5 +"
    // (Copiamos para uma variável nova, pois 'strtok' modifica a string)
    char expressao[256];
    strcpy(expressao, argv[1]);
    
    // Chama a função principal
    double resultado = evaluateRPN(expressao);
    
    // Imprime o resultado formatado com 2 casas decimais
    printf("Resultado: %.2f\n", resultado);
    
    return 0; // Sucesso
}