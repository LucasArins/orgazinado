#include <stdio.h>
#define TAMANHO 3
char tabuleiro[TAMANHO][TAMANHO];

void comecar_tabuleiro()
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            tabuleiro[i][j] = ' ';
        }
    }
}
void mostra_tabuleiro()
{
    printf("\n");
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            printf(" %c ", tabuleiro[i][j]);
            if (j < TAMANHO - 1)
                printf("|");
        }
        printf("\n");
        if (i < TAMANHO - 1)
            printf("------------\n");
    }
    printf("\n");   
}
void jogar(int linha, int coluna, char jogador)
{
    if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO)
    {
        if (tabuleiro[linha][coluna] == ' ')
        {
            tabuleiro[linha][coluna] = jogador;
        }
        else
        {
            printf("Posicao ja ocupada. Tente novamente.\n");
        }
    }
    else
    {
        printf("Posicao invalida. Tente novamente.\n");
    }
}
int verifica_vencedor()
{
    for (int i = 0; i < TAMANHO; i++)
    {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
        {
            return 1;
        }
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
        {
            return 1;
        }
    }
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
    {
        return 1;
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
    {
        return 1;
    }
    return 0;
}
int tabuleiro_cheio()
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (tabuleiro[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}
int main()
{
    int linha, coluna;
    char jogador = 'X';
    comecar_tabuleiro();

    printf("     ___  _______  _______  _______    ______   _______    __   __  _______  ___      __   __  _______\n");
    printf("    |   ||       ||       ||       |  |      | |   _   |  |  | |  ||       ||   |    |  | |  ||   _   |\n");
    printf("    |   ||   _   ||    ___||   _   |  |  _    ||  ||  |  |  ||  ||    ___||   |    |  ||  ||  ||  |\n");
    printf("    |   ||  | |  ||   | __ |  | |  |  | | |   ||       |  |       ||   |___ |   |    |       ||       |\n");
    printf("    |   ||  ||  ||   ||  ||  ||  |  | |_|   ||       |  |       ||    ___||   |___ |       ||       |\n");
    printf("   |    ||       ||   |_| ||       |  |       ||   _   |   |     | |   |___ |       ||   _   ||   _   |\n");
    printf("   |____||_______||_______||_______|  |______| |__| |__|    |___|  |_______||_______||__| |__||__| |__|\n");
    printf("\n");
    printf("Bem-vindo ao Jogo da Velha!\n");
    printf("\n");
    
    while (1)
    {
        mostra_tabuleiro();

        if (verifica_vencedor())
        {
            printf("Jogador %c venceu!\n", (jogador == 'X') ? 'O' : 'X'); // volta o jogador anterior
            break;
        }

        if (tabuleiro_cheio())
        {
            printf("Empate! O tabuleiro esta cheio.\n");
            break;
        }

        printf("Jogador %c, digite sua jogada (linha coluna ou -1 para sair): ", jogador);
        scanf("%d %d", &linha, &coluna);

        if (linha == -1 || coluna == -1)
        {
            printf("Jogo encerrado por escolha do jogador.\n");
            break;
        }
        linha--;
        coluna--;

        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO)
        {
            printf("Posição inválida! Tente novamente.\n");
            continue;
        }

        if (tabuleiro[linha][coluna] != ' ')
        {
            printf("Posição ocupada! Tente novamente.\n");
            continue;
        }

        tabuleiro[linha][coluna] = jogador;
        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    mostra_tabuleiro();
    return 0;
}
