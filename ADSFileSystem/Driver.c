#include "Driver.h"

int LeiaBlocoFisico(int id, byte * buffer) {
	FILE *arq ;
	char textId[33];
	_itoa(id, textId, 10);
	arq = fopen(strcat(textId, ".txt"), "rb");
	if (!arq) return 0;
	size_t result = fread (buffer,1,SB_TAM_BLOCO_FISICO,arq);
	if (result != SB_TAM_BLOCO_FISICO)
		return -1;
	fclose (arq);
	return 1;
}

int EscrevaBlocoFisico(int id, byte * buffer) {
	FILE * pFile;
	char textId[33];
	_itoa(id, textId, 10);
	pFile = fopen(strcat(textId, ".txt"), "wb+");
	fwrite(buffer, 1, SB_TAM_BLOCO_FISICO, pFile);
	fclose(pFile);
	return	1;
}
