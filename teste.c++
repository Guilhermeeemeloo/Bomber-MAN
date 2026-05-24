/*
Trabalho Bomberman - M2 - Algorítmos e Programação II

Bernardo Prantz Pin
Samuel Pereira Eduardo Santana
Toni Eliezer Dos Santos
Guilherme Melo
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <locale.h>
#include <fstream>
#include <string>

// multiplataforma
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
    #include <mmsystem.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

using namespace std;

    const int mapaFase1[19][25] = {

        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };
    const int mapaFase2[19][25] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    const int mapaFase3[19][25] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
        {1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

const unsigned maxInimigos = 10;

// ============================================================
// SISTEMA DE POWER-UPS
// ============================================================
// Tipos de power-up
enum TipoPowerUp {
    PU_FOGO,        // Aumenta raio de fogo (+1, cumulativo)
    PU_BOMBA,       // Aumenta qtd de bombas (+1, cumulativo)
    PU_VIDA,        // Vida extra (cumulativo)
    PU_RELOGIO,     // Bomba relógio (explode instantaneamente)
    PU_ESCUDO,      // Sobreviver a uma bomba
    PU_FANTASMA,    // Passar por blocos quebráveis
    TOTAL_POWERUPS
};

const char* nomePowerUp[] = {
    "Fogo+",
    "Bomba+",
    "Vida+",
    "Relogio",
    "Escudo",
    "Fantasma"
};

const char* emojPowerUp[] = {
    "🔥",  // Fogo+
    "💣",  // Bomba+
    "❤️",  // Vida+
    "⏰",  // Relogio
    "🛡️",  // Escudo
    "👻"   // Fantasma
};

struct PowerUp {
    int x;
    int y;
    bool ativo;
    TipoPowerUp tipo;
};

const int maxPowerUps = 30;

// Power-ups do jogador (atributos acumulados)
struct PowerUpsJogador {
    int nivelFogo;      // raio extra de explosão (default 0)
    int qtdBombas;      // bombas simultâneas permitidas (default 1)
    int vidas;          // <--- MUDOU DE vidasExtra para vidas
    bool temRelogio;    // próxima bomba explode pelo controle
    int escudos;        // escudos que absorvem dano (default 0)
    bool temFantasma;   // pode atravessar caixas (default false)
};
// ============================================================

template <typename T>
void troca(T& a, T& b) {
    T temporario = a;
    a = b;
    b = temporario;
}

struct Jogador {
    int x;
    int y;
    bool vivo;
    int qtdMovimentos;
    int bombasUsadas;
    double pontuacao;
    int inimigosAbatidos;
    int caixasDestruidas;
    PowerUpsJogador pus; // power-ups ativos
};

struct pRanking {
    string data;
    string nomeJogador;
    int movimentos;
    int bombasUsadas;
    int pontosJogador;
    int tempoPartida;
};

struct Inimigo {
    int x;
    int y;
    bool vivo;
    int direcao;
    int passos;
    bool boss;

};

struct Bomba {
    int x;
    int y;
    bool ativa;
    chrono::steady_clock::time_point tempoPlantada;
    bool explosaoAtiva;
    chrono::steady_clock::time_point tempoExplosao;
    bool ehRelogio;
};

struct EstadoJogo {
    int mapa[19][25];
    bool rodando;
    bool vencedor;
    unsigned inimigosAtivos;
    chrono::steady_clock::time_point tempoInicio;
    int fase;
    bool portalAtivo;
    int portalX;
    int portalY;
    bool spawnaBoss;
    PowerUp powerUps[maxPowerUps]; // array de power-ups no mapa
    int totalPowerUps;
};

void enableANSI() {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
}

#ifndef _WIN32
int _kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}


int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif
void tocaMusica(int faixa) {
    #ifdef _WIN32
    switch(faixa) {
        case 0: PlaySound(TEXT("tema_menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
        case 1: PlaySound(TEXT("tema_fase1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
        case 2: PlaySound(TEXT("tema_fase2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
        case 3: PlaySound(TEXT("tema_fase3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
    }
    #endif
}

double calculaPontuacao(Jogador& p1) {
    double pontosBase = (p1.inimigosAbatidos * 100) + (p1.caixasDestruidas * 10);

    double bonusBomba = 1.0;
    if(p1.bombasUsadas > 0) {
        double relacao = (double)p1.inimigosAbatidos / p1.bombasUsadas;
        if(relacao >= 1.0)       bonusBomba = 2.0;
        else if(relacao >= 0.5)  bonusBomba = 1.5;
        else                     bonusBomba = 1.0;
    }

    double penalidade = 1.0;
    int excesso = p1.qtdMovimentos / 50;
    if(excesso > 8) excesso = 8;
    penalidade = 1.0 - (excesso * 0.05);

    return pontosBase * bonusBomba * penalidade;
}

// ============================================================
// FUNÇÕES DO SISTEMA DE POWER-UPS
// ============================================================

// Inicializa os atributos padrão de power-ups do jogador
void inicializaPowerUpsJogador(Jogador& p1) {
    p1.pus.nivelFogo    = 0;
    p1.pus.qtdBombas    = 1;
    p1.pus.vidas        = 1;
    p1.pus.temRelogio   = true;
    p1.pus.escudos      = 0;
    p1.pus.temFantasma  = false;
}

// Sorteia power-ups no mapa quando uma caixa é destruída
// Cada caixa destruída tem ~40% de chance de gerar um power-up
void sorteiaDropPowerUp(EstadoJogo& jogo, int linhaDestruida, int colunaDestruida) {
    if(jogo.totalPowerUps >= maxPowerUps) return;

    // 40% de chance de dropar
    if(rand() % 100 >= 40) return;

    // Garante que a célula está livre (mapa[x][y] == 0 após destruição)
    if(jogo.mapa[linhaDestruida][colunaDestruida] != 0) return;

    // Sorteia o tipo (distribuição ponderada para balanceamento)
    // Fogo e Bomba são mais comuns; Escudo e Fantasma mais raros
    int sorteio = rand() % 100;
    TipoPowerUp tipo;
    if     (sorteio < 25) tipo = PU_FOGO;
    else if(sorteio < 45) tipo = PU_BOMBA;
    else if(sorteio < 60) tipo = PU_VIDA;
    else if(sorteio < 72) tipo = PU_RELOGIO;
    else if(sorteio < 86) tipo = PU_ESCUDO;
    else                  tipo = PU_FANTASMA;

    jogo.powerUps[jogo.totalPowerUps].x     = linhaDestruida;
    jogo.powerUps[jogo.totalPowerUps].y     = colunaDestruida;
    jogo.powerUps[jogo.totalPowerUps].ativo  = true;
    jogo.powerUps[jogo.totalPowerUps].tipo   = tipo;
    jogo.totalPowerUps++;
}

// Aplica o efeito do power-up no jogador
void aplicaPowerUp(Jogador& p1, TipoPowerUp tipo) {
    switch(tipo) {
        case PU_FOGO:
            p1.pus.nivelFogo++;
            break;
        case PU_BOMBA:
            p1.pus.qtdBombas++;
            break;
        case PU_VIDA:
            p1.pus.vidas++;
            break;
        case PU_RELOGIO:
            p1.pus.temRelogio = true;
            break;
        case PU_ESCUDO:
            p1.pus.escudos++;
            break;
        case PU_FANTASMA:
            p1.pus.temFantasma = true;
            break;
        default: break;
    }
}

// Verifica se o jogador está sobre algum power-up e o coleta
void coletaPowerUp(EstadoJogo& jogo, Jogador& p1) {
    for(int i = 0; i < jogo.totalPowerUps; i++) {
        if(jogo.powerUps[i].ativo &&
           jogo.powerUps[i].x == p1.x &&
           jogo.powerUps[i].y == p1.y) {
            aplicaPowerUp(p1, jogo.powerUps[i].tipo);
            jogo.powerUps[i].ativo = false;
        }
    }
}

// Limpa todos os power-ups do mapa (usado ao trocar de fase)
void limpaPowerUps(EstadoJogo& jogo) {
    for(int i = 0; i < maxPowerUps; i++) {
        jogo.powerUps[i].ativo = false;
    }
    jogo.totalPowerUps = 0;
}

// Verifica se uma célula é bloqueada levando em conta o fantasma
bool celulaBloqueia(EstadoJogo& jogo, Jogador& p1, int x, int y) {
    int cel = jogo.mapa[x][y];
    if(cel == 1) return true;             // parede sólida: sempre bloqueia
    if(cel == 2 && !p1.pus.temFantasma) return true; // caixa: bloqueia sem fantasma
    return false;
}
// ============================================================

// procedimento para desenhar o mapa do jogo
void imprimeMapa(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba& bomba, Bomba& bombaP2, Inimigo inimigos[], unsigned selDificuldade = 1) {

    string corChao = "\033[42m";
    if (jogo.fase == 2) corChao = "\033[46m";
    if (jogo.fase == 3) corChao = "\033[100m";

    for(int i=0; i<19; i++) {
        for(int j=0; j<25; j++) {

            // --- calcula raio real de explosão com nivelFogo ---
            int raio = 1 + p1.pus.nivelFogo;
            bool naExplosao = false;
            if(bomba.explosaoAtiva && jogo.mapa[i][j] != 1) {
                if(i == bomba.x && j == bomba.y) naExplosao = true;
                // propaga para cima
                for(int r = 1; r <= raio && !naExplosao; r++) {
                    if(jogo.mapa[bomba.x - r][bomba.y] == 1) break;
                    if(i == bomba.x - r && j == bomba.y) { naExplosao = true; break; }
                }
                // propaga para baixo
                for(int r = 1; r <= raio && !naExplosao; r++) {
                    if(jogo.mapa[bomba.x + r][bomba.y] == 1) break;
                    if(i == bomba.x + r && j == bomba.y) { naExplosao = true; break; }
                }
                // propaga para esquerda
                for(int r = 1; r <= raio && !naExplosao; r++) {
                    if(jogo.mapa[bomba.x][bomba.y - r] == 1) break;
                    if(i == bomba.x && j == bomba.y - r) { naExplosao = true; break; }
                }
                // propaga para direita
                for(int r = 1; r <= raio && !naExplosao; r++) {
                    if(jogo.mapa[bomba.x][bomba.y + r] == 1) break;
                    if(i == bomba.x && j == bomba.y + r) { naExplosao = true; break; }
                }
            }

            if(naExplosao) {
                cout << "\033[103m💥\033[0m";

            } else if(i==p1.x && j==p1.y) {
                if(p1.vivo == true){
                    cout << corChao << "👳🏻‍♂️\033[0m";
                } else {
                    cout << corChao << "🪦\033[0m";
                }
            }else if(i==p2.x && j==p2.y) {
                if(p2.vivo == true) cout << corChao << "🥷\033[0m";
                else cout << corChao << "🪦\033[0m";
            }else if(bomba.ativa == true && i==bomba.x && j==bomba.y) {
                cout << corChao << "💣\033[0m";

            }else if(bombaP2.ativa == true && i==bombaP2.x && j==bombaP2.y) {
                cout << corChao << "💣\033[0m";
             }else if(jogo.portalAtivo && i == jogo.portalX && j == jogo.portalY) {
                cout << "\033[45m🕌\033[0m";
                continue;

            } else {
                // Verifica power-up na célula
                bool temPU = false;
                int idxPU = -1;
                for(int p = 0; p < jogo.totalPowerUps; p++) {
                    if(jogo.powerUps[p].ativo && jogo.powerUps[p].x == i && jogo.powerUps[p].y == j) {
                        temPU = true;
                        idxPU = p;
                        break;
                    }
                }

                bool inimigoAqui = false;
                bool ehBoss = false;
                for(int k = 0; k < jogo.inimigosAtivos; k++) {
                    if(inimigos[k].vivo == true && i == inimigos[k].x && j == inimigos[k].y) {
                        inimigoAqui = true;
                        if(inimigos[k].boss == true) ehBoss = true;
                        break;
                    }
                }

                if(inimigoAqui) {
                    if(ehBoss) cout << corChao << "👺";
                    else       cout << corChao << "👹";
                } else if(temPU) {
                    // Exibe o emoji do power-up no chão
                    cout << corChao << emojPowerUp[jogo.powerUps[idxPU].tipo] << "\033[0m";
                } else {
                    switch (jogo.mapa[i][j]) {
                    case 0: cout << corChao << "  \033[0m"; break;
                    case 1: cout << "\033[47m  \033[0m";   break;
                    case 2: cout << corChao << "🧱\033[0m"; break;
                    }
                }
            }
        }
        cout << "\n";
    }

    // --- HUD ---
    cout << "\033[33mDIFICULDADE: ";
    if(selDificuldade == 3)      cout << "Dificil";
    else if(selDificuldade == 2) cout << "Intermediario";
    else                         cout << "Facil";

    auto tempoAtual = chrono::steady_clock::now();
    int tempoDecorrido = chrono::duration_cast<chrono::seconds>(tempoAtual - jogo.tempoInicio).count();
    int minutos  = tempoDecorrido / 60;
    int segundos = tempoDecorrido % 60;

    cout << "\t\033[33m" << "TEMPO DE JOGO: ";
    if(minutos > 0)  { cout << minutos << "m "; if(segundos < 10) cout << "0"; }
    else             { cout << "00m "; if(segundos < 10) cout << "0"; }
    cout << segundos << "s ";

    cout << "\n\033[36mMOVIMENTOS: " << p1.qtdMovimentos
         << " | INIMIGOS ABATIDOS: " << p1.inimigosAbatidos
         << "\nBOMBAS USADAS: " << p1.bombasUsadas
         << " | PONTOS: " << p1.pontuacao << "\033[0m";

    // --- HUD de power-ups ativos ---
    cout << "\n\033[35mPOWER-UPS: ";
    cout << "🔥x" << p1.pus.nivelFogo + 1;       // exibe nível atual (base 1)
    cout << " | 💣x" << p1.pus.qtdBombas;
    cout << " | ❤️x" << p1.pus.vidas;
    if(p1.pus.temRelogio)      cout << " | ⏰RELOGIO";
    if(p1.pus.escudos     > 0) cout << " | 🛡️x" << p1.pus.escudos;
    if(p1.pus.temFantasma)     cout << " | 👻FANTASMA";
    cout << "\033[0m";

    cout << "\033[J";
}

// procedimento para executar as acoes do jogador no mapa
void executaMovimentos(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba& bomba1, Bomba& bomba2) {
    char tecla;
    if ( _kbhit() ) {
        tecla = getch();

        // --- CONTROLES DO JOGADOR 1 (WASD) ---
        if(p1.vivo) {
            if(tecla == 'w' && !celulaBloqueia(jogo, p1, p1.x-1, p1.y)) { p1.x--; p1.qtdMovimentos++; }
            if(tecla == 's' && !celulaBloqueia(jogo, p1, p1.x+1, p1.y)) { p1.x++; p1.qtdMovimentos++; }
            if(tecla == 'a' && !celulaBloqueia(jogo, p1, p1.x, p1.y-1)) { p1.y--; p1.qtdMovimentos++; }
            if(tecla == 'd' && !celulaBloqueia(jogo, p1, p1.x, p1.y+1)) { p1.y++; p1.qtdMovimentos++; }

            if(tecla == 'x' && !bomba1.ativa && !bomba1.explosaoAtiva) {
                bomba1.ativa = true; bomba1.x = p1.x; bomba1.y = p1.y;
                bomba1.tempoPlantada = chrono::steady_clock::now();
                bomba1.ehRelogio = p1.pus.temRelogio;
            }
            if(tecla == 'c' && bomba1.ativa && bomba1.ehRelogio) {
                bomba1.ehRelogio = false;
                bomba1.tempoPlantada = chrono::steady_clock::now() - chrono::seconds(10);
            }
        }

        // --- CONTROLES DO JOGADOR 2 (Setas) ---
        if(p2.vivo) {
            if(tecla == 72 && !celulaBloqueia(jogo, p2, p2.x-1, p2.y)) { p2.x--; p2.qtdMovimentos++; } // Cima
            if(tecla == 80 && !celulaBloqueia(jogo, p2, p2.x+1, p2.y)) { p2.x++; p2.qtdMovimentos++; } // Baixo
            if(tecla == 75 && !celulaBloqueia(jogo, p2, p2.x, p2.y-1)) { p2.y--; p2.qtdMovimentos++; } // Esq
            if(tecla == 77 && !celulaBloqueia(jogo, p2, p2.x, p2.y+1)) { p2.y++; p2.qtdMovimentos++; } // Dir

            if(tecla == '0' && !bomba2.ativa && !bomba2.explosaoAtiva) {
                bomba2.ativa = true; bomba2.x = p2.x; bomba2.y = p2.y;
                bomba2.tempoPlantada = chrono::steady_clock::now();
                bomba2.ehRelogio = p2.pus.temRelogio;
            }
            if(tecla == '1' && bomba2.ativa && bomba2.ehRelogio) {
                bomba2.ehRelogio = false;
                bomba2.tempoPlantada = chrono::steady_clock::now() - chrono::seconds(10);
            }
        }
        coletaPowerUp(jogo, p1);
        coletaPowerUp(jogo, p2);
    }
}

bool temInimigoNaCasa(int x, int y, int indexAtual, Inimigo inimigos[], unsigned total) {
    for(int k = 0; k < total; k++) {
        if(k != indexAtual && inimigos[k].vivo && inimigos[k].x == x && inimigos[k].y == y)
            return true;
    }
    return false;
}

bool ehAreaPerigosa(int x, int y, Bomba& bomba, int nivelFogo) {
    if (bomba.ativa && x == bomba.x && y == bomba.y) return true;

    if (bomba.explosaoAtiva) {
        int raio = 1 + nivelFogo;
        if(x == bomba.x && y == bomba.y) return true;
        for(int r = 1; r <= raio; r++) {
            if(x == bomba.x - r && y == bomba.y) return true;
            if(x == bomba.x + r && y == bomba.y) return true;
            if(x == bomba.x && y == bomba.y - r) return true;
            if(x == bomba.x && y == bomba.y + r) return true;
        }
    }
    return false;
}

void movimentaInimigos(EstadoJogo& jogo, Inimigo inimigos[], Bomba& bomba, Jogador& p1, unsigned selDificuldade) {

    int chancePerseguicao;
    if(selDificuldade == 3)      chancePerseguicao = 75;
    else if(selDificuldade == 2) chancePerseguicao = 50;
    else                         chancePerseguicao = 0;

    for(int k = 0; k < jogo.inimigosAtivos; k++) {

        if(inimigos[k].vivo == false) continue;

        if(inimigos[k].passos == 0) {

            if(inimigos[k].boss == true) {
                int diffX = p1.x - inimigos[k].x;
                int diffY = p1.y - inimigos[k].y;

                int dirX = (diffX > 0) ? 1 : 0;
                int dirY = (diffY > 0) ? 3 : 2;

                int proxX = inimigos[k].x + (dirX == 1 ? 1 : -1);
                int proxY = inimigos[k].y + (dirY == 3 ? 1 : -1);

                bool livreX = (jogo.mapa[proxX][inimigos[k].y] == 0);
                bool livreY = (jogo.mapa[inimigos[k].x][proxY] == 0);

                if(abs(diffX) >= abs(diffY)) {
                    if(livreX) inimigos[k].direcao = dirX;
                    else if(livreY) inimigos[k].direcao = dirY;
                    else inimigos[k].direcao = rand() % 4;
                } else {
                    if(livreY) inimigos[k].direcao = dirY;
                    else if(livreX) inimigos[k].direcao = dirX;
                    else inimigos[k].direcao = rand() % 4;
                }
            } else if(selDificuldade == 1) {
                inimigos[k].direcao = rand() % 4;
            } else {
                int sorteio = rand() % 100;
                if(sorteio < chancePerseguicao) {
                    int diffX = p1.x - inimigos[k].x;
                    int diffY = p1.y - inimigos[k].y;
                    if(abs(diffX) >= abs(diffY))
                        inimigos[k].direcao = (diffX > 0) ? 1 : 0;
                    else
                        inimigos[k].direcao = (diffY > 0) ? 3 : 2;
                } else {
                    inimigos[k].direcao = rand() % 4;
                }
            }

            inimigos[k].passos = rand() % 3 + 1;
            continue;
        }

        switch(inimigos[k].direcao) {
        case 0:
            if(jogo.mapa[inimigos[k].x - 1][inimigos[k].y] == 0 &&
               !ehAreaPerigosa(inimigos[k].x - 1, inimigos[k].y, bomba, p1.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x - 1, inimigos[k].y, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].x--;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 1:
            if(jogo.mapa[inimigos[k].x + 1][inimigos[k].y] == 0 &&
               !ehAreaPerigosa(inimigos[k].x + 1, inimigos[k].y, bomba, p1.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x + 1, inimigos[k].y, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].x++;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 2:
            if(jogo.mapa[inimigos[k].x][inimigos[k].y-1] == 0 &&
               !ehAreaPerigosa(inimigos[k].x, inimigos[k].y-1, bomba, p1.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x, inimigos[k].y-1, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].y--;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 3:
            if(jogo.mapa[inimigos[k].x][inimigos[k].y+1] == 0 &&
               !ehAreaPerigosa(inimigos[k].x, inimigos[k].y+1, bomba, p1.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x, inimigos[k].y+1, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].y++;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        }
    }
}

void inicializaInimigos(EstadoJogo& jogo, Inimigo inimigos[], Jogador p1){
    int sorteioLinha, sorteioColuna;

    for(int i = 0; i < jogo.inimigosAtivos; i++){
        bool areaLivre = false;
        inimigos[i].vivo = true;
        inimigos[i].direcao = 0;
        inimigos[i].passos = 0;
        inimigos[i].boss = false;
        do{
            sorteioLinha = rand() % 19;
            sorteioColuna = rand() %  25;

            if (jogo.mapa[sorteioLinha][sorteioColuna] == 0) {
                areaLivre = true;
                if((sorteioLinha == p1.x && sorteioColuna == p1.y) ||
                   (sorteioLinha == p1.x +1 && sorteioColuna == p1.y) ||
                   (sorteioLinha == p1.x && sorteioColuna == p1.y +1) ||
                   (sorteioLinha == p1.x +2 && sorteioColuna == p1.y) ||
                   (sorteioLinha == p1.x && sorteioColuna == p1.y +2)){
                    areaLivre = false;
                }
            }

            if(areaLivre == true) {
                inimigos[i].x = sorteioLinha;
                inimigos[i].y = sorteioColuna;
            }
        }while(areaLivre == false);
    }
}

void sorteiaFrageis(EstadoJogo& jogo, Jogador& p1){
    int cont = 0, sorteioLinha, sorteioColuna;
    bool areaLivre = false;

    while(cont < 50) {
        sorteioLinha = rand() % 19;
        sorteioColuna = rand() %  25;

        if (jogo.mapa[sorteioLinha][sorteioColuna] == 0) {
            areaLivre = true;

            if((sorteioLinha == p1.x && sorteioColuna == p1.y) ||
               (sorteioLinha == p1.x +1 && sorteioColuna == p1.y) ||
               (sorteioLinha == p1.x && sorteioColuna == p1.y +1))
                areaLivre = false;

            if(areaLivre == true) {
                jogo.mapa[sorteioLinha][sorteioColuna] = 2;
                cont++;
            }
        }
    }
}

// Destrói caixas no raio da bomba e dropa power-ups
void destruiCaixasComDrop(EstadoJogo& jogo, Jogador& p1, Bomba& bomba) {
    int raio = 1 + p1.pus.nivelFogo;

    auto tentaDestruir = [&](int lx, int ly) -> bool {
        if(jogo.mapa[lx][ly] == 2) {
            jogo.mapa[lx][ly] = 0;
            p1.caixasDestruidas++;
            sorteiaDropPowerUp(jogo, lx, ly); // chance de dropar item
            return false; // caixa interrompe propagação
        }
        return false;
    };

    // Centro
    tentaDestruir(bomba.x, bomba.y);

    // Cima
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x - r][bomba.y] == 1) break;
        if(tentaDestruir(bomba.x - r, bomba.y)) break;
    }
    // Baixo
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x + r][bomba.y] == 1) break;
        if(tentaDestruir(bomba.x + r, bomba.y)) break;
    }
    // Esquerda
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x][bomba.y - r] == 1) break;
        if(tentaDestruir(bomba.x, bomba.y - r)) break;
    }
    // Direita
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x][bomba.y + r] == 1) break;
        if(tentaDestruir(bomba.x, bomba.y + r)) break;
    }
}

// Verifica se uma célula está na área de explosão (respeitando raio e blocos)
bool celulaNaExplosao(EstadoJogo& jogo, Bomba& bomba, int x, int y, int raio) {
    if(x == bomba.x && y == bomba.y) return true;

    // Cima
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x - r][bomba.y] == 1) break;
        if(x == bomba.x - r && y == bomba.y) return true;
    }
    // Baixo
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x + r][bomba.y] == 1) break;
        if(x == bomba.x + r && y == bomba.y) return true;
    }
    // Esquerda
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x][bomba.y - r] == 1) break;
        if(x == bomba.x && y == bomba.y - r) return true;
    }
    // Direita
    for(int r = 1; r <= raio; r++) {
        if(jogo.mapa[bomba.x][bomba.y + r] == 1) break;
        if(x == bomba.x && y == bomba.y + r) return true;
    }
    return false;
}

void detonaBomba(EstadoJogo& jogo, Bomba& bomba, Jogador& p1, Inimigo inimigos[]){

    if(bomba.ativa == true) {
        auto tempoAtual = chrono::steady_clock::now();
        auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoPlantada).count();

        // TRAVA DO RELOGIO: Só explode sozinha se NÃO for relógio!
        if(bomba.ehRelogio == false && duracao >= 3000) {
            bomba.ativa = false;

            // Destrói caixas com drop de power-up
            destruiCaixasComDrop(jogo, p1, bomba);

            int raio = 1 + p1.pus.nivelFogo;

            // Mata inimigos no raio
            for(int k = 0; k < jogo.inimigosAtivos; k++) {
                if(inimigos[k].vivo == true) {
                    if(celulaNaExplosao(jogo, bomba, inimigos[k].x, inimigos[k].y, raio)) {
                        inimigos[k].vivo = false;
                        p1.inimigosAbatidos++;
                        p1.pontuacao = calculaPontuacao(p1);
                    }
                }
            }

            bomba.explosaoAtiva = true;
            bomba.tempoExplosao = chrono::steady_clock::now();

            // Verifica dano ao jogador
            // Verifica dano ao jogador
            if(celulaNaExplosao(jogo, bomba, p1.x, p1.y, raio)) {
                if(p1.pus.escudos > 0) {
                    p1.pus.escudos--; // absorve com escudo
                } else {
                    p1.pus.vidas--;
                    if(p1.pus.vidas <= 0) {
                        p1.vivo = false;
                    } else {
                        // Respawn na base para não morrer de novo no mesmo milissegundo
                        p1.x = 1;
                        p1.y = 1;
                    }
                }
            }
        }
    }

    if(bomba.explosaoAtiva == true) {
        auto tempoAtual = chrono::steady_clock::now();
        auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoExplosao).count();
        if(duracao >= 500) {
            bomba.explosaoAtiva = false;
        }
    }
}

void carregaMapa(EstadoJogo& jogo) {
    const int (*mapa)[25];

    if(jogo.fase == 1)      mapa = mapaFase1;
    else if(jogo.fase == 2) mapa = mapaFase2;
    else                    mapa = mapaFase3;

    for(int i = 0; i < 19; i++)
        for(int j = 0; j < 25; j++)
            jogo.mapa[i][j] = mapa[i][j];
}

void avancaFase(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba& bomba, Bomba& bombaP2, Inimigo inimigos[], unsigned selDificuldade) {
    jogo.fase++;
    tocaMusica(jogo.fase);
    jogo.portalAtivo = false;
    jogo.spawnaBoss = false;
    carregaMapa(jogo);

    p1.x = 1;
    p1.y = 1;
    bomba.ativa = false;
    bomba.explosaoAtiva = false;
    bomba.ehRelogio = false;

    // Reseta o P2 também
    p2.x = 1;
    p2.y = 2;
    bombaP2.ativa = false;
    bombaP2.explosaoAtiva = false;
    bombaP2.ehRelogio = false;

    inicializaPowerUpsJogador(p1);
    inicializaPowerUpsJogador(p2);
    limpaPowerUps(jogo);

    if(selDificuldade == 1)      jogo.inimigosAtivos = 3;
    else if(selDificuldade == 2) jogo.inimigosAtivos = 5;
    else                         jogo.inimigosAtivos = 7;

    for(int k = 0; k < jogo.inimigosAtivos; k++) inimigos[k].boss = false;

    sorteiaFrageis(jogo, p1);
    if(jogo.mapa[1][2] == 2) jogo.mapa[1][2] = 0; // Protege para não nascer caixa em cima do P2

    inicializaInimigos(jogo, inimigos, p1);
}
void contagemRecursiva(int segundos) {
    if (segundos == 0) {
        cout << "\033[33m 0!\033[0m\n";
        auto inicioPausa = chrono::steady_clock::now();
        while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 500) {}
        return;
    }

    cout << "\033[33m" << segundos << "...\033[0m ";

    auto inicioPausa = chrono::steady_clock::now();
    while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {}

    contagemRecursiva(segundos - 1);
}

void verificaFim(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba& bomba, Bomba& bombaP2, Inimigo inimigos[], unsigned selDificuldade){
    int inimigosMortos = 0;
    for(int k = 0; k < jogo.inimigosAtivos; k++){
        // Dano P1
        if(inimigos[k].vivo == true && inimigos[k].x == p1.x && inimigos[k].y == p1.y && p1.vivo) {
            if(p1.pus.escudos > 0) {
                p1.pus.escudos--;
                if(p1.x > 1) p1.x--;
            } else {
                p1.pus.vidas--;
                if(p1.pus.vidas <= 0) p1.vivo = false;
                else { p1.x = 1; p1.y = 1; }
            }
        }
        // Dano P2
        if(inimigos[k].vivo == true && inimigos[k].x == p2.x && inimigos[k].y == p2.y && p2.vivo) {
            if(p2.pus.escudos > 0) {
                p2.pus.escudos--;
                if(p2.x > 1) p2.x--;
            } else {
                p2.pus.vidas--;
                if(p2.pus.vidas <= 0) p2.vivo = false;
                else { p2.x = 1; p2.y = 2; }
            }
        }
        if(inimigos[k].vivo == false) inimigosMortos++;
    }

    if(inimigosMortos == jogo.inimigosAtivos && bomba.explosaoAtiva == false && bombaP2.explosaoAtiva == false) {
        if(jogo.fase == 3) {
            if(jogo.spawnaBoss == false) {
                jogo.spawnaBoss = true;
                jogo.inimigosAtivos = 1;
                inimigos[0].vivo = true;
                inimigos[0].boss = true;
                inimigos[0].x = 17;
                inimigos[0].y = 23;
                inimigos[0].passos = 0;
                inimigos[0].direcao = 0;
            } else {
                #ifdef _WIN32
                    COORD coord; coord.X = 0; coord.Y = 0;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                #else
                    cout << "\033[H";
                #endif
                jogo.vencedor = true;
                imprimeMapa(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);
                auto inicioPausa = chrono::steady_clock::now();
                while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {}
                jogo.rodando = false;
            }
        } else {
            jogo.portalAtivo = true;
        }
    }

    // Se ALGUÉM pisou no portal, avança
    if(jogo.portalAtivo && ((p1.x == jogo.portalX && p1.y == jogo.portalY) || (p2.x == jogo.portalX && p2.y == jogo.portalY))) {
        #ifdef _WIN32
            COORD coord; coord.X = 0; coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            cout << "\033[H";
        #endif
        imprimeMapa(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);

        cout << "\n\n\t\033[36m AVANCANDO PARA A FASE " << jogo.fase + 1 << " EM: \033[0m";
        contagemRecursiva(3);

        jogo.portalAtivo = false;
        avancaFase(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);
    }

    // GAME OVER SOMENTE SE AMBOS MORREREM
    if(p1.vivo == false && p2.vivo == false && bomba.explosaoAtiva == false && bombaP2.explosaoAtiva == false){
        #ifdef _WIN32
            COORD coord; coord.X = 0; coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            cout << "\033[H";
        #endif
        imprimeMapa(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);
        auto inicioPausa = chrono::steady_clock::now();
        while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {}
        jogo.rodando = false;
    }
}

void imprimeTela(){
    int matTelaInicial[19][25] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,13,0,0,0,1},
    {1,0,12,12,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,4,0,0,0,0,0,13,0,1},
    {1,0,0,0,0,0,0,12,0,0,0,0,0,0,0,4,0,0,0,13,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,1},
    {1,0,0,12,0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,1},
    {1,0,0,0,12,0,0,12,14,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,12,14,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,12,14,14,3,3,3,3,3,3,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,12,0,0,12,14,14,3,3,3,3,0,0,0,0,0,0,12,0,0,1},
    {1,0,0,0,0,0,0,0,0,12,14,14,14,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,1},
    {1,0,12,12,0,0,0,0,5,6,7,5,8,9,7,10,11,0,0,12,0,0,0,0,1},
    {1,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

for(int i = 0; i < 19; i++){
    for(int j = 0; j < 25; j++){
        switch(matTelaInicial[i][j]){
        case 0: cout<< "\033[104m  \033[0m"; break;
        case 1: cout<< "\033[107m  \033[0m"; break;
        case 2: cout<< "\033[103m🔥\033[0m"; break;
        case 3: cout<< "\033[100m💣\033[0m"; break;
        case 4: cout<< "\033[104m🧨\033[0m"; break;
        case 5: cout<< "\033[104m\033[31m B"; break;
        case 6: cout<< "\033[104m\033[31m 0"; break;
        case 7: cout<< "\033[104m\033[31m M"; break;
        case 8: cout<< "\033[104m\033[31m E"; break;
        case 9: cout<< "\033[104m\033[31m R"; break;
        case 10: cout<< "\033[104m\033[31m A"; break;
        case 11: cout<< "\033[104m\033[31m N"; break;
        case 12: cout<< "\033[44m🧱\033[0m"; break;
        case 13: cout<< "\033[104m👹\033[0m"; break;
        case 14: cout<< "\033[40m  \033[0m"; break;
        }
    }
    cout << "\n";
}
}

void imprimeTela(bool vencedor){
    int matGameOver[19][25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,4,2,2,0,0,4,2,5,0,0,2,2,2,2,0,0,2,2,2,0,0,0,1,
                                1,0,2,0,0,0,0,2,0,2,0,0,2,4,0,2,0,0,2,3,0,0,0,0,1,
                                1,0,2,0,3,0,0,2,2,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,1,
                                1,0,4,2,2,0,0,2,0,2,0,0,2,0,0,2,0,0,2,2,2,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,2,2,2,0,0,2,0,0,2,0,0,2,2,2,0,0,2,2,0,0,0,0,1,
                                1,0,2,0,2,0,0,2,0,0,2,0,0,2,3,0,0,0,2,3,0,0,0,0,1,
                                1,0,2,0,2,0,0,4,3,3,5,0,0,2,0,0,0,0,2,4,5,0,0,0,1,
                                1,0,2,2,2,0,0,0,4,5,0,0,0,2,2,2,0,0,2,0,2,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                                };

    int matWin[19][25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,0,2,0,0,2,0,0,0,1,
                        1,0,0,2,0,0,0,2,0,0,0,0,2,0,0,0,0,2,2,0,2,0,0,0,1,
                        1,0,0,2,0,0,0,2,0,0,0,0,2,0,0,0,0,2,4,5,2,0,0,0,1,
                        1,0,0,2,3,2,3,2,0,0,0,0,2,0,0,0,0,2,0,2,2,0,0,0,1,
                        1,0,0,4,5,0,4,5,0,0,0,0,2,0,0,0,0,2,0,0,2,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                        };

    if(vencedor == false){
        for(int i = 0; i < 19; i++){
            for(int j = 0; j < 25; j++){
                switch(matGameOver[i][j]){
                case 0: cout<< "\033[40m  \033[0m"; break;
                case 1: cout<< "\033[47m  \033[0m"; break;
                case 2: cout<< "\033[101m  \033[0m"; break;
                case 3: cout<< "\033[101m  \033[0m"; break;
                case 4: cout<< "\033[101m  \033[0m"; break;
                case 5: cout<< "\033[101m  \033[0m"; break;
                }
            }
            cout << "\n";
        }
    }else{
        for(int i = 0; i < 19; i++){
            for(int j = 0; j < 25; j++){
                switch(matWin[i][j]){
                case 0: cout<< "\033[40m  \033[0m"; break;
                case 1: cout<< "\033[47m  \033[0m"; break;
                case 2: cout<< "\033[44m  \033[0m"; break;
                case 3: cout<< "\033[44m  \033[0m"; break;
                case 4: cout<< "\033[44m  \033[0m"; break;
                case 5: cout<< "\033[44m  \033[0m"; break;
                }
            }
            cout << "\n";
        }
    }
}

void salvaRanking(Jogador p1, EstadoJogo jogo){

    auto tempoFinal = chrono::steady_clock::now();
    int tempoTotal = chrono::duration_cast<chrono::seconds>(tempoFinal - jogo.tempoInicio).count();

    time_t t = time(0);
    tm* now = localtime(&t);
    char dataAtual[11];
    strftime(dataAtual, sizeof(dataAtual), "%d/%m/%Y", now);

    string nomeJogador;
    cout << "\n\n\nDIGITE SEU PRIMEIRO NOME: ";
    cout << "\033[J";
    cin >> nomeJogador;

    ofstream arqRank;
    arqRank.open("ranking.txt", ios::app);
    if(arqRank.is_open()){
        arqRank << dataAtual << "\t" << nomeJogador << "\t" << tempoTotal << "\t" << p1.qtdMovimentos << "\t" << p1.bombasUsadas << "\t" << p1.pontuacao << "\n";
        arqRank.close();
    }else{
        cout << "Erro ao salvar!!!" << endl;
    }
}

void resetaJogo(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba& bomba, Bomba& bombaP2, Inimigo inimigos[], unsigned selDificuldade){
    cout << "\033[J";
    p1.caixasDestruidas = 0;
    p2.caixasDestruidas = 0;

    jogo.fase=1;
    tocaMusica(1);
    if(selDificuldade == 1)      jogo.inimigosAtivos = 3;
    else if(selDificuldade == 2) jogo.inimigosAtivos = 5;
    else if(selDificuldade == 3) jogo.inimigosAtivos = 7;

    jogo.spawnaBoss = false;
    carregaMapa(jogo);

    jogo.rodando = true;
    jogo.vencedor = false;

    p1.vivo = true;
    p1.qtdMovimentos = 0;
    p1.bombasUsadas = 0;
    p1.pontuacao = 0;
    p1.inimigosAbatidos = 0;
    p1.x = 1;
    p1.y = 1;

    p2.vivo = true;
    p2.qtdMovimentos = 0;
    p2.bombasUsadas = 0;
    p2.pontuacao = 0;
    p2.inimigosAbatidos = 0;
    p2.x = 1;
    p2.y = 2;

    bomba.ativa = false;
    bomba.explosaoAtiva = false;
    bomba.ehRelogio = false;
    bomba.tempoExplosao = chrono::steady_clock::now();
    bomba.tempoPlantada = chrono::steady_clock::now();
    bomba.x = 0;
    bomba.y = 0;

    bombaP2.ativa = false;
    bombaP2.explosaoAtiva = false;
    bombaP2.ehRelogio = false;
    bombaP2.tempoExplosao = chrono::steady_clock::now();
    bombaP2.tempoPlantada = chrono::steady_clock::now();
    bombaP2.x = 0;
    bombaP2.y = 0;

    jogo.portalAtivo = false;
    jogo.portalX = 9;
    jogo.portalY = 12;

    inicializaPowerUpsJogador(p1);
    inicializaPowerUpsJogador(p2);
    limpaPowerUps(jogo);

    sorteiaFrageis(jogo, p1);
    if(jogo.mapa[1][2] == 2) jogo.mapa[1][2] = 0; // Protege o spawn do P2
    inicializaInimigos(jogo, inimigos, p1);

    jogo.tempoInicio = chrono::steady_clock::now();
}

int main() {
    system ("chcp 65001");
    #ifdef _WIN32
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);

        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
    #endif

    srand(time(NULL));
    enableANSI();

    #ifdef _WIN32
        DWORD volume = 0x33FF33FF;
        waveOutSetVolume(0, volume);
    #endif
    tocaMusica(0);

    EstadoJogo jogo;
    Jogador p1;
    Jogador p2;
    Bomba bomba;
    Bomba bombaP2;
    Inimigo inimigos[maxInimigos];
    jogo.inimigosAtivos = 3;

    auto tempoInimigos = chrono::steady_clock::now();

    pRanking lista[100];
    pRanking temp;
    int totalJogadores;
    unsigned opcao;
    unsigned selDificuldade = 1;
    char lido;
    ifstream arqRank;
    do{
        #ifdef _WIN32
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
                cout << "\033[H";
        #endif

            imprimeTela();
            cout << "\033[J";
            cout << "\n1- Jogar \n2- Selecionar dificuldade \n3- Info \n4- Ranking \n5- Fechar o Jogo" << endl;
            cin >> opcao;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                opcao = 0;
            }

            switch(opcao){
                case 1:
                    resetaJogo(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);

                    while(jogo.rodando == true) {
                        #ifdef _WIN32
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                                cout << "\033[H";
                        #endif

                                imprimeMapa(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);

                                executaMovimentos(jogo, p1, p2, bomba, bombaP2);

                                auto tempoAtual_inimigos = chrono::steady_clock::now();
                                auto duracaoInimigos = chrono::duration_cast < chrono::milliseconds>(tempoAtual_inimigos - tempoInimigos).count();

                                if(duracaoInimigos >= 500) {
                                    movimentaInimigos(jogo, inimigos, bomba,p1,selDificuldade);
                                    tempoInimigos = chrono::steady_clock::now();
                                }

                                detonaBomba(jogo, bomba, p1, inimigos);
                                detonaBomba(jogo, bombaP2, p2, inimigos);
                                verificaFim(jogo, p1, p2, bomba, bombaP2, inimigos, selDificuldade);
                    }
                    #ifdef _WIN32
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    #else
                        cout << "\033[H";
                    #endif

                        imprimeTela(jogo.vencedor);
                        salvaRanking(p1, jogo);
                        cout << "PRESSIONE QUALQUER TECLA PARA VOLTAR A TELA INICIAL";

                        #ifdef _WIN32
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                                cout << "\033[H";
                        #endif
                        while(_kbhit()) { getch(); }
                        cin.clear();
                        getch();
                        #ifdef _WIN32
                            system ("cls");
                        #else
                            system ("clear");
                        #endif
                        cout << "\033[2J\033[H";

                        tocaMusica(0);
                    break;

                case 2:

                    do{

                        #ifdef _WIN32
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                            cout << "\033[H";
                        #endif

                        imprimeTela();
                        cout << "\033[J";

                        cout << "\nEscolha a dificuldade: \n1- Facil \n2- Intermediario \n3- Dificil\n";
                        cin >> selDificuldade;

                        if(cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            selDificuldade = 0;
                        }
                        if(selDificuldade == 1) jogo.inimigosAtivos = 3;
                        if(selDificuldade == 2) jogo.inimigosAtivos = 5;
                        if(selDificuldade == 3) jogo.inimigosAtivos = 7;

                    }while(selDificuldade < 1 || selDificuldade > 3);
                    break;
                case 3:
                    #ifdef _WIN32
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    #else
                        cout << "\033[H";
                    #endif

                    imprimeTela();
                    cout << "\033[J";

                    cout << "\n\033[36m===\t COMO JOGAR\t===\033[0m\n\n";

                    cout << "\033[33mCONTROLES:\033[0m\n";
                    cout << "  W / Seta Cima    -> Mover para cima\n";
                    cout << "  S / Seta Baixo   -> Mover para baixo\n";
                    cout << "  A / Seta Esquerda-> Mover para esquerda\n";
                    cout << "  D / Seta Direita -> Mover para direita\n";
                    cout << "  X                -> Plantar bomba\n";

                    cout << "\n\033[33mITENS DO MAPA:\033[0m\n";
                    cout << "  \033[42m🧔\033[0m  Voce\n";
                    cout << "  \033[42m👹\033[0m  Inimigo - evite o contato!\n";
                    cout << "  \033[42m💣\033[0m  Bomba plantada - explode em 3 segundos.\n";
                    cout << "  \033[103m💥\033[0m  Explosao - mata inimigos e destroi caixas.\n";
                    cout << "  \033[42m🧱\033[0m  Caixa destruivel pela bomba.\n";
                    cout << "  \033[47m  \033[0m  Parede solida - nao e destruivel.\n";

                    cout << "\n\033[33mPOWER-UPS (dropam de caixas destruidas):\033[0m\n";
                    cout << "  🔥 Fogo+     -> Aumenta raio de explosao (+1, cumulativo)\n";
                    cout << "  💣 Bomba+    -> Aumenta qtd de bombas simultaneas (cumulativo)\n";
                    cout << "  ❤️  Vida+     -> Vida extra, sobrevive a um dano (cumulativo)\n";
                    cout << "  ⏰ Relogio  -> Proxima bomba explode instantaneamente\n";
                    cout << "  🛡️  Escudo    -> Absorve um dano de bomba ou inimigo\n";
                    cout << "  👻 Fantasma -> Atravessa caixas destruiveis temporariamente\n";
                    cout << "  OBS: power-ups RESETAM ao avancar de fase!\n";

                    cout << "\n\033[33mOBJETIVO:\033[0m\n";
                    cout << "  Elimine todos os inimigos usando bombas para vencer!\n";
                    cout << "  Cuidado para nao se explodir!\n";

                    cout << "\n\033[33mDIFICULDADE:\033[0m\n";
                    cout << "  Facil        -> 3 inimigos, movimento aleatorio\n";
                    cout << "  Intermediario-> 5 inimigos, 50%% de chance de te perseguir\n";
                    cout << "  Dificil      -> 7 inimigos, 75%% de chance de te perseguir\n";

                    cout << "\n\033[33mPONTUACAO:\033[0m\n";
                    cout << "  Cada inimigo abatido    -> +100 pontos\n";
                    cout << "  Cada caixa destruida    -> +10 pontos\n";
                    cout << "  Bonus por eficiencia:\n";
                    cout << "    1+ inimigo por bomba  -> x2.0\n";
                    cout << "    1 inimigo a cada 2    -> x1.5\n";
                    cout << "    Abaixo disso          -> x1.0\n";
                    cout << "  Penalidade de movimento:\n";
                    cout << "    A cada 50 movimentos  -> -5%% (maximo -40%%)\n";

                    cout << "\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...";
                    while(_kbhit()) { getch(); }
                        cin.clear();
                        getch();
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                        cout << "\033[2J\033[H";
                    break;
                case 4:
                    #ifdef _WIN32
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    #else
                        cout << "\033[H";
                    #endif
                        imprimeTela();
                        cout << "\033[J";
                        cout << "\n\033[36m===\t RANKING\t  ===\033[0m\n\n";

                        arqRank.open("ranking.txt");
                        if(arqRank.is_open()){
                            totalJogadores = 0;

                            while(arqRank >> lista[totalJogadores].data >> lista[totalJogadores].nomeJogador >> lista[totalJogadores].tempoPartida >> lista[totalJogadores].movimentos >> lista[totalJogadores].bombasUsadas >> lista[totalJogadores].pontosJogador){
                                totalJogadores++;
                            }
                            arqRank.close();

                        }else{
                            cout << "Erro ao acessar o ranking!";
                            cout << "\033[J";
                        }
                        for(int i = 0; i < totalJogadores - 1; i++){
                            for(int j = 0; j < totalJogadores - i - 1; j++){
                                if(lista[j].pontosJogador < lista[j+1].pontosJogador){
                                    troca(lista[j], lista[j+1]);
                                }
                            }
                        }
                        cout << "DATA\t\tNOME\tBOMBAS\tMOVIMENTOS\tTEMPO\tPONTOS\n";
                        for(int i = 0; i < totalJogadores; i++){
                            int minutos = lista[i].tempoPartida / 60;
                            int segundos = lista[i].tempoPartida % 60;

                            cout << lista[i].data << "\t" << lista[i].nomeJogador << "\t" << lista[i].bombasUsadas << "\t" << lista[i].movimentos << "\t\t";

                            if(minutos < 10) cout << "0";
                            cout << minutos << "m ";
                            if(segundos < 10) cout << "0";
                            cout << segundos << "s\t";

                            cout << "  " << lista[i].pontosJogador << endl;
                        }
                        cout << "\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...";
                        while(_kbhit()) { getch(); }
                            cin.clear();
                            getch();
                        break;
            }
    }while(opcao != 5);

    cout << "\n\nOBRIGADO POR JOGAR!" << endl;

    return 0;
}

