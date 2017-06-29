#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <ctime>

#include "perlin_noise.h"

#define MAX_GREY 255
#define SEED (time(NULL))

int main() {

	int WIDTH, HEIGHT, iterations;

	printf("Podaj szerokosc: ");
	scanf("%d", &WIDTH);
	printf("\nPodaj wysokosc: ");
	scanf("%d", &HEIGHT); 
	printf("\nPodaj liczbe iteracji: ");
	scanf("%d", &iterations);
	printf("\n");

	printf("Zaczynam generowac\n");
	int *testGREY = (int*)malloc(WIDTH * HEIGHT * sizeof(int));
	getNoise(testGREY, WIDTH, HEIGHT, MAX_GREY, iterations, SEED);
	printf("Wygenerowano GREY\n");

	printf("Zaczynam zapis\n");
	FILE *plik;

	plik = fopen("tmp.pgm", "w");

	fprintf(plik, "P2\n%d %d\n%d\n", WIDTH, HEIGHT, MAX_GREY);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) fprintf(plik, "%d \t", testGREY[i * WIDTH + j]);
	}
	printf("Zapisano\n");

	printf("Zaczynam zwalniac pamiec\n");
	fclose(plik);
	free(testGREY);
	printf("Zwolnilem pamiec\n");

	printf("Koniec\n");

	return 0;
}