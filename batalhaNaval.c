#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAMANHO_HABILIDADE 5

// Estrutura para representar uma habilidade
typedef struct {
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    char nome[20];
} Habilidade;

// Funções para inicialização
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void inicializarHabilidadeCone(Habilidade *habilidade) {
    strcpy(habilidade->nome, "Cone");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria um padrão de cone apontando para baixo
            if (i >= j && i + j >= TAMANHO_HABILIDADE - 1) {
                habilidade->matriz[i][j] = 1;
            } else {
                habilidade->matriz[i][j] = 0;
            }
        }
    }
}

void inicializarHabilidadeCruz(Habilidade *habilidade) {
    strcpy(habilidade->nome, "Cruz");
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria um padrão de cruz
            if (i == centro || j == centro) {
                habilidade->matriz[i][j] = 1;
            } else {
                habilidade->matriz[i][j] = 0;
            }
        }
    }
}

void inicializarHabilidadeOctaedro(Habilidade *habilidade) {
    strcpy(habilidade->nome, "Octaedro");
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria um padrão de losango (octaedro visto de frente)
            int dist_centro_i = abs(i - centro);
            int dist_centro_j = abs(j - centro);
            if (dist_centro_i + dist_centro_j <= centro) {
                habilidade->matriz[i][j] = 1;
            } else {
                habilidade->matriz[i][j] = 0;
            }
        }
    }
}

// Função para posicionar navios (simplificada para o exemplo)
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio horizontal
    for (int j = 2; j < 5; j++) tabuleiro[2][j] = NAVIO;
    
    // Navio vertical
    for (int i = 5; i < 8; i++) tabuleiro[i][7] = NAVIO;
    
    // Navio diagonal principal
    for (int i = 0; i < 3; i++) tabuleiro[i][i] = NAVIO;
    
    // Navio diagonal secundária
    for (int i = 0; i < 3; i++) tabuleiro[i][9-i] = NAVIO;
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      Habilidade habilidade, int centro_x, int centro_y) {
    int offset = TAMANHO_HABILIDADE / 2;
    
    printf("\nAplicando habilidade %s em (%d,%d):\n", habilidade.nome, centro_x, centro_y);
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int tab_x = centro_x - offset + i;
            int tab_y = centro_y - offset + j;
            
            // Verifica se está dentro do tabuleiro
            if (tab_x >= 0 && tab_x < TAMANHO_TABULEIRO && 
                tab_y >= 0 && tab_y < TAMANHO_TABULEIRO) {
                
                // Se a posição na matriz de habilidade for 1, marca no tabuleiro
                if (habilidade.matriz[i][j] == 1) {
                    tabuleiro[tab_x][tab_y] = HABILIDADE;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) printf("%2d ", j);
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch(tabuleiro[i][j]) {
                case AGUA: printf(" . "); break;
                case NAVIO: printf(" N "); break;
                case HABILIDADE: printf(" X "); break;
                default: printf(" ? ");
            }
        }
        printf("\n");
    }
}

// Função para exibir uma matriz de habilidade
void exibirHabilidade(Habilidade habilidade) {
    printf("\nPadrao da habilidade %s:\n", habilidade.nome);
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade.matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    
    printf("BATALHA NAVAL - HABILIDADES ESPECIAIS\n");
    printf("-------------------------------------\n");
    
    // Cria as habilidades
    Habilidade cone, cruz, octaedro;
    inicializarHabilidadeCone(&cone);
    inicializarHabilidadeCruz(&cruz);
    inicializarHabilidadeOctaedro(&octaedro);
    
    // Exibe os padrões das habilidades
    exibirHabilidade(cone);
    exibirHabilidade(cruz);
    exibirHabilidade(octaedro);
    
    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 3, 3);    // Cone no centro
    aplicarHabilidade(tabuleiro, cruz, 7, 2);    // Cruz perto da borda
    aplicarHabilidade(tabuleiro, octaedro, 5, 5); // Octaedro no centro
    
    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
