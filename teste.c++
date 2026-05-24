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

double calculaPontuacao(Jogador& p1) {
    // PONTOS BASE
    double pontosBase = (p1.inimigosAbatidos * 100) + (p1.caixasDestruidas * 10);

    // BÔNUS DE EFICIÊNCIA DE BOMBAS
    double bonusBomba = 1.0;
    if(p1.bombasUsadas > 0) {
        double relacao = (double)p1.inimigosAbatidos / p1.bombasUsadas;
        if(relacao >= 1.0)       bonusBomba = 2.0;  // matou mais de 1 inimigo por bomba
        else if(relacao >= 0.5)  bonusBomba = 1.5;  // matou 1 inimigo a cada 2 bombas
        else                     bonusBomba = 1.0;  // abaixo disso, sem bônus
    }

    // PENALIDADE DE MOVIMENTOS
    double penalidade = 1.0;
    int excesso = p1.qtdMovimentos / 50;
    if(excesso > 8) excesso = 8;
    penalidade = 1.0 - (excesso * 0.05);

    // CÁLCULO FINAL
    return pontosBase * bonusBomba * penalidade;
}

// procedimento para desenhar o mapa do jogo
void imprimeMapa(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[], unsigned selDificuldade = 1) {

    string corChao = "\033[42m"; // Verde Fase 1
    if (jogo.fase == 2) corChao = "\033[46m"; // Azul Fase 2
    if (jogo.fase == 3) corChao = "\033[100m"; // Cinza Escuro Fase 3

	for(int i=0; i<19; i++) {
		for(int j=0; j<25; j++) {

			if(bomba.explosaoAtiva == true && jogo.mapa[i][j] != 1 && (i == bomba.x && j == bomba.y || i == bomba.x - 1 && j == bomba.y || i == bomba.x + 1 && j == bomba.y ||  i == bomba.x && j == bomba.y - 1 || i == bomba.x && j == bomba.y + 1)) {
				cout << "\033[103m💥\033[0m";

			}else if(i==p1.x && j==p1.y) {
				if(p1.vivo == true){
                    cout<< corChao << "👳🏻‍♂️\033[0m";
				}else{
                    cout<< corChao<< "🪦\033[0m";
				}

			}else if(bomba.ativa == true && i==bomba.x && j==bomba.y) {
				cout << corChao << "💣\033[0m";

			}else if(jogo.portalAtivo && i == jogo.portalX && j == jogo.portalY) {
                cout << "\033[45m🕌\033[0m";
                continue;
			}else{
                bool inimigoAqui = false;
				bool ehBoss = false; // <-- Nova variavel para checar se o inimigo é o boss
				for(int k = 0; k < jogo.inimigosAtivos; k++) {
					if(inimigos[k].vivo == true && i == inimigos[k].x && j == inimigos[k].y) {
						inimigoAqui = true;
						if(inimigos[k].boss == true) ehBoss = true; // Salva a identidade dele
						break; // Otimizaçao: ja achou o inimigo, pode parar de procurar nessa casa
					}
				}

				if(inimigoAqui == true) {
					if(ehBoss) cout << corChao << "👺"; // Emoji exclusivo do Boss!
					else cout << corChao << "👹";       // Inimigo comum
				}else{
					switch (jogo.mapa[i][j]) {
					case 0:
						cout<< corChao << "  \033[0m";
						break;
					case 1:
						cout<< "\033[47m  \033[0m";
						break;
					case 2:
						cout<< corChao << "🧱\033[0m";
						break;
					}
				}
			}

		}
		cout<<"\n";
	}
	cout << "\033[33mDIFICULDADE: ";
	if(selDificuldade == 3){
        cout << "Dificil";
	}else if(selDificuldade == 2){
        cout << "Intermediario";
	}else{
        cout << "Facil";
	}


	auto tempoAtual = chrono::steady_clock::now();
	int tempoDecorrido = chrono::duration_cast<chrono::seconds>(tempoAtual - jogo.tempoInicio).count();

	int minutos = tempoDecorrido / 60;
	int segundos = tempoDecorrido % 60;

	cout << "\t\033[33m" << "TEMPO DE JOGO: ";

	if (minutos > 0) {
	    cout << minutos << "m ";
	    if (segundos < 10) cout << "0";
	}
	if (minutos <= 0) {
	    cout << "00m ";
	    if (segundos < 10) cout << "0";
	}
	cout << segundos << "s ";

	cout << "\n\033[36mMOVIMENTOS: " << p1.qtdMovimentos << " | INIMIGOS ABATIDOS: " << p1.inimigosAbatidos << "\nBOMBAS USADAS: " << p1.bombasUsadas << " | PONTOS: " << p1.pontuacao << "\033[0m";
	cout << "\033[J";
}

