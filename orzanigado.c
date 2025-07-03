/*
 * ===================================
 *          JOGO DA VELHA
 * ===================================
 * Um simples jogo da velha para 2 jogadores
 * Implementado em C
 */

#include <stdio.h>
#include <stdlib.h>

// ===================================
//           CONSTANTES
// ===================================
#define TAMANHO 3
#define JOGADOR_X 'X'
#define JOGADOR_O 'O'
#define ESPACO_VAZIO ' '
#define SAIR -1

// ===================================
//        VARIÁVEIS GLOBAIS
// ===================================
char tabuleiro[TAMANHO][TAMANHO];

// ===================================
//      PROTÓTIPOS DAS FUNÇÕES
// ===================================
void exibir_titulo(void);
void inicializar_tabuleiro(void);
void exibir_tabuleiro(void);
void exibir_instrucoes(void);
int realizar_jogada(int linha, int coluna, char jogador);
int verificar_vencedor(void);
int tabuleiro_completo(void);
char alternar_jogador(char jogador_atual);
void processar_jogo(void);

// ===================================
//      IMPLEMENTAÇÃO DAS FUNÇÕES
// ===================================

/**
 * Exibe o título do jogo com arte ASCII
 */
void exibir_titulo(void) {
    printf("\n");
    printf("     ___  _______  _______  _______    ______   _______    __   __  _______  ___      __   __  _______\n");
    printf("    |   ||       ||       ||       |  |      | |   _   |  |  | |  ||       ||   |    |  | |  ||   _   |\n");
    printf("    |   ||   _   ||    ___||   _   |  |  _    ||  ||  |  |  ||  ||    ___||   |    |  ||  ||  ||  |\n");
    printf("    |   ||  | |  ||   | __ |  | |  |  | | |   ||       |  |       ||   |___ |   |    |       ||       |\n");
    printf("    |   ||  ||  ||   ||  ||  ||  |  | |_|   ||       |  |       ||    ___||   |___ |       ||       |\n");
    printf("   |    ||       ||   |_| ||       |  |       ||   _   |   |     | |   |___ |       ||   _   ||   _   |\n");
    printf("   |____||_______||_______||_______|  |______| |__| |__|    |___|  |_______||_______||__| |__||__| |__|\n");
    printf("\n");
    printf("                                   Bem-vindo ao Jogo da Velha!\n");
    printf("                                   ========================\n\n");
}

/**
 * Inicializa o tabuleiro com espaços vazios
 */
void inicializar_tabuleiro(void) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = ESPACO_VAZIO;
        }
    }
}

/**
 * Exibe o tabuleiro atual na tela
 */
void exibir_tabuleiro(void) {
    printf("\n   Posições:        Tabuleiro:\n");
    printf("   1 | 2 | 3        ");
    
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < TAMANHO - 1) printf("|");
        }
        printf("\n");
        
        if (i < TAMANHO - 1) {
            printf("   ---------        -----------\n");
            printf("   %d | %d | %d        ", (i+1)*3+1, (i+1)*3+2, (i+1)*3+3);
        }
    }
    printf("\n");
}

/**
 * Exibe as instruções do jogo
 */
