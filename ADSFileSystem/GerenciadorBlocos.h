#define INODE_REFERENCES_COUNT 13

// SIZE 64
typedef struct I_NODE{
	// ID DO INODE
	int id;			
	// REFENCIAS PARA BLOCOS LOGICOS
	int blockReference[INODE_REFERENCES_COUNT];
	// REFERENCIA PARA O PROXIMO INODE
	int nextNode;
	// FLAG GENERICA (LIBERADO OU NAO)
	int flag;
} iNode;

// SIZE 64
typedef struct DIR_NODE{
	// ID DO DIRETORIO
	int id;
	// NOME DO ARQUIVO
	char filename[21];
	// EXTENSAO
	char fileExtension[4];
	// FLAG GENERICA
	unsigned char flag;
	// DESCRICAO
	char description[21];
	// TAMANHO (MELHOR IMPLENTACAO COM unsigned long)
	int size;
	// REFERENCIA PARA INODE
	int iNodeReference;
	// REFERENCIA PARA O PROXIMO DIRETORIO
	int next;
} DirectoryNode;

typedef struct FILE_INFO {
	char name[21];
	char desc[21];
	char ext[4];
	int size;
} FileInfo;

#include <stdio.h>

// Declaracao de funcoes
// Exportadas para DLL
__declspec(dllexport) void writeFile(char * name, char * ext, char * flag, char * descr, int size, byte * content);
__declspec(dllexport) bool deleteFile(char * name);
__declspec(dllexport) bool readFile(char * name, byte * dados);
__declspec(dllexport) bool existsFile(char * name);
__declspec(dllexport) void formatDisk();
__declspec(dllexport) FileInfo * getFileInfo(char * name);