// procedimento para executar as acoes do jogador no mapa
void executaMovimentos(EstadoJogo& jogo, Jogador& p1, Bomba& bomba) {
	char tecla;

	if(p1.vivo == true){
        if ( _kbhit() ) {
            tecla = getch();
            switch(tecla)
            {
            case 72:
            case 'w':
                if(jogo.mapa[p1.x-1][p1.y] == 0) {
                    p1.x--;
                    p1.qtdMovimentos++;
                }
                break;
            case 80:
            case 's':
                if(jogo.mapa[p1.x+1][p1.y] == 0) {
                    p1.x++;
                    p1.qtdMovimentos++;
                }
                break;
            case 75:
            case 'a':
                if(jogo.mapa[p1.x][p1.y-1] == 0) {
                    p1.y--;
                    p1.qtdMovimentos++;
                }
                break;
            case 77:
            case 'd':
                if(jogo.mapa[p1.x][p1.y+1] == 0) {
                    p1.y++;
                    p1.qtdMovimentos++;
                }
                break;
            case 88:
            case 'x':
                if(bomba.ativa == false && bomba.explosaoAtiva == false) {
                    bomba.ativa = true;
                    bomba.x = p1.x;
                    bomba.y = p1.y;
                    p1.bombasUsadas++;
                    bomba.tempoPlantada = chrono::steady_clock::now();
                }
                break;

            }
        }
	}
}

// procedimento para movimentar os inimigos no mapa      //Alterar Aqui a dificuldade
void movimentaInimigos(EstadoJogo& jogo, Inimigo inimigos[], Bomba& bomba, Jogador& p1, unsigned selDificuldade) {

    // Define a chance de perseguição baseada na dificuldade
    int chancePerseguicao;
    if(selDificuldade == 3) {
        chancePerseguicao = 75; // Difícil: 75% de chance
    } else if(selDificuldade == 2) {
        chancePerseguicao = 50; // Intermediário: 50% de chance
    } else {
        chancePerseguicao = 0;  // Fácil: sem perseguição
    }

    for(int k = 0; k < jogo.inimigosAtivos; k++) {

        // Ignora inimigos mortos
        if(inimigos[k].vivo == false) {
            continue;
        }

        // Só escolhe nova direção quando os passos acabam
        if(inimigos[k].passos == 0) {

            if(inimigos[k].boss == true) {
                // Inteligencia do Boss: Tenta o caminho mais direto, se tiver bloqueado, tenta "deslizar" pelo outro eixo
                int diffX = p1.x - inimigos[k].x;
                int diffY = p1.y - inimigos[k].y;

                int dirX = (diffX > 0) ? 1 : 0; // 1 = Baixo, 0 = Cima
                int dirY = (diffY > 0) ? 3 : 2; // 3 = Direita, 2 = Esquerda

                // Simula se as proximas casas nas direcoes desejadas estao livres (chao = 0)
                int proxX = inimigos[k].x + (dirX == 1 ? 1 : -1);
                int proxY = inimigos[k].y + (dirY == 3 ? 1 : -1);

                bool livreX = (jogo.mapa[proxX][inimigos[k].y] == 0);
                bool livreY = (jogo.mapa[inimigos[k].x][proxY] == 0);

                // Decide o movimento
                if(abs(diffX) >= abs(diffY)) {
                    if(livreX) inimigos[k].direcao = dirX;          // Vai reto
                    else if(livreY) inimigos[k].direcao = dirY;     // Desvia pelo lado
                    else inimigos[k].direcao = rand() % 4;          // Encurralado (tenta sortear p/ desbugar)
                } else {
                    if(livreY) inimigos[k].direcao = dirY;          // Vai reto
                    else if(livreX) inimigos[k].direcao = dirX;     // Desvia pelo lado
                    else inimigos[k].direcao = rand() % 4;          // Encurralado (tenta sortear p/ desbugar)
                }
            } else if(selDificuldade == 1) {
                // FÁCIL: sempre aleatório
                inimigos[k].direcao = rand() % 4;

            } else {
                // INTERMEDIÁRIO E DIFÍCIL: sorteio de perseguição
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

        // Executa o movimento na direção escolhida
        switch(inimigos[k].direcao) {
        case 0: // Cima
            if(jogo.mapa[inimigos[k].x - 1][inimigos[k].y] == 0 &&
                (bomba.ativa == false || (inimigos[k].x - 1 != bomba.x || inimigos[k].y != bomba.y))) {
                inimigos[k].x--;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 1: // Baixo
            if(jogo.mapa[inimigos[k].x + 1][inimigos[k].y] == 0 &&
                (bomba.ativa == false || (inimigos[k].x + 1 != bomba.x || inimigos[k].y != bomba.y))) {
                inimigos[k].x++;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 2: // Esquerda
            if(jogo.mapa[inimigos[k].x][inimigos[k].y - 1] == 0 &&
                (bomba.ativa == false || (inimigos[k].x != bomba.x || inimigos[k].y - 1 != bomba.y))) {
                inimigos[k].y--;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        case 3: // Direita
            if(jogo.mapa[inimigos[k].x][inimigos[k].y + 1] == 0 &&
                (bomba.ativa == false || (inimigos[k].x != bomba.x || inimigos[k].y + 1 != bomba.y))) {
                inimigos[k].y++;
                inimigos[k].passos--;
            } else {
                inimigos[k].passos = 0;
            }
            break;
        }
    }
}
//procedimento para inicializar os inimigos no jogo
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
                if((sorteioLinha == p1.x && sorteioColuna == p1.y) || (sorteioLinha == p1.x +1 && sorteioColuna == p1.y) || (sorteioLinha == p1.x && sorteioColuna == p1.y +1) || (sorteioLinha == p1.x +2 && sorteioColuna == p1.y) || (sorteioLinha == p1.x && sorteioColuna == p1.y +2)){
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

// procedimento para escolher aleatoriamente a posicao das paredes frageis
void sorteiaFrageis(EstadoJogo& jogo, Jogador& p1){
    int cont = 0, sorteioLinha, sorteioColuna;
    bool areaLivre = false;

    while(cont < 50) {
		sorteioLinha = rand() % 19;
		sorteioColuna = rand() %  25;

		if (jogo.mapa[sorteioLinha][sorteioColuna] == 0) {
			areaLivre = true;

			if((sorteioLinha == p1.x && sorteioColuna == p1.y) || (sorteioLinha == p1.x +1 && sorteioColuna == p1.y) || (sorteioLinha == p1.x && sorteioColuna == p1.y +1))
				areaLivre = false;



                if(areaLivre == true) {
                    jogo.mapa[sorteioLinha][sorteioColuna] = 2;
                    cont++;
			}
		}
	}
}

// procedimento que conta o timer da bomba e ao desativa-la aplica seus efeitos
void detonaBomba(EstadoJogo& jogo, Bomba& bomba, Jogador& p1, Inimigo inimigos[]){

    if(bomba.ativa == true) {
			auto tempoAtual = chrono::steady_clock::now();
            auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoPlantada).count();

			if(duracao >= 3000) {
				bomba.ativa = false;

				if(jogo.mapa[bomba.x-1][bomba.y] == 2) {
                        jogo.mapa[bomba.x-1][bomba.y] = 0;
                        p1.caixasDestruidas++;
                }
                if(jogo.mapa[bomba.x+1][bomba.y] == 2) {
                    jogo.mapa[bomba.x+1][bomba.y] = 0;
                    p1.caixasDestruidas++;
            }
                if(jogo.mapa[bomba.x][bomba.y-1] == 2) {
                    jogo.mapa[bomba.x][bomba.y-1] = 0;
                    p1.caixasDestruidas++;
                }
                if(jogo.mapa[bomba.x][bomba.y+1] == 2) {
                    jogo.mapa[bomba.x][bomba.y+1] = 0;
                    p1.caixasDestruidas++;
                }

				for(int k = 0; k < jogo.inimigosAtivos; k++) {
					if(inimigos[k].vivo == true) {
						if(inimigos[k].x == bomba.x && inimigos[k].y == bomba.y || inimigos[k].x == bomba.x - 1 && inimigos[k].y == bomba.y || inimigos[k].x == bomba.x + 1 && inimigos[k].y == bomba.y || inimigos[k].x == bomba.x && inimigos[k].y == bomba.y - 1 || inimigos[k].x == bomba.x && inimigos[k].y == bomba.y + 1) {
							inimigos[k].vivo = false;
							p1.inimigosAbatidos++;
							p1.pontuacao = calculaPontuacao(p1);
						}
					}
				}

				bomba.explosaoAtiva = true;
				bomba.tempoExplosao = chrono::steady_clock::now();

				if(bomba.x == p1.x && bomba.y == p1.y) p1.vivo = false;
				if(bomba.x -1 == p1.x && bomba.y == p1.y) p1.vivo = false;
				if(bomba.x +1 == p1.x && bomba.y == p1.y) p1.vivo = false;
				if(bomba.x == p1.x && bomba.y -1 == p1.y) p1.vivo = false;
				if(bomba.x == p1.x && bomba.y +1 == p1.y) p1.vivo = false;
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

void avancaFase(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[], unsigned selDificuldade) {
    jogo.fase++;
    jogo.portalAtivo = false;
    jogo.spawnaBoss = false;
    carregaMapa(jogo);

    p1.x = 1;
    p1.y = 1;
    bomba.ativa = false;
    bomba.explosaoAtiva = false;

    // Todas as fases agora começam com caixas e inimigos normais!
    if(selDificuldade == 1) jogo.inimigosAtivos = 3;
    else if(selDificuldade == 2) jogo.inimigosAtivos = 5;
    else jogo.inimigosAtivos = 7;

    for(int k = 0; k < jogo.inimigosAtivos; k++) inimigos[k].boss = false;

    sorteiaFrageis(jogo, p1);
    inicializaInimigos(jogo, inimigos, p1);

    // ATENCAO: Apagamos o jogo.tempoInicio daqui para não resetar o Ranking!
}
void contagemRecursiva(int segundos) {
    if (segundos == 0) {
        cout << "\033[33m 0!\033[0m\n";
        auto inicioPausa = chrono::steady_clock::now();
        while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 500) {}
        return;
    }

    cout << "\033[33m" << segundos << "...\033[0m ";

    // Pausa de 1 segundo
    auto inicioPausa = chrono::steady_clock::now();
    while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {}

    contagemRecursiva(segundos - 1);
}
// procedimento para verificar se as condicoes de vitoria ou derrota foram atingidas
void verificaFim(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[], unsigned selDificuldade){
    int inimigosMortos = 0;
    for(int k = 0; k < jogo.inimigosAtivos; k++){
        if(inimigos[k].vivo == true && inimigos[k].x == p1.x && inimigos[k].y == p1.y) p1.vivo = false;
        if(inimigos[k].vivo == false) inimigosMortos++;
    }

    if(inimigosMortos == jogo.inimigosAtivos && bomba.explosaoAtiva == false) {
        if(jogo.fase == 3) {
            if(jogo.spawnaBoss == false) {
                // O Boss nasce no mapa!
                jogo.spawnaBoss = true;
                jogo.inimigosAtivos = 1;
                inimigos[0].vivo = true;
                inimigos[0].boss = true;
                inimigos[0].x = 17;
                inimigos[0].y = 23;
                inimigos[0].passos = 0;
                inimigos[0].direcao = 0;
            } else {
                // Boss morreu = vitória final
                #ifdef _WIN32
                    COORD coord; coord.X = 0; coord.Y = 0;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                #else
                    cout << "\033[H";
                #endif
                jogo.vencedor = true;
                imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);
                auto inicioPausa = chrono::steady_clock::now();
                while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {}
                jogo.rodando = false;
            }
        } else {
            jogo.portalAtivo = true; // Fases 1 e 2: ativa o portal
        }
    }

    // Jogador entrou no portal (Com transicao suave para nao ser abrupto)
    // Jogador entrou no portal (Com animação e recursividade)
    if(jogo.portalAtivo && p1.x == jogo.portalX && p1.y == jogo.portalY) {

        // 1. Força a impressão da tela para MOSTRAR o jogador no portal
        #ifdef _WIN32
            COORD coord; coord.X = 0; coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            cout << "\033[H";
        #endif
        imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);

        // 2. Aciona o texto e a função recursiva
        cout << "\n\n\t\033[36m AVANCANDO PARA A FASE " << jogo.fase + 1 << " EM: \033[0m";
        contagemRecursiva(3);

        // 3. Muda a fase de fato
        jogo.portalAtivo = false;
        avancaFase(jogo, p1, bomba, inimigos, selDificuldade);
    }

    if(p1.vivo == false && bomba.explosaoAtiva == false){
        #ifdef _WIN32
            COORD coord; coord.X = 0; coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            cout << "\033[H";
        #endif
        imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);
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
// procedimento que desenha a tela final
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

void resetaJogo(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[], unsigned selDificuldade){
    cout << "\033[J";
    p1.caixasDestruidas = 0;


    jogo.fase=1;
    if(selDificuldade == 1) jogo.inimigosAtivos = 3;
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
    bomba.ativa = false;
    bomba.explosaoAtiva = false;
    bomba.tempoExplosao = chrono::steady_clock::now();
    bomba.tempoPlantada = chrono::steady_clock::now();
    bomba.x = 0;
    bomba.y = 0;
    jogo.portalAtivo = false;
    jogo.portalX = 9;
    jogo.portalY = 12;

    sorteiaFrageis(jogo, p1);

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
        PlaySound(TEXT("musica.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    #endif

	EstadoJogo jogo;
    Jogador p1;
    Bomba bomba;
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
                    resetaJogo(jogo, p1, bomba, inimigos, selDificuldade);

                    while(jogo.rodando == true) {
                        #ifdef _WIN32
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                                cout << "\033[H";
                        #endif

                                imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);

                                executaMovimentos(jogo, p1, bomba);

                                auto tempoAtual_inimigos = chrono::steady_clock::now();
                                auto duracaoInimigos = chrono::duration_cast < chrono::milliseconds>(tempoAtual_inimigos - tempoInimigos).count();

                                if(duracaoInimigos >= 500) {
                                    movimentaInimigos(jogo, inimigos, bomba,p1,selDificuldade);
                                    tempoInimigos = chrono::steady_clock::now();
                                }

                                detonaBomba(jogo, bomba, p1, inimigos);

                                verificaFim(jogo, p1, bomba, inimigos, selDificuldade);

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
                        while(_kbhit()) {
                            getch();
                        }
                        cin.clear();
                        getch();
                        #ifdef _WIN32
                            system ("cls");
                        #else
                            system ("clear");
                        #endif
                        cout << "\033[2J\033[H";
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
                        if(selDificuldade == 1){
                            jogo.inimigosAtivos = 3;
                        }
                        if(selDificuldade == 2){
                            jogo.inimigosAtivos = 5;
                        }
                        if(selDificuldade == 3){
                            jogo.inimigosAtivos = 7;
                        }

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
                    cout << "  \033[47m  \033[0m  Parede solida - não e destruivel.\n";

                    cout << "\n\033[33mOBJETIVO:\033[0m\n";
                    cout << "  Elimine todos os inimigos usando bombas para vencer!\n";
                    cout << "  Cuidado para nao se explodir!\n";

                    cout << "\n\033[33mDIFICULDADE:\033[0m\n";
                    cout << "  Facil        -> 3 inimigos, movimento aleatorio\n";
                    cout << "  Intermediario-> 5 inimigos, 50% de chance de te perseguir\n";
                    cout << "  Dificil      -> 7 inimigos, 75% de chance de te perseguir\n";

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
                                    troca(lista[j], lista[j+1]); // O Template agindo aqui!
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
