#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX 25
#define MAX_MONSTROS 10

const char *MAPA_VILA[10] = {
    "**********",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "* N      *",
    "*        *",
    "*        *",
    "*      L *",
    "**********"
};

const char *MAPA_ANDAR1[10] = {
    "**********",
    "* kkk    *",
    "* kk     *",
    "*        *",
    "* #      *",
    "* #      *",
    "*       @*",
    "*    ***",
    "* D    L *",
    "**********"
};

const char *MAPA_ANDAR2[15] = {
    "***************",
    "* ##       O  *",
    "*             *",
    "*             *",
    "*             *",
    "* #           *",
    "* ##         @*",
    "* #           *",
    "* ###         *",
    "*             *",
    "*****D*********",
    "*   *         *",
    "*   *    *****",
    "*@  * D     L*",
    "***************"
};

const char *MAPA_ANDAR3[25] = {
    "*************************",
    "* ##                    *",
    "*                       *",
    "* ###                   *",
    "* #       @             *",
    "*                       *",
    "*                       *",
    "*                       *",
    "* ##     ****           *",
    "* D                    @*",
    "*******D*** #       ****",
    "*   *                   *",
    "*   ***************     *",
    "*   *                   *",
    "*   @                   *",
    "* ###                   *",
    "* ##                    *",
    "* #                     *",
    "*****D*******************",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*                       *",
    "*************************"
};

char terreno[MAX][MAX];
int altura, largura;
int jogador_linha = 1, jogador_coluna = 1; 
char jogador_dir = '>'; 
int arma = 0; 
int tem_chave = 0;   
int vidas = 3;   

int boss_vida = 3;
int boss_linha = 21;
int boss_coluna = 12;
int boss_vivo = 1;

int monstro_linha[MAX_MONSTROS];
int monstro_coluna[MAX_MONSTROS];
int monstro_tipo[MAX_MONSTROS];
int monstro_vivo[MAX_MONSTROS];
int num_monstros = 0;

void carregar_monstros(int andar) {
    num_monstros = 0;
    int i;
    
    for(i = 0; i < MAX_MONSTROS; i++) {
        monstro_vivo[i] = 0;
    }

    if (andar == 1) {
        monstro_linha[0] = 3; monstro_coluna[0] = 7; monstro_tipo[0] = 1; monstro_vivo[0] = 1;
        monstro_linha[1] = 5; monstro_coluna[1] = 3; monstro_tipo[1] = 1; monstro_vivo[1] = 1;
        num_monstros = 2;
    }
    else if (andar == 2) {
        monstro_linha[0] = 4; monstro_coluna[0] = 6;  monstro_tipo[0] = 1; monstro_vivo[0] = 1;
        monstro_linha[1] = 7; monstro_coluna[1] = 4;  monstro_tipo[1] = 2; monstro_vivo[1] = 1;
        monstro_linha[2] = 11; monstro_coluna[2] = 6;  monstro_tipo[2] = 1; monstro_vivo[2] = 1;
        num_monstros = 3;
    }
    else if (andar == 3) {
        monstro_linha[0] = 5;  monstro_coluna[0] = 10;  monstro_tipo[0] = 2; monstro_vivo[0] = 1;
        monstro_linha[1] = 14; monstro_coluna[1] = 8;   monstro_tipo[1] = 2; monstro_vivo[1] = 1;
        num_monstros = 2;
    }
}

int atacar_monstros(int alvo_linha, int alvo_coluna) {
    int m;
 
    if (boss_vivo && boss_linha == alvo_linha && boss_coluna == alvo_coluna) {
        boss_vida--;
        if (boss_vida <= 0) {
            boss_vivo = 0;
            return 1; 
        }
        return 0;
    }
    
    for (m = 0; m < num_monstros; m++) {
        if (monstro_vivo[m] && monstro_linha[m] == alvo_linha && monstro_coluna[m] == alvo_coluna) {
            monstro_vivo[m] = 0; 
            return 0;
        }
    }
    return 0;   
}