void exibir_instrucoes(void) {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║              INSTRUÇÕES               ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ • Digite linha e coluna (1-3)         ║\n");
    printf("║ • Exemplo: '1 2' para primeira linha, ║\n");
    printf("║   segunda coluna                      ║\n");
    printf("║ • Digite '-1 -1' para sair do jogo    ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

/**
 * Realiza uma jogada no tabuleiro
 * @param linha Linha da jogada (0-2)
 * @param coluna Coluna da jogada (0-2)
 * @param jogador Símbolo do jogador ('X' ou 'O')
 * @return 1 se a jogada foi válida, 0 caso contrário
 */
int realizar_jogada(int linha, int coluna, char jogador) {
    // Verifica se a posição está dentro dos limites
    if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
        printf("❌ Posição inválida! Use valores entre 1 e 3.\n");
        return 0;
    }
    
    // Verifica se a posição está livre
    if (tabuleiro[linha][coluna] != ESPACO_VAZIO) {
        printf("❌ Posição já ocupada! Escolha outra posição.\n");
        return 0;
    }
    
    // Realiza a jogada
    tabuleiro[linha][coluna] = jogador;
    return 1;
}

/**
 * Verifica se há um vencedor no jogo
 * @return 1 se há vencedor, 0 caso contrário
 */
int verificar_vencedor(void) {
    // Verifica linhas e colunas
    for (int i = 0; i < TAMANHO; i++) {
        // Verifica linha
        if (tabuleiro[i][0] == tabuleiro[i][1] && 
            tabuleiro[i][1] == tabuleiro[i][2] && 
            tabuleiro[i][0] != ESPACO_VAZIO) {
            return 1;
        }
        
        // Verifica coluna
        if (tabuleiro[0][i] == tabuleiro[1][i] && 
            tabuleiro[1][i] == tabuleiro[2][i] && 
            tabuleiro[0][i] != ESPACO_VAZIO) {
            return 1;
        }
    }
    
    // Verifica diagonal principal
    if (tabuleiro[0][0] == tabuleiro[1][1] && 
        tabuleiro[1][1] == tabuleiro[2][2] && 
        tabuleiro[0][0] != ESPACO_VAZIO) {
        return 1;
    }
    
    // Verifica diagonal secundária
    if (tabuleiro[0][2] == tabuleiro[1][1] && 
        tabuleiro[1][1] == tabuleiro[2][0] && 
        tabuleiro[0][2] != ESPACO_VAZIO) {
        return 1;
    }
    
    return 0;
}

/**
 * Verifica se o tabuleiro está completamente preenchido
 * @return 1 se está completo, 0 caso contrário
 */
int tabuleiro_completo(void) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == ESPACO_VAZIO) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Alterna entre os jogadores X e O
 * @param jogador_atual Jogador atual
 * @return Próximo jogador
 */
char alternar_jogador(char jogador_atual) {
    return (jogador_atual == JOGADOR_X) ? JOGADOR_O : JOGADOR_X;
}

/**
 * Processa o loop principal do jogo
 */
void processar_jogo(void) {
    int linha, coluna;
    char jogador_atual = JOGADOR_X;
    int jogada_valida;
    
    while (1) {
        exibir_tabuleiro();
        
        // Verifica se há vencedor
        if (verificar_vencedor()) {
            char vencedor = alternar_jogador(jogador_atual);
            printf("\n🎉 PARABÉNS! Jogador %c venceu! 🎉\n", vencedor);
            break;
        }
        
        // Verifica empate
        if (tabuleiro_completo()) {
            printf("\n🤝 Empate! O tabuleiro está completo. 🤝\n");
            break;
        }
        
        // Solicita jogada do jogador atual
        printf("Jogador %c, digite sua jogada (linha coluna): ", jogador_atual);
        
        if (scanf("%d %d", &linha, &coluna) != 2) {
            printf("❌ Entrada inválida! Digite dois números.\n");
            // Limpa o buffer
            while (getchar() != '\n');
            continue;
        }
        
        // Verifica se o jogador quer sair
        if (linha == SAIR || coluna == SAIR) {
            printf("👋 Jogo encerrado por escolha do jogador.\n");
            break;
        }
        
        // Converte para índices de array (0-2)
        linha--;
        coluna--;
        
        // Tenta realizar a jogada
        jogada_valida = realizar_jogada(linha, coluna, jogador_atual);
        
        if (jogada_valida) {
            jogador_atual = alternar_jogador(jogador_atual);
        }
    }
}

// ===================================
//          FUNÇÃO PRINCIPAL
// ===================================

/**
 * Função principal do programa
 */
int main(void) {
    // Exibe título e instruções
    exibir_titulo();
    exibir_instrucoes();
    
    // Inicializa o tabuleiro
    inicializar_tabuleiro();
    
    // Inicia o jogo
    processar_jogo();
    
    // Exibe tabuleiro final
    exibir_tabuleiro();
    
    printf("\nObrigado por jogar! 🎮\n");
    
    return 0;
}
