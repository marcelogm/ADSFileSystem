#include <stdio.h>
#include <stdlib.h>
//#include "GerenciadorBlocos.h"
#include "adsio.h"

// NENHUMA FUNÇÃO DE DRIVER PODE SER CHAMADA DIRETAMENTE

ADS_FILE* ADS_open(const char * filename){
	ADS_FILE* f = malloc(sizeof(ADS_FILE));
	return f;
}

size_t ADS_write(const void * ptr, size_t size, size_t count, ADS_FILE * stream){
	return 0;
}

size_t ADS_read(void * ptr, size_t size, size_t count, ADS_FILE * stream){
	return 0;
}

int ADS_close(ADS_FILE * stream){
	return 0;
}