void carregar_andar(int andar) {
    int i, j;
    
    if (andar == 0)      { altura = 10; largura = 10; } 
    else if (andar == 1) { altura = 10; largura = 10; } 
    else if (andar == 2) { altura = 15; largura = 15; } 
    else                 { altura = 25; largura = 25; } 

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            if (andar == 0)      terreno[i][j] = MAPA_VILA[i][j];
            else if (andar == 1) terreno[i][j] = MAPA_ANDAR1[i][j];
            else if (andar == 2) terreno[i][j] = MAPA_ANDAR2[i][j];
            else                 terreno[i][j] = MAPA_ANDAR3[i][j];
        }
    }

    jogador_linha = 1;                                 
    jogador_coluna = 1;                                
    jogador_dir = '>';                                 
    tem_chave = 0;

    carregar_monstros(andar);                          
}

void desenhar_mapa(int andar) { 
    system("cls");
    int i, j, m;
    char caractere_impressao;

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            caractere_impressao = terreno[i][j];

            if (i == jogador_linha && j == jogador_coluna) {
                caractere_impressao = jogador_dir;
            }
            
            for (m = 0; m < num_monstros; m++) {
                if (monstro_vivo[m] && monstro_linha[m] == i && monstro_coluna[m] == j) {
                    if (monstro_tipo[m] == 1) caractere_impressao = 'X';
                    else                      caractere_impressao = 'Y';
                }
            }
          
            if (andar == 3 && boss_vivo && i == boss_linha && j == boss_coluna) {
                caractere_impressao = 'Z'; 
            }

            printf("%c", caractere_impressao);
        }
        printf("\n");
    }
    
    printf("\nVidas: %d | Chave: %s | Arma: ", vidas, tem_chave ? "Sim" : "Nao");
    if (arma == 1)      printf("Espada\n");
    else if (arma == 2) printf("Arco\n");
    else if (arma == 3) printf("Cajado\n");
    else                printf("Nenhuma\n");   
    
    if (andar == 3 && boss_vivo) {
        printf("CHEFAO: Gorgoroth, o Tita de Ferro (Z) | VIDA: %d/3\n", boss_vida);
    }
}

int mover(int dx, int dy, char dir) {
    jogador_dir = dir;
    int novo_linha = jogador_linha + dy;
    int novo_coluna = jogador_coluna + dx;

    if (novo_linha < 0 || novo_linha >= altura || novo_coluna < 0 || novo_coluna >= largura) {
        return 0;
    }

    char celula_destino = terreno[novo_linha][novo_coluna];

    if (celula_destino != '*' && celula_destino != 'N' && celula_destino != 'L' &&
        celula_destino != 'k' && celula_destino != 'D' && celula_destino != 'O') {
        
        jogador_coluna = novo_coluna;
        jogador_linha = novo_linha;

        if (terreno[jogador_linha][jogador_coluna] == '#') {  
            return 1; 
        }
    }
    return 0;   
}

int interagir(void) { 
    int frente_linha = jogador_linha;
    int frente_coluna = jogador_coluna;

    if (jogador_dir == '^')      frente_linha--;
    else if (jogador_dir == 'v') frente_linha++;
    else if (jogador_dir == '<') frente_coluna--;
    else if (jogador_dir == '>') frente_coluna++;

    char alvo = terreno[frente_linha][frente_coluna];

    if (alvo == 'N') {
        int escolha = 0;
        while (escolha < 1 || escolha > 3) { 
            printf("\n1 - Espada\n2 - Arco\n3 - Cajado\nEscolha: ");
            escolha = getch() - '0';
        }
        arma = escolha; 
        return 0;       
    }
    else if (alvo == 'L') {
        return 1; 
    }
    else if (alvo == '@') {   
        terreno[frente_linha][frente_coluna] = ' ';   
        tem_chave = 1;
        return 0;
    }
    else if (alvo == 'D') {   
        if (tem_chave == 1) {
            terreno[frente_linha][frente_coluna] = ' ';   
            tem_chave = 0;                                 
        }
        return 0;
    }
    else if (alvo == 'O') {   
        terreno[12][4] = ' ';   
        return 0;
    }
    return 0;   
}

