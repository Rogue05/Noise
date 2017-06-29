#include "perlin_noise.h"

void getNoise(int *image, int width, int height, int max_color, int iterations, int seed) {
	int i, j, k;
	srand(seed);
	float wsp;

	int size = width * height;
	int tmp_width = width, tmp_height = height;

	int *tmp = (int*)malloc(size * sizeof(int));
	int *tmp_rozmycie = (int*)malloc(size * sizeof(int));

	/* zeruje */
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			image[i*width + j] = 0;
		}
	}

	/* zapelniam tmp */
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			tmp[i*width + j] = rand() % max_color;
			//image[i*width + j] += tmp[i*width + j];
		}
	}

	/* przygotowanie wsp */
	wsp = 1;
	for (i = 0; i < iterations; i++) wsp /= 2;

	/* hokus pokus */
	for (k=1; k <= iterations; k++) {

		/* rozmycie */
		tmp[0] = (tmp[1] + tmp[0] + tmp[width] + tmp[width + 1]) / 4;

		/* rozmycie gory */
		for (j = 1; j < width; j++) tmp[j] = (tmp[j - 1] + tmp[j] + tmp[j + 1] +
			tmp[width + j - 1] + tmp[width + j] + tmp[width + j + 1]) / 6;

		/* rozmycie lewe */
		for (i = 1; i < height - 1; i++) tmp[i*width] = (tmp[(i - 1)*width] + tmp[i*width] + tmp[(i + 1)*width] +
			tmp[(i - 1)*width + 1] + tmp[i*width + 1] + tmp[(i + 1)*width + 1]) / 6;

		/* rozmycie srodka */
		for (i = 1; i < height - 1; i++) {
			for (j = 1; j < width - 1; j++) {
				tmp_rozmycie[i*width + j] = (tmp[(i - 1)*width + j - 1] + tmp[(i - 1)*width + j] + tmp[(i - 1)*width + j + 1] +
					tmp[(i)*width + j - 1] + tmp[(i)*width + j] + tmp[(i)*width + j + 1] +
					tmp[(i + 1)*width + j - 1] + tmp[(i + 1)*width + j] + tmp[(i + 1)*width + j + 1]) / 9;
			}
		}
		
		/* przepisanie rozmycia */
		for (i = 1; i < height - 1; i++) {
			for (j = 1; j < width - 1; j++) {
				tmp[i*width + j] = tmp_rozmycie[i*width + j];
			}
		}
		/* koniec rozmycia */

		/* histogram */
		int cmin = 1000000, cmax = 0;
		for (i = 1; i < height - 1; i++) {
			for (j = 1; j < width - 1; j++) {
				if (tmp[i*width + j] > cmax) cmax = tmp[i*width + j];
				if (tmp[i*width + j] < cmin) cmin = tmp[i*width + j];
			}
		}

		for (i = 0; i < height - 0; i++) {
			for (j = 0; j < width - 0; j++) {
				tmp[i*width + j] = (float)(tmp[i*width + j] - cmin) / (cmax - cmin) * max_color;
			}
		}
		/* koniec hist */

		/* przepisanie */
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				image[i*width + j] += (tmp[i*width + j] * wsp);
			}
		}
		/* koniec przepisania */

		/* aktualizacja tmp */
		for (i = height - 1; i >= 0; i--) {
			for (j = width - 1; j >= 0; j--) {
				tmp[i*width + j] = tmp[i / k*width + j / k];
			}
		}
		/* koniec alktualizacji tmp */

		printf("%f\n", wsp);
		wsp *= 2;
	}

	/* histogram */
	int cmin = 1000000, cmax = 0;
	for (i = 1; i < height - 1; i++) {
		for (j = 1; j < width - 1; j++) {
			if (image[i*width + j] > cmax) cmax = image[i*width + j];
			if (image[i*width + j] < cmin) cmin = image[i*width + j];
		}
	}

	for (i = 0; i < height - 0; i++) {
		for (j = 0; j < width - 0; j++) {
			image[i*width + j] = (float)(image[i*width + j] - cmin) / (cmax - cmin) * max_color;
		}
	}
	/* koniec hist */

	free(tmp);
	free(tmp_rozmycie);
}