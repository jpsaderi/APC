#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define NEGRITO "\033[1m"
#define RESETCOLOR "\033[0m"

#define TRUE 1
#define FALSE 0

#ifndef _WIN32
#include <termios.h>
#include <fcntl.h>

int kbhit(){
	struct termios oldt, newt;
	int ch, oldf;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch,stdin);
		return 1;
	}
	return 0;
}

int getch(void) {
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#else
	#include <conio.h>
#endif





int Altura = 13 , Largura = 8;
char Mat[50][50];
int pos1, pos2, pos_x1, pos_x2, pos_y1, pos_y2;
int Pontuacao = 0;
int Perdeu = FALSE;

void Clear(){
	printf("\033c");
}

void Inicializar_matriz(){
	int i, j;
	for(i = 0; i < Altura; i++){
		for(j = 0; j < Largura; j++){
			if(j == 0 || j == Largura-1 || i == Altura-1){
				Mat[i][j] = '#';
			}
			else{
				Mat[i][j] = ' ';
			}
		}
	}
}


int Aleatorio_Letra(){
	int num;
	num = rand()%5;
	return num;
}
int Aleatorio_Posicao(){
	int num;
	num = (rand()%(Largura-3))+1;
	return num;
}

char EscolheLetra(){
	int cor = Aleatorio_Letra();
	switch(cor){
		case 0 : return 'A';
				 break;
		case 1 : return 'B';
				 break;
		case 2 : return 'C';
				 break;
		case 3 : return 'D';
				 break;
		case 4 : return 'E';
				 break;
		default : break;	
	}
}

void CriarLetras(){
	char letra1, letra2;
	letra1 = EscolheLetra();
	letra2 = EscolheLetra();

	pos1 = Aleatorio_Posicao();
	pos2 = pos1 +1;

	if(Mat[0][pos1] == ' ' && Mat[0][pos2] == ' '){
		Mat[0][pos1] = letra1;
		Mat[0][pos2] = letra2;
		pos_x1 = pos1;
		pos_x2 = pos2;
		pos_y1 = 0;
		pos_y2 = 0;	
	}
	else{
		Perdeu = TRUE;
	}
}

void TrocarLetras(){
	Vet[]
}

void DescerLetras(){
	int chegoufim1, chegoufim2;
	int x1, x2, y1, y2;
	x1 = pos1;
	x2 = pos2
	y1 = 0;
	y2 = 0;

	if()

}

int DescerLetra(){
	int achou=0,achoumelhor=0;
	/*verifica se o termo depois dele eh um
	espaco vazio e se for faz ela descer*/
	if (y1==0 || y2==0){
		verifverti=0;
	}
	if (verifverti == 0){  // horizontal
		if (matriz[y1+1][x1] == ' '){
			matriz[y1+1][x1] = matriz[y1][x1];
			matriz[y1][x1] = ' ';
			y1++;
		}		
		else
			achou=1;
		if (matriz[y2+1][x2] == ' '){
			matriz[y2+1][x2] = matriz[y2][x2];
			matriz[y2][x2] = ' ';
			y2++;
		}
		else
			achoumelhor=1;
		if (achou && achoumelhor){
			if(!CriaLetra(matriz)){
				return 0;
			}
			return 1;
		}
		return 1;
	}
	else{
		if (matriz[y2+1][x2] == ' '){
			matriz[y2+1][x2] = matriz[y2][x2];
			matriz[y2][x2] = ' ';
			y2++;
		}
		else
			achou=1;
		if (matriz[y1][x1+1] == ' '){
			matriz[y1][x1+1] = matriz[y1-1][x1+1];
			matriz[y1-1][x1+1] = ' ';
			y1++;
		}
		else
			achoumelhor=1;
		if (achou && achoumelhor){
			if(!CriaLetra(matriz)){
				return 0;
			}
			return 1;
		}
		return 1;
	}
}






//void MoverDireita(int Vet[][], int )




// Verificar_lados(char Vet[][], int pos_x1, int pos_y1, char letra){
// 	if(Vet[pos_x1][pos_y1] == letra){

// 		return Verificar_lados(Vet[][], pos_x1+1, pos_y1, letra);
// 	}


// }


void Imprimir_matriz(){
	int i, j;

	printf("%d\n", Pontuacao);
	for(i = 0; i < Altura; i++){
		for (j = 0; j < Largura; j++){
			if(Mat[i][j] == 'A'){
				printf(VERMELHO"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'B'){
				printf(VERDE"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'C'){
				printf(AMARELO"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'D'){
				printf(AZUL"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'E'){
				printf(MAGENTA"%c "RESETCOLOR, Mat[i][j]);
			}
			else{
				printf("%c ", Mat[i][j]);
			}
		}
		printf("\n");
	}
}



int main(){
	int letra1, letra2, i;
	srand(time(NULL));
	Inicializar_matriz();
	for(i = 0; i < 20 && Perdeu == FALSE; i++){
		Clear();
		CriarLetras();
		usleep(500000);
		Imprimir_matriz();
	}


	return 0;
}