int atacar(void) {
    int dl, dc; 

    if (arma == 1) {   
        for (dl = 1; dl <= 2; dl++) {          
            for (dc = -1; dc <= 1; dc++) {     
                int alvo_linha = jogador_linha, alvo_coluna = jogador_coluna;
                if (jogador_dir == '^')      { alvo_linha = jogador_linha - dl; alvo_coluna = jogador_coluna + dc; }
                else if (jogador_dir == 'v') { alvo_linha = jogador_linha + dl; alvo_coluna = jogador_coluna + dc; }
                else if (jogador_dir == '<') { alvo_linha = jogador_linha + dc; alvo_coluna = jogador_coluna - dl; }
                else                         { alvo_linha = jogador_linha + dc; alvo_coluna = jogador_coluna + dl; }

                if (terreno[alvo_linha][alvo_coluna] == 'k') terreno[alvo_linha][alvo_coluna] = ' ';
                if (atacar_monstros(alvo_linha, alvo_coluna) == 1) return 1;   
            }
        }
    }   
    else if (arma == 2) {   
        for (dl = 1; dl <= 4; dl++) {
            int alvo_linha = jogador_linha, alvo_coluna = jogador_coluna;  
            if (jogador_dir == '^')      alvo_linha  -= dl;   
            else if (jogador_dir == 'v') alvo_linha  += dl;   
            else if (jogador_dir == '<') alvo_coluna -= dl;   
            else                         alvo_coluna += dl;   

            if (terreno[alvo_linha][alvo_coluna] == 'k') terreno[alvo_linha][alvo_coluna] = ' ';
            if (atacar_monstros(alvo_linha, alvo_coluna) == 1) return 1;   
        }
    }
    else if (arma == 3) {   
        for (dl = -1; dl <= 1; dl++) {
            for (dc = -1; dc <= 1; dc++) {
                if (dl == 0 && dc == 0) continue;   
                int alvo_linha = jogador_linha + dl;
                int alvo_coluna = jogador_coluna + dc;

                if (terreno[alvo_linha][alvo_coluna] == 'k') terreno[alvo_linha][alvo_coluna] = ' ';   
                if (atacar_monstros(alvo_linha, alvo_coluna) == 1) return 1;   
            }
        }
    }
    return 0;   
}

int mover_monstros(int andar) {
    int i;
    
  
    for (i = 0; i < num_monstros; i++) {
        if (monstro_vivo[i] == 0) continue;

        int nova_linha  = monstro_linha[i];
        int nova_coluna = monstro_coluna[i];

        if (monstro_tipo[i] == 1) {            
            int dir = rand() % 4;
            if      (dir == 0) nova_linha--;
            else if (dir == 1) nova_linha++;
            else if (dir == 2) nova_coluna--;
            else               nova_coluna++;
        }
        else if (monstro_tipo[i] == 2) {       
            int dl_real = jogador_linha  - monstro_linha[i];
            int dc_real = jogador_coluna - monstro_coluna[i];
            
            if (abs(dl_real) >= abs(dc_real)) {
                if (dl_real > 0) nova_linha++; else nova_linha--;
            } else {
                if (dc_real > 0) nova_coluna++; else nova_coluna--;
            }
        }

        char destino = terreno[nova_linha][nova_coluna];
        if (destino == '*' || destino == 'N' || destino == 'L' || destino == 'k' || destino == 'D') continue;

        if (nova_linha == jogador_linha && nova_coluna == jogador_coluna) return 1;   

        monstro_linha[i]  = nova_linha;
        monstro_coluna[i] = nova_coluna;
    }

    if (andar == 3 && boss_vivo) {
        if (jogador_linha >= 19) { 
            int dl = jogador_linha  - boss_linha;
            int dc = jogador_coluna - boss_coluna;

            int n_boss_l = boss_linha;
            int n_boss_c = boss_coluna;

            if (abs(dl) >= abs(dc)) {
                if (dl > 0) n_boss_l++; else n_boss_l--;
            } else {
                if (dc > 0) n_boss_c++; else n_boss_c--;
            }

            char dest_boss = terreno[n_boss_l][n_boss_c];
            if (dest_boss != '*' && dest_boss != 'D') {
                boss_linha = n_boss_l;
                boss_coluna = n_boss_c;
            }

            if (boss_linha == jogador_linha && boss_coluna == jogador_coluna) {
                return 1; 
            }
        }
    }
    return 0;   
}

int jogar_andar(int andar) {
    char entrada;
    int dano;

    while (1) {
        desenhar_mapa(andar); 
        printf("Comando (W/A/S/D/I/O): ");
        entrada = getch();

        dano = 0; 

        if (entrada == 'w' || entrada == 'W')      dano = mover(0, -1, '^');
        else if (entrada == 's' || entrada == 'S') dano = mover(0,  1, 'v');
        else if (entrada == 'a' || entrada == 'A') dano = mover(-1, 0, '<');
        else if (entrada == 'd' || entrada == 'D') dano = mover( 1, 0, '>');
        else if (entrada == 'i' || entrada == 'I') {                 
            if (interagir() == 1) return 1;  
        }
        else if (entrada == 'o' || entrada == 'O') {
            if (atacar() == 1) return 1; 
        }
        else continue;                   

        if (entrada == 'w' || entrada == 's' || entrada == 'a' || entrada == 'd' ||
            entrada == 'W' || entrada == 'S' || entrada == 'A' || entrada == 'D') {
            if (mover_monstros(andar) == 1) {
                dano = 1;                
            }
        }

        if (dano == 1) {               
            vidas--;
            if (vidas <= 0) return 2; 
            printf("\nVoce tomou dano! Reiniciando andar...\n");
            system("pause");
            carregar_andar(andar);       
        }
    }
}

void jogar(void) {
    vidas = 3;
    boss_vida = 3;
    boss_vivo = 1;
    boss_linha = 21;
    boss_coluna = 12;
    
    int andar = 0;
    while (andar <= 3) {
        carregar_andar(andar);
        int resultado = jogar_andar(andar);

        if (resultado == 1) {
            andar++;   
            if (andar <= 3) {
                printf("\nProximo andar liberado!\n");
                system("pause");
            }
        }
        else if (resultado == 2) {
            printf("\nGAME OVER! Suas vidas acabaram.\n");
            break;
        }     
        else break;
    }

    if (andar > 3) {
        printf("\nPARABENS! Gorgoroth, o Tita de Ferro foi derrotado e voce venceu o jogo!\n");
    }
}

void exibir_tutorial(void) {
    system("cls");
    printf("=== TUTORIAL BASICO ===\n\n");
    printf("Controles de Movimento:\n");
    printf("  W - Mover para Cima (^)\n");
    printf("  S - Mover para Baixo (v)\n");
    printf("  A - Mover para Esquerda (<)\n");
    printf("  D - Mover para Direita (>)\n\n");
    printf("Acoes:\n");
    printf("  I - Interagir (Pegar armas/chaves, abrir portas, usar alcapoes 'L')\n");
    printf("  O - Atacar (Usa a arma equipada na direcao que voce esta olhando)\n\n");
    printf("Elementos do Mapa:\n");
    printf("  *   : Paredes\n");
    printf("  #   : Espinhos (dao dano)\n");
    printf("  @   : Chaves\n");
    printf("  D   : Portas Trancadas\n");
    printf("  X/Y : Monstros comuns\n");
    printf("  Z   : Gorgoroth, o Tita de Ferro\n\n");
    system("pause");
}

void exibir_creditos(void) {
    system("cls");
    printf("=== CREDITOS ===\n\n");
    printf("Jogo desenvolvido por:\n");
    printf("-> Davi Lasmar Bieri\n");
    printf("-> Arthur Aleixo\n\n");
    printf("Disciplina: Programacao I\n\n");
    system("pause");
}

int main() {
    srand(time(NULL));
    int opcao;
    
    while (1) {
        system("cls");
        printf("=== JOGO DE MATRIZ ===\n");
        printf("1. Jogar\n");
        printf("2. Tutorial\n");
        printf("3. Creditos\n");
        printf("4. Sair\n\n");
        printf("Escolha: ");
        opcao = getch() - '0';

        if (opcao == 1) {
            jogar();
            printf("\nPressione qualquer tecla para voltar ao menu principal...");
            getch();
        }
        else if (opcao == 2) {
            exibir_tutorial();
        }
        else if (opcao == 3) {
            exibir_creditos();
        }
        else if (opcao == 4) {
            break;
        }
    }
    return 0;
}