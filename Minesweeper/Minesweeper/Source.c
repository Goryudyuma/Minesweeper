#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define tate 16
#define yoko 16
#define bakudan 40

#define kara 0
#define bomb -1
#define hata -2
#define kara2 -3

int masu[tate+2][yoko+2][2];
int okimasu=0;
int endflag = 0;

void zyunbi(){
	int i, j;
	endflag = 0;
	for (i = 0; i < tate+2; i++){
		for (j = 0; j < yoko+2; j++){
			masu[i][j][0] = kara;
			masu[i][j][1] = kara2;
		}
	}
}

int kuri_han(int okimasu2){
	int i, j;
	for (i = -1; i <= 1; i++){
		for (j = -1; j <= 1; j++){
			if (!(i == 0 && j == 0)){
				masu[okimasu2 / 100][okimasu2 % 100][1] = masu[okimasu2 / 100][okimasu2 % 100][0];
				if (masu[okimasu2 / 100][okimasu2 % 100][1] == kara){
					kuri_han(okimasu2);
				}
			}
		}
	}
}

void te(){
	printf("‚Ç‚±‚É’u‚­H:");
	do{
		scanf_s("%d", &okimasu);
	} while (okimasu / 10000 != 0||okimasu/100>tate||okimasu%100>yoko);
	if (masu[okimasu / 100][okimasu % 100][0] == bomb){
		endflag = 1;
	}
	else{
		masu[okimasu / 100][okimasu % 100][1] = masu[okimasu / 100][okimasu % 100][0];
		if (masu[okimasu / 100][okimasu % 100][1] == kara){
			kuri_han(okimasu);
		}
	}
}

void bomb_haiti(){
	int i,p;
	srand((unsigned)time(NULL));
	for (i = 0; i < bakudan; i++){
		p = rand() % (tate*yoko);
		if (masu[p / tate+1][p%yoko+1][0] == bomb){
			i--;
		}
		else{
			masu[p / tate+1][p%yoko+1][0] = bomb;
		}
	}
}

void hyouzi(){
	int i, j;
	for (i = 0; i < tate+2; i++){
		if (i == 0){
			printf("„¬„ª");
			for (j = 1; j < yoko ;j++){
				printf("„ª");
			}
			printf("„­\n");
		}
		else if (i == tate + 1){
			printf("„¯„ª");
			for (j = 1; j < yoko ; j++){
				printf("„ª");
			}
			printf("„®\n");
		}
		else{
			for (j = 0; j < yoko + 2; j++){
				if (j == 0 || (j == yoko + 1)){
					printf("„«");
				}
				else if (masu[i][j][1] == kara){
					printf(" ");
				}
				else if (masu[i][j][1] == bomb){
					printf("* ");
				}
				else if (masu[i][j][1] == hata){
					printf("P ");
				}
				else if (masu[i][j][1] == kara2){
					printf("  ");
				}
				else{
					printf("%d ", masu[i][j][1]);
				}
			}
			puts("");
		}
	}	
}

void hantei(){
	int i, j;
	int k, l;
	int count;
	for (i = 1; i <= tate; i++){
		for (j = 1; j <= yoko; j++){
			count = 0;
			if (masu[i][j][0] != bomb){
				for (k = -1; k <= 1; k++){
					for (l = -1; l <= 1; l++){
						if (!(k == 0 && l == 0)){
							if (masu[i + k][j + l][0] == bomb){
								count++;
							}
						}
					}
				}
				masu[i][j][0] = count;
			}
		}
	}
	masu[okimasu / 100][okimasu % 100][1] = masu[okimasu / 100][okimasu % 100][0];
}

int main(){
	zyunbi();
	te();
	bomb_haiti();
	hantei();
	do{
		hyouzi();
		te();
	} while (endflag != 1);
}