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
#include <thread>

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
    int vidas;          // vezes que o personagem pode morrer e spawnar sem dar game over (default 1)
    bool temRelogio;    // jogador ganha poder sobre quando a bomba explodirá
    int escudos;        // escudos que absorvem dano (default 0)
    bool temFantasma;   // pode atravessar caixas (default false)
};

// uso de template num bubble sort para ordenação do ranking (case 4 na main)
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
    int modoJogo;
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

// Inicializa os atributos padrão de power-ups do jogador
void inicializaPowerUpsJogador(Jogador& p1) {
    p1.pus.nivelFogo    = 0;
    p1.pus.qtdBombas    = 1;
    p1.pus.vidas        = 1;
    p1.pus.temRelogio   = false;
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
        if(jogo.powerUps[i].ativo && jogo.powerUps[i].x == p1.x && jogo.powerUps[i].y == p1.y){
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
// protótipo de função usada em imprimeMapa para não ter que reorganizar as ordens das funções ;)
bool celulaNaExplosao(EstadoJogo& jogo, Bomba& bomba, int x, int y, int raio);

// procedimento para desenhar o mapa do jogo
void imprimeMapa(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba bombasP1[], Bomba bombasP2[], Inimigo inimigos[], unsigned selDificuldade = 1){
    string corChao = "\033[42m";
    if (jogo.fase == 2) corChao = "\033[46m";
    if (jogo.fase == 3) corChao = "\033[100m";

    for(int i=0; i<19; i++) {
        for(int j=0; j<25; j++) {
            bool naExplosao = false;

            // Verifica se em determinada posição do mapa será desenhado o fogo da explosao da bomba do P1
            for(int b = 0; b < 5; b++) {
                if(bombasP1[b].explosaoAtiva && celulaNaExplosao(jogo, bombasP1[b], i, j, 1 + p1.pus.nivelFogo)) {
                    naExplosao = true; break;
                }
            }
            // Verifica se em determinada posição do mapa será desenhado o fogo da explosao da bomba do P2
            for(int b = 0; b < 5; b++) {
                if(!naExplosao && bombasP2[b].explosaoAtiva && celulaNaExplosao(jogo, bombasP2[b], i, j, 1 + p2.pus.nivelFogo)) {
                    naExplosao = true; break;
                }
            }

            // Verifica se a posição atual tem uma bomba plantada
            bool temBombaPlatada = false;
            for(int b = 0; b < 5; b++) {
                if(bombasP1[b].ativa && i == bombasP1[b].x && j == bombasP1[b].y) { temBombaPlatada = true; break; }
                if(bombasP2[b].ativa && i == bombasP2[b].x && j == bombasP2[b].y) { temBombaPlatada = true; break; }
            }

            if(naExplosao) {
                cout << "\033[103m💥\033[0m"; //fogo da explosao
            } else if(i==p1.x && j==p1.y) {
                if(p1.vivo == true) cout << corChao << "👳🏻‍♂️\033[0m"; //p1
                else cout << corChao << "🪦\033[0m"; // lapide do p1 morto
            } else if(jogo.modoJogo == 2 && i==p2.x && j==p2.y) {
                if(p2.vivo == true) cout << corChao << "🥷\033[0m"; //p2
                else cout << corChao << "🪦\033[0m"; //lapide do p2 morto
            } else if(temBombaPlatada) {
                cout << corChao << "💣\033[0m"; //bomba plantada em contagem para explosao
            } else if(jogo.portalAtivo && i == jogo.portalX && j == jogo.portalY) {
                cout << "\033[45m🕌\033[0m"; //portal para proxima fase
            } else {
                //verifica sem tem algum power up na posição
                bool temPU = false;
                int idxPU = -1;
                for(int p = 0; p < jogo.totalPowerUps; p++) {
                    if(jogo.powerUps[p].ativo && jogo.powerUps[p].x == i && jogo.powerUps[p].y == j) {
                        temPU = true;
                        idxPU = p; break;
                    }
                }

                //verifica se tem inimigo na posição da matriz e se ele é boss ou nao
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
                    if(ehBoss) cout << corChao << "👺"; //boss
                    else       cout << corChao << "👹"; // inimigo comum

                } else if(temPU) {// desenha o emoji do power up de acordo com o bloco de verificação anterior
                    cout << corChao << emojPowerUp[jogo.powerUps[idxPU].tipo] << "\033[0m";
                } else {
                    switch (jogo.mapa[i][j]) {
                    case 0: cout << corChao << "  \033[0m"; break; //chão
                    case 1: cout << "\033[107m  \033[0m";   break; // parede solida
                    case 2: cout << corChao << "🧱\033[0m"; break; // parede quebravel
                    }
                }
            }
        }
        cout << "\n";
    }

    cout << "\033[33mDIFICULDADE: ";
    if(selDificuldade == 3)      cout << "Dificil";
    else if(selDificuldade == 2) cout << "Intermediario";
    else                         cout << "Facil";

    auto tempoAtual = chrono::steady_clock::now();
    int tempoDecorrido = chrono::duration_cast<chrono::seconds>(tempoAtual - jogo.tempoInicio).count();
    int minutos  = tempoDecorrido / 60;
    int segundos = tempoDecorrido % 60;

    cout << "\t\033[33mTEMPO DE JOGO: ";
    if(minutos > 0)  {
        cout << minutos << "m "; if(segundos < 10) cout << "0"; }
    else             { cout << "00m "; if(segundos < 10) cout << "0"; }
    cout << segundos << "s ";

    cout << "\n\033[36mMOVIMENTOS: " << p1.qtdMovimentos << " | INIMIGOS ABATIDOS: " << p1.inimigosAbatidos
         << "\nBOMBAS USADAS: " << p1.bombasUsadas << " | PONTOS: " << p1.pontuacao << "\033[0m";

    cout << "\n\033[35mPOWER-UPS: 🔥x" << p1.pus.nivelFogo + 1 << " | 💣x" << p1.pus.qtdBombas << " | ❤️x" << p1.pus.vidas;
    if(p1.pus.temRelogio)      cout << " | ⏰RELOGIO";
    if(p1.pus.escudos > 0)     cout << " | 🛡️x" << p1.pus.escudos;
    if(p1.pus.temFantasma)     cout << " | 👻FANTASMA";
    cout << "\033[0m";

    if (jogo.modoJogo == 2) {
        cout << "\n\033[36m[P2] MOVIMENTOS: " << p2.qtdMovimentos << " | INIMIGOS ABATIDOS: " << p2.inimigosAbatidos
             << "\n[P2] BOMBAS USADAS: " << p2.bombasUsadas << " | PONTOS: " << p2.pontuacao << "\033[0m";
        cout << "\n\033[35m[P2] POWER-UPS: 🔥x" << p2.pus.nivelFogo + 1 << " | 💣x" << p2.pus.qtdBombas << " | ❤️x" << p2.pus.vidas;
        if(p2.pus.temRelogio)  cout << " | ⏰RELOGIO";
        if(p2.pus.escudos > 0) cout << " | 🛡️x" << p2.pus.escudos;
        if(p2.pus.temFantasma) cout << " | 👻FANTASMA";
        cout << "\033[0m\n";
    }
    cout << "\033[J";
}
bool ehAreaPerigosa(EstadoJogo& jogo, int x, int y, Bomba bombasP1[], Bomba bombasP2[], int nivelFogoP1, int nivelFogoP2) {
    // Verifica todas as bombas do P1
    for(int i = 0; i < 5; i++) {
        if(jogo.modoJogo == 3){
            // Se a bomba está plantada, a área de fogo futura é perigosa
            if (bombasP1[i].ativa && celulaNaExplosao(jogo, bombasP1[i], x, y, 1 + nivelFogoP1)) return true;
        }
        // Se já está explodindo, a área de fogo atual é perigosa, evita que inimigos entrem na area de fogo da explosao e reapareçam vivos
        if (bombasP1[i].explosaoAtiva && celulaNaExplosao(jogo, bombasP1[i], x, y, 1 + nivelFogoP1)) return true;
    }
    // Verifica todas as bombas do P2
    for(int i = 0; i < 5; i++) {
        if (bombasP2[i].ativa && celulaNaExplosao(jogo, bombasP2[i], x, y, 1 + nivelFogoP2)) return true;
        if (bombasP2[i].explosaoAtiva && celulaNaExplosao(jogo, bombasP2[i], x, y, 1 + nivelFogoP2)) return true;
    }
    return false;
}

void movimentaIA(EstadoJogo& jogo, Jogador& bot, Bomba minhasBombas[], Bomba inimigoBombas[], int meuFogo, int inimigoFogo, Inimigo inimigos[]) {
    if (!bot.vivo) return;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // 1. AVALIA PERIGO IMINENTE
    bool perigoAtual = ehAreaPerigosa(jogo, bot.x, bot.y, minhasBombas, inimigoBombas, meuFogo, inimigoFogo);
    for(int k=0; k<jogo.inimigosAtivos; k++) {
        if(inimigos[k].vivo && abs(inimigos[k].x - bot.x) + abs(inimigos[k].y - bot.y) <= 1) perigoAtual = true;
    }

    // 2. MAPEAR CASAS 100% SEGURAS AO REDOR
    int casasSeguras[4];
    int numSeguras = 0;
    for(int i=0; i<4; i++) {
        int nx = bot.x + dx[i];
        int ny = bot.y + dy[i];

        if(!celulaBloqueia(jogo, bot, nx, ny) &&
           !ehAreaPerigosa(jogo, nx, ny, minhasBombas, inimigoBombas, meuFogo, inimigoFogo)) {
            bool temInimigo = false;
            for(int k=0; k<jogo.inimigosAtivos; k++) {
                if(inimigos[k].vivo && abs(inimigos[k].x - nx) + abs(inimigos[k].y - ny) <= 1) temInimigo = true;
            }
            if(!temInimigo) casasSeguras[numSeguras++] = i;
        }
    }

    // 3. MODO FUGA E PÂNICO
    if(perigoAtual) {
        if(numSeguras > 0) {
            // Foge para uma casa totalmente segura
            int escolha = casasSeguras[rand() % numSeguras];
            bot.x += dx[escolha];
            bot.y += dy[escolha];
            bot.qtdMovimentos++;
        } else {
            // MODO PÂNICO: Está na área da bomba e não há casa 100% segura adjacente!
            // Procura a bomba mais próxima e dá um passo na direção contrária a ela.
            int bx = bot.x, by = bot.y;
            int minDist = 999;
            for(int i=0; i<5; i++) {
                if(minhasBombas[i].ativa || minhasBombas[i].explosaoAtiva) {
                    int dist = abs(bot.x - minhasBombas[i].x) + abs(bot.y - minhasBombas[i].y);
                    if(dist < minDist) { minDist = dist; bx = minhasBombas[i].x; by = minhasBombas[i].y; }
                }
                if(inimigoBombas[i].ativa || inimigoBombas[i].explosaoAtiva) {
                    int dist = abs(bot.x - inimigoBombas[i].x) + abs(bot.y - inimigoBombas[i].y);
                    if(dist < minDist) { minDist = dist; bx = inimigoBombas[i].x; by = inimigoBombas[i].y; }
                }
            }

            int melhorFuga = -1;
            int maxDistParaBomba = minDist;
            for(int i=0; i<4; i++) {
                int nx = bot.x + dx[i];
                int ny = bot.y + dy[i];
                if(!celulaBloqueia(jogo, bot, nx, ny)) {
                    int distBomba = abs(nx - bx) + abs(ny - by);
                    if(distBomba > maxDistParaBomba) { // Escolhe o caminho que afasta da bomba
                        maxDistParaBomba = distBomba;
                        melhorFuga = i;
                    }
                }
            }
            if(melhorFuga != -1) {
                bot.x += dx[melhorFuga];
                bot.y += dy[melhorFuga];
                bot.qtdMovimentos++;
            }
        }
        return; // Foge e aborta qualquer outra ação
    }

    // busca de alvos
    bool temAlvoPerto = false;
    for(int i=0; i<4; i++) {

        int nx = bot.x + dx[i];

        int ny = bot.y + dy[i];

        if(jogo.mapa[nx][ny] == 2) temAlvoPerto = true;

        for(int k=0; k<jogo.inimigosAtivos; k++) {

            if(inimigos[k].vivo && inimigos[k].x == nx && inimigos[k].y == ny) temAlvoPerto = true;

        }

    }

    if(temAlvoPerto) {
        int ativas = 0, indexLivre = -1;
        for(int i = 0; i < 5; i++) {
            if(minhasBombas[i].ativa || minhasBombas[i].explosaoAtiva) ativas++;
            else if(indexLivre == -1) indexLivre = i;
        }
        if(ativas < bot.pus.qtdBombas && indexLivre != -1) {
            minhasBombas[indexLivre].ativa = true;
            minhasBombas[indexLivre].x = bot.x;
            minhasBombas[indexLivre].y = bot.y;
            minhasBombas[indexLivre].tempoPlantada = chrono::steady_clock::now();
            minhasBombas[indexLivre].ehRelogio = false;
            return;
        }
    }

    // busca itens power up perto
    int distMin = 9999;
    int melhorMove = -1;
    for(int i=0; i<numSeguras; i++) {
        int nx = bot.x + dx[casasSeguras[i]];
        int ny = bot.y + dy[casasSeguras[i]];

        for(int p = 0; p < jogo.totalPowerUps; p++) {
            if(jogo.powerUps[p].ativo) {
                int dist = abs(nx - jogo.powerUps[p].x) + abs(ny - jogo.powerUps[p].y);
                if(dist < distMin) {
                    distMin = dist;
                    melhorMove = casasSeguras[i];
                }
            }
        }
    }

    if(melhorMove != -1) {
        bot.x += dx[melhorMove];
        bot.y += dy[melhorMove];
        bot.qtdMovimentos++;
    } else if(numSeguras > 0) {
        int escolha = casasSeguras[rand() % numSeguras];
        bot.x += dx[escolha];
        bot.y += dy[escolha];
        bot.qtdMovimentos++;
    }
}
// procedimento para executar as acoes do jogador no mapa
void executaMovimentos(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba bombasP1[], Bomba bombasP2[]) {
    int tecla;

    // Usando while para ler toda a fila do teclado e tirar o input lag
    while ( _kbhit() ) {
        tecla = getch();

        // Tratamento para setas no Windows (evita duplo clique)
        if (tecla == 224 || tecla == 0 || tecla == -32) {
            tecla = getch();
        }

        // --- CONTROLES DO JOGADOR 1 (WASD) ---
        if(p1.vivo) {
            if(tecla == 'w' && !celulaBloqueia(jogo, p1, p1.x-1, p1.y)) { p1.x--; p1.qtdMovimentos++; }
            if(tecla == 's' && !celulaBloqueia(jogo, p1, p1.x+1, p1.y)) { p1.x++; p1.qtdMovimentos++; }
            if(tecla == 'a' && !celulaBloqueia(jogo, p1, p1.x, p1.y-1)) { p1.y--; p1.qtdMovimentos++; }
            if(tecla == 'd' && !celulaBloqueia(jogo, p1, p1.x, p1.y+1)) { p1.y++; p1.qtdMovimentos++; }

            if(tecla == 'x') {
                int ativas = 0;
                int indexLivre = -1;
                // Conta quantas bombas estão ativas e acha uma livre
                for(int i = 0; i < 5; i++) {
                    if(bombasP1[i].ativa || bombasP1[i].explosaoAtiva) ativas++;
                    else if(indexLivre == -1) indexLivre = i;
                }

                // Planta se não atingiu o limite do power-up
                if(ativas < p1.pus.qtdBombas && indexLivre != -1) {
                    bombasP1[indexLivre].ativa = true;
                    bombasP1[indexLivre].x = p1.x;
                    bombasP1[indexLivre].y = p1.y;
                    bombasP1[indexLivre].tempoPlantada = chrono::steady_clock::now();
                    bombasP1[indexLivre].ehRelogio = p1.pus.temRelogio;
                }
            }
            if(tecla == 'c') {
                for(int i = 0; i < 5; i++) {
                    if(bombasP1[i].ativa && bombasP1[i].ehRelogio) {
                        bombasP1[i].ehRelogio = false;
                        bombasP1[i].tempoPlantada = chrono::steady_clock::now() - chrono::seconds(10);
                    }
                }
            }
        }

        // --- CONTROLES DO JOGADOR 2 (Setas) ---
        if(p2.vivo) {
            if(tecla == 72 && !celulaBloqueia(jogo, p2, p2.x-1, p2.y)) { p2.x--; p2.qtdMovimentos++; } // Cima
            if(tecla == 80 && !celulaBloqueia(jogo, p2, p2.x+1, p2.y)) { p2.x++; p2.qtdMovimentos++; } // Baixo
            if(tecla == 75 && !celulaBloqueia(jogo, p2, p2.x, p2.y-1)) { p2.y--; p2.qtdMovimentos++; } // Esq
            if(tecla == 77 && !celulaBloqueia(jogo, p2, p2.x, p2.y+1)) { p2.y++; p2.qtdMovimentos++; } // Dir

            if(tecla == '0') {
                int ativas = 0;
                int indexLivre = -1;
                // Conta quantas bombas estão ativas e acha uma livre
                for(int i = 0; i < 5; i++) {
                    if(bombasP2[i].ativa || bombasP2[i].explosaoAtiva) ativas++;
                    else if(indexLivre == -1) indexLivre = i;
                }

                // Planta se não atingiu o limite do power-up
                if(ativas < p2.pus.qtdBombas && indexLivre != -1) {
                    bombasP2[indexLivre].ativa = true;
                    bombasP2[indexLivre].x = p2.x;
                    bombasP2[indexLivre].y = p2.y;
                    bombasP2[indexLivre].tempoPlantada = chrono::steady_clock::now();
                    bombasP2[indexLivre].ehRelogio = p2.pus.temRelogio;
                }
            }

            if(tecla == '1') {
                for(int i = 0; i < 5; i++) {
                    if(bombasP2[i].ativa && bombasP2[i].ehRelogio) {
                        bombasP2[i].ehRelogio = false;
                        bombasP2[i].tempoPlantada = chrono::steady_clock::now() - chrono::seconds(10);
                    }
                }
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



void movimentaInimigos(EstadoJogo& jogo, Inimigo inimigos[], Bomba bombasP1[], Bomba bombasP2[], Jogador& p1, Jogador& p2, unsigned selDificuldade){

    int chancePerseguicao;
    if(selDificuldade == 3)      chancePerseguicao = 75;
    else if(selDificuldade == 2) chancePerseguicao = 50;
    else                         chancePerseguicao = 0;

    for(int k = 0; k < jogo.inimigosAtivos; k++) {

        if(inimigos[k].vivo == false) continue;

        if(inimigos[k].passos == 0) {

            if(inimigos[k].boss == true) {
                Jogador* alvoBoss = &p1;
                if (jogo.modoJogo >= 2) {
                    if (!p1.vivo && p2.vivo) alvoBoss = &p2;
                    else if (p1.vivo && p2.vivo) {
                        int distP1 = abs(p1.x - inimigos[k].x) + abs(p1.y - inimigos[k].y);
                        int distP2 = abs(p2.x - inimigos[k].x) + abs(p2.y - inimigos[k].y);
                        if (distP2 < distP1) alvoBoss = &p2;
                    }
                }
                int diffX = alvoBoss->x - inimigos[k].x;
                int diffY = alvoBoss->y - inimigos[k].y;

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
                    Jogador* alvo = &p1;

                    if (jogo.modoJogo >= 2) {
                        if (!p1.vivo && p2.vivo) {
                            alvo = &p2;
                        } else if (p1.vivo && p2.vivo) {
                            int distP1 = abs(p1.x - inimigos[k].x) + abs(p1.y - inimigos[k].y);
                            int distP2 = abs(p2.x - inimigos[k].x) + abs(p2.y - inimigos[k].y);
                            if (distP2 < distP1) {
                                alvo = &p2;
                            }
                        }
                    }
                    int diffX = alvo->x - inimigos[k].x;
                    int diffY = alvo->y - inimigos[k].y;
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
        case 0: // Cima (x - 1)
            if(jogo.mapa[inimigos[k].x - 1][inimigos[k].y] == 0 &&
               !ehAreaPerigosa(jogo, inimigos[k].x - 1, inimigos[k].y, bombasP1, bombasP2, p1.pus.nivelFogo, p2.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x - 1, inimigos[k].y, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].x--;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 1: // Baixo (x + 1)
            if(jogo.mapa[inimigos[k].x + 1][inimigos[k].y] == 0 &&
               !ehAreaPerigosa(jogo, inimigos[k].x + 1, inimigos[k].y, bombasP1, bombasP2, p1.pus.nivelFogo, p2.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x + 1, inimigos[k].y, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].x++;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 2: // Esquerda (y - 1)
            if(jogo.mapa[inimigos[k].x][inimigos[k].y-1] == 0 &&
               !ehAreaPerigosa(jogo, inimigos[k].x, inimigos[k].y - 1, bombasP1, bombasP2, p1.pus.nivelFogo, p2.pus.nivelFogo) &&
               !temInimigoNaCasa(inimigos[k].x, inimigos[k].y-1, k, inimigos, jogo.inimigosAtivos)) {
                inimigos[k].y--;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 3: // Direita (y + 1)
            if(jogo.mapa[inimigos[k].x][inimigos[k].y+1] == 0 &&
               !ehAreaPerigosa(jogo, inimigos[k].x, inimigos[k].y + 1, bombasP1, bombasP2, p1.pus.nivelFogo, p2.pus.nivelFogo) &&
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
void destruiCaixasComDrop(EstadoJogo& jogo, Jogador& autor, Bomba& bomba) {
    int raio = 1 + autor.pus.nivelFogo;

    auto tentaDestruir = [&](int lx, int ly) -> bool {
        if(jogo.mapa[lx][ly] == 2) {
            jogo.mapa[lx][ly] = 0;
            autor.caixasDestruidas++;
            sorteiaDropPowerUp(jogo, lx, ly); // chance de dropar item
            return false;
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

// CORREÇÃO: Recebendo p1 e p2 para checar dano em ambos!
void detonaBomba(EstadoJogo& jogo, Bomba& bomba, Jogador& autor, Jogador& p1, Jogador& p2, Inimigo inimigos[]){

    if(bomba.ativa == true) {
        auto tempoAtual = chrono::steady_clock::now();
        auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoPlantada).count();

        if(bomba.ehRelogio == false && duracao >= 3000) {
            bomba.ativa = false;
            destruiCaixasComDrop(jogo, autor, bomba);
            int raio = 1 + autor.pus.nivelFogo;

            for(int k = 0; k < jogo.inimigosAtivos; k++) {
                if(inimigos[k].vivo == true) {
                    if(celulaNaExplosao(jogo, bomba, inimigos[k].x, inimigos[k].y, raio)) {
                        inimigos[k].vivo = false;
                        autor.inimigosAbatidos++;
                        autor.pontuacao = calculaPontuacao(autor);
                    }
                }
            }
            bomba.explosaoAtiva = true;
            bomba.tempoExplosao = chrono::steady_clock::now();

            // Verifica dano ao P1
            if(celulaNaExplosao(jogo, bomba, p1.x, p1.y, raio)) {
                if(p1.pus.escudos > 0) p1.pus.escudos--;
                else {
                    p1.pus.vidas--;
                    if(p1.pus.vidas <= 0) p1.vivo = false;
                    else { p1.x = 1; p1.y = 1; }
                }
            }
            // Verifica dano ao P2
            if(jogo.modoJogo >= 2 && celulaNaExplosao(jogo, bomba, p2.x, p2.y, raio)) {
                if(p2.pus.escudos > 0) p2.pus.escudos--;
                else {
                    p2.pus.vidas--;
                    if(p2.pus.vidas <= 0) p2.vivo = false;
                    else { p2.x = 1; p2.y = 2; }
                }
            }
        }
    }

    if(bomba.explosaoAtiva == true) {
        auto tempoAtual = chrono::steady_clock::now();
        auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoExplosao).count();
        if(duracao >= 500) bomba.explosaoAtiva = false;
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

void avancaFase(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba bombasP1[], Bomba bombasP2[], Inimigo inimigos[], unsigned selDificuldade) {
    jogo.fase++;
    tocaMusica(jogo.fase);
    jogo.portalAtivo = false;
    jogo.spawnaBoss = false;
    carregaMapa(jogo);

    p1.x = 1;
    p1.y = 1;
    p1.vivo = true;
    for(int i = 0; i < 5; i++) {
        bombasP1[i].ativa = false;
        bombasP1[i].explosaoAtiva = false;
        bombasP1[i].ehRelogio = false;

        bombasP2[i].ativa = false;
        bombasP2[i].explosaoAtiva = false;
        bombasP2[i].ehRelogio = false;
    }



    if(jogo.modoJogo == 2) {
        p2.x = 1;
        p2.y = 2;
        p2.vivo = true;
    }

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

void verificaFim(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba bombasP1[], Bomba bombasP2[], Inimigo inimigos[], unsigned selDificuldade){
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

    // Verifica se há alguma bomba explodindo no momento
    bool temExplosao = false;
    for(int i = 0; i < 5; i++) {
        if(bombasP1[i].explosaoAtiva || bombasP2[i].explosaoAtiva) temExplosao = true;
    }

    if(inimigosMortos == jogo.inimigosAtivos && !temExplosao) {
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
                imprimeMapa(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);
                auto inicioPausa = chrono::steady_clock::now();
                while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {}
                jogo.rodando = false;
            }
        } else {
            jogo.portalAtivo = true;
            jogo.mapa[jogo.portalX][jogo.portalY] = 0;
        }
    }

    // Se ALGUÉM pisou no portal, avança
    if(jogo.portalAtivo && ((p1.vivo && p1.x == jogo.portalX && p1.y == jogo.portalY) || (p2.vivo && p2.x == jogo.portalX && p2.y == jogo.portalY))) {
            #ifdef _WIN32
            COORD coord; coord.X = 0; coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            cout << "\033[H";
        #endif
        imprimeMapa(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);

        cout << "\n\n\t\033[36m AVANCANDO PARA A FASE " << jogo.fase + 1 << " EM: \033[0m";
        contagemRecursiva(3);

        jogo.portalAtivo = false;
        avancaFase(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);
    }

    // GAME OVER SOMENTE SE AMBOS MORREREM
    if(p1.vivo == false && p2.vivo == false && !temExplosao){
        #ifdef _WIN32
            COORD coord; coord.X = 0; coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            cout << "\033[H";
        #endif
        imprimeMapa(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);
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

void salvaRanking(Jogador p1, Jogador p2, EstadoJogo jogo) {

    auto tempoFinal = chrono::steady_clock::now();
    int tempoTotal = chrono::duration_cast<chrono::seconds>(tempoFinal - jogo.tempoInicio).count();

    time_t t = time(0);
    tm* now = localtime(&t);
    char dataAtual[11];
    strftime(dataAtual, sizeof(dataAtual), "%d/%m/%Y", now);

    auto salva = [&](Jogador& p, string nome) {
        ofstream arqRank;
        arqRank.open("ranking.txt", ios::app);
        if(arqRank.is_open()) {
            arqRank << dataAtual << "\t" << nome << "\t" << tempoTotal << "\t"
                    << p.qtdMovimentos << "\t" << p.bombasUsadas << "\t" << p.pontuacao << "\n";
            arqRank.close();
        } else {
            cout << "Erro ao salvar!!!" << endl;
        }
    };

    string nome1;
    cout << "\n\n\nP1 - DIGITE SEU PRIMEIRO NOME: ";
    cout << "\033[J";
    cin >> nome1;
    salva(p1, nome1);

    if(jogo.modoJogo == 2) {
        string nome2;
        cout << "P2 - DIGITE SEU PRIMEIRO NOME: ";
        cout << "\033[J";
        cin >> nome2;
        salva(p2, nome2);
    }
}

void resetaJogo(EstadoJogo& jogo, Jogador& p1, Jogador& p2, Bomba bombasP1[], Bomba bombasP2[], Inimigo inimigos[], unsigned selDificuldade){
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

    if (jogo.modoJogo == 2) {
        p2.vivo = true;
        p2.x = 1;
        p2.y = 2;
    } else {
        p2.vivo = false;
        p2.x = 0;
        p2.y = 0;
    }
    p2.qtdMovimentos = 0;
    p2.bombasUsadas = 0;
    p2.pontuacao = 0;
    p2.inimigosAbatidos = 0;

    for(int i = 0; i < 5; i++) {
        bombasP1[i].ativa = false;
        bombasP1[i].explosaoAtiva = false;
        bombasP1[i].ehRelogio = false;

        bombasP2[i].ativa = false;
        bombasP2[i].explosaoAtiva = false;
        bombasP2[i].ehRelogio = false;
    }


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
    Bomba bombasP1[5];
    Bomba bombasP2[5];

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
                    // --- SUB-MENU DO MODO DE JOGO ---
                    do {
                        #ifdef _WIN32
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                            cout << "\033[H";
                        #endif
                        imprimeTela();
                        cout << "\033[J";
                        cout << "\nSelecione o Modo de Jogo:\n";
                        cout << "1- 1 Jogador\n";
                        cout << "2- 2 Jogadores (Cooperativo)\n";
                        cout << "3- PC vs PC\n";
                        cout << "Escolha: ";
                        cin >> jogo.modoJogo;

                        if(cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            jogo.modoJogo = 0;
                        }
                    } while(jogo.modoJogo < 1 || jogo.modoJogo > 3);

                    // Prepara o jogo para qualquer um dos 3 modos
                    resetaJogo(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);

                    while(jogo.rodando == true) {
                        #ifdef _WIN32
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                                cout << "\033[H";
                        #endif

                        imprimeMapa(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);

                        // --- VERIFICA QUEM ESTÁ JOGANDO ---
                        static auto tempoBots = chrono::steady_clock::now(); // Cria o relógio do bot

                        if (jogo.modoJogo == 1 || jogo.modoJogo == 2) {
                            executaMovimentos(jogo, p1, p2, bombasP1, bombasP2);
                        } else if (jogo.modoJogo == 3) {
                            auto tempoAtual_bots = chrono::steady_clock::now();
                            // O bot só pensa e age a cada 250 milissegundos
                            if(chrono::duration_cast<chrono::milliseconds>(tempoAtual_bots - tempoBots).count() >= 250) {
                                movimentaIA(jogo, p1, bombasP1, bombasP2, p1.pus.nivelFogo, p2.pus.nivelFogo, inimigos);
                                movimentaIA(jogo, p2, bombasP2, bombasP1, p2.pus.nivelFogo, p1.pus.nivelFogo, inimigos);
                                coletaPowerUp(jogo, p1);
                                coletaPowerUp(jogo, p2);
                                tempoBots = chrono::steady_clock::now(); // Reseta o timer
                            }
                        }

                        this_thread::sleep_for(chrono::milliseconds(30));

                        auto tempoAtual_inimigos = chrono::steady_clock::now();
                        auto duracaoInimigos = chrono::duration_cast < chrono::milliseconds>(tempoAtual_inimigos - tempoInimigos).count();

                        // Define a velocidade baseada na dificuldade escolhida
                        int velocidadeInimigos = 500;
                        if (selDificuldade == 1)      velocidadeInimigos = 500; // Fácil: Inimigos lerdos
                        else if (selDificuldade == 2) velocidadeInimigos = 350; // Médio: Velocidade normal
                        else if (selDificuldade == 3) velocidadeInimigos = 200; // Difícil: Inimigos muito rápidos! (Hardcore)

                        if(duracaoInimigos >= velocidadeInimigos) {
                            movimentaInimigos(jogo, inimigos, bombasP1, bombasP2, p1, p2, selDificuldade);
                            tempoInimigos = chrono::steady_clock::now();
                        }

                        for(int i = 0; i < 5; i++) {
                            detonaBomba(jogo, bombasP1[i], p1, p1, p2, inimigos);
                            detonaBomba(jogo, bombasP2[i], p2, p1, p2, inimigos);
                        }

                        verificaFim(jogo, p1, p2, bombasP1, bombasP2, inimigos, selDificuldade);
                    }

                    // --- TELA DE FIM DE JOGO E RANKING ---
                    #ifdef _WIN32
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    #else
                        cout << "\033[H";
                    #endif

                    imprimeTela(jogo.vencedor);
                    if (jogo.modoJogo != 3) { // Se foram bots jogando, não faz sentido salvar no ranking
                        salvaRanking(p1, p2, jogo);
                    }

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
                    break; // Fim do Case 1 do Menu Principal

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

                        cout << "\033[33mMODOS DE JOGO:\033[0m\n";
                        cout << "  1 - 1 Jogador          -> Voce contra os inimigos\n";
                        cout << "  2 - 2 Jogadores (Coop) -> P1 (WASD) e P2 (Setas) juntos\n";
                        cout << "  3 - PC vs PC           -> Dois bots jogam automaticamente\n";

                        cout << "\n\033[33mCONTROLES - JOGADOR 1:\033[0m\n";
                        cout << "  W  -> Mover para cima\n";
                        cout << "  S  -> Mover para baixo\n";
                        cout << "  A  -> Mover para esquerda\n";
                        cout << "  D  -> Mover para direita\n";
                        cout << "  X  -> Plantar bomba\n";
                        cout << "  C  -> Detonar bomba-relogio\n";

                        cout << "\n\033[33mCONTROLES - JOGADOR 2:\033[0m\n";
                        cout << "  Seta Cima    -> Mover para cima\n";
                        cout << "  Seta Baixo   -> Mover para baixo\n";
                        cout << "  Seta Esquerda-> Mover para esquerda\n";
                        cout << "  Seta Direita -> Mover para direita\n";
                        cout << "  0            -> Plantar bomba\n";
                        cout << "  1            -> Detonar bomba-relogio\n";

                        cout << "\n\033[33mITENS DO MAPA:\033[0m\n";
                        cout << "  \033[42m👳🏻‍♂️\033[0m  Jogador 1\n";
                        cout << "  \033[42m🥷\033[0m  Jogador 2\n";
                        cout << "  \033[42m👹\033[0m  Inimigo comum - evite o contato!\n";
                        cout << "  \033[42m👺\033[0m  Boss (fase 3) - persegue voce sempre!\n";
                        cout << "  \033[42m💣\033[0m  Bomba plantada - explode em 3 segundos.\n";
                        cout << "  \033[103m💥\033[0m  Explosao - mata inimigos e destroi caixas.\n";
                        cout << "  \033[42m🧱\033[0m  Caixa destruivel pela bomba.\n";
                        cout << "  \033[47m  \033[0m  Parede solida - nao e destruivel.\n";
                        cout << "  \033[45m🕌\033[0m  Portal - aparece ao eliminar todos os inimigos.\n";

                        cout << "\n\033[33mPOWER-UPS (dropam de caixas destruidas - 40%% de chance):\033[0m\n";
                        cout << "  🔥 Fogo+     -> Aumenta raio de explosao (+1, cumulativo)\n";
                        cout << "  💣 Bomba+    -> Aumenta qtd de bombas simultaneas (cumulativo)\n";
                        cout << "  ❤️  Vida+     -> Vida extra, sobrevive a mais um dano (cumulativo)\n";
                        cout << "  ⏰ Relogio  -> Bomba so explode ao detonar manualmente (C / tecla 1)\n";
                        cout << "  🛡️  Escudo    -> Absorve um dano de bomba ou inimigo\n";
                        cout << "  👻 Fantasma -> Atravessa caixas destruiveis\n";
                        cout << "  OBS: power-ups RESETAM ao avancar de fase!\n";

                        cout << "\n\033[33mOBJETIVO:\033[0m\n";
                        cout << "  Elimine todos os inimigos para abrir o portal e avance de fase!\n";
                        cout << "  Sobreviva ate a fase 3 e derrote o Boss para vencer!\n";
                        cout << "  Cuidado para nao se explodir!\n";

                        cout << "\n\033[33mDIFICULDADE:\033[0m\n";
                        cout << "  Facil        -> 3 inimigos, movimento aleatorio, velocidade lenta\n";
                        cout << "  Intermediario-> 5 inimigos, 50%% de chance de perseguir\n";
                        cout << "  Dificil      -> 7 inimigos, 75%% de chance de perseguir, muito rapidos\n";

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
