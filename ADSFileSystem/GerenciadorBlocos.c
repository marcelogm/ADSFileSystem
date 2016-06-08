#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Driver.h"
#include "GerenciadorBlocos.h"

typedef unsigned char byte;
//#define DEBUG true

#define DISK_GB_SIZE 16
#define DISK_TOTAL_SIZE (((DISK_GB_SIZE) * 1024) * 1024)
#define FB_COUNT (DISK_TOTAL_SIZE / SB_TAM_BLOCO_FISICO)
#define BITMAP_FB_COUNT (FB_COUNT / SB_TAM_BLOCO_FISICO)
// DIRECTORY
#define DIR_SIZE (sizeof(DirectoryNode))
#define DIR_COUNT (DISK_TOTAL_SIZE / SB_TAM_BLOCO_LOGICO)
#define DIR_PER_FB ((SB_TAM_BLOCO_FISICO) / DIR_SIZE)
#define DIR_FB_COUNT (DIR_COUNT / DIR_PER_FB)
// INODES
#define INODE_SIZE (sizeof(iNode))
#define	INODE_COUNT (DISK_TOTAL_SIZE / SB_TAM_BLOCO_LOGICO)
#define	INODE_PER_FB ((SB_TAM_BLOCO_FISICO) / INODE_SIZE)
#define INODE_FB_COUNT (INODE_COUNT / INODE_PER_FB)
// LOGICAL BLOCK
#define RES_AREA_OFFSET (BITMAP_FB_COUNT + DIR_FB_COUNT + INODE_FB_COUNT)
#define FB_PER_LB (SB_TAM_BLOCO_LOGICO / SB_TAM_BLOCO_FISICO)
#define LB_COUNT ((FB_COUNT - RES_AREA_OFFSET) / FB_PER_LB)

#pragma region LOGICAL_BLOCK
void diskSpec();
void readLB(int idLB, byte* buffer);
void writeLB(int idLB, byte* buffer);
void freeLB(int idLB);
int findEmptyLB();

#define BM_CUR_PG ((RES_AREA_OFFSET + idFB) / SB_TAM_BLOCO_FISICO)
#define BM_CUR_ITEM ((RES_AREA_OFFSET + idFB) % SB_TAM_BLOCO_FISICO)	

void readLB(int idLB, byte* buffer) {
	int idFB = idLB * FB_PER_LB; // GET FB ID
	for (size_t i = 0; i < FB_PER_LB; i++)
		LeiaBlocoFisico(RES_AREA_OFFSET + idFB++, &buffer[SB_TAM_BLOCO_FISICO * i]);
}

void writeLB(int idLB, byte* buffer) {
	byte bitmapPage[SB_TAM_BLOCO_FISICO];
	int idFB = idLB * DIR_PER_FB;
	int curPage = BM_CUR_PG;
	LeiaBlocoFisico(curPage, &bitmapPage);
	for (size_t i = 0; i < FB_PER_LB; i++) {
		bitmapPage[BM_CUR_ITEM] = '1';
		EscrevaBlocoFisico(RES_AREA_OFFSET + idFB++, &buffer[SB_TAM_BLOCO_FISICO * i]);
	}
	EscrevaBlocoFisico(curPage, &bitmapPage);
}

void freeLB(int idLB) {
	byte bitmapPage[SB_TAM_BLOCO_FISICO];
	int idFB = idLB *= DIR_PER_FB;
	int curPage = BM_CUR_PG;
	LeiaBlocoFisico(curPage, &bitmapPage);
	for (size_t i = 0; i < FB_PER_LB; i++) {
		bitmapPage[BM_CUR_ITEM] = '0';
		idFB++;
	}
	EscrevaBlocoFisico(curPage, &bitmapPage);
}

int findEmptyLB() {
	byte bitmapPage[SB_TAM_BLOCO_FISICO];
	LeiaBlocoFisico(0, &bitmapPage);
	int idFB = 0, idLB = 0, bmCurPage = 0, bmCurItem = 0;
	do {
		if (BM_CUR_ITEM != bmCurPage)
			LeiaBlocoFisico(BM_CUR_PG, &bitmapPage);
		bmCurPage = BM_CUR_PG;
		bmCurItem = BM_CUR_ITEM;
		idLB = ((((bmCurPage * SB_TAM_BLOCO_FISICO) + bmCurItem) - RES_AREA_OFFSET) / FB_PER_LB);
		idFB++;
	} while (bitmapPage[bmCurItem] != '0');
	return idLB;
}

#undef BM_CUR_PG
#undef BM_CUR_ITEM
#pragma endregion

#pragma region FORMAT
void diskSpec();
void bitmapCreate();
void dirTreeCreate();
void iNodesCreate();
void bitmapSetReservedArea();
void formatDisk();

void diskSpec() {
	printf("\
			Total em GB: %d\n\
			Total em KB: %d\n\
			Quantidade de blocos: %d\n\
			Blocos de bitmap: %d\n\
			Tamanho do DirNode: %d\n\
			Quantidade de DirNode: %d\n\
			DirNode por bloco fisico: %d\n\
			Blocos Fisicos com DirNode: %d\n\
			Tamanho do iNode: %d\n\
			Quantidade de iNodes: %d\n\
			iNodes por bloco: %d\n\
			Blocos com iNodes: %d\n\
			Primeiro bloco para dados: %d",
		DISK_GB_SIZE, DISK_TOTAL_SIZE, FB_COUNT,
		BITMAP_FB_COUNT, DIR_SIZE, DIR_COUNT,
		DIR_PER_FB, DIR_FB_COUNT, INODE_SIZE,
		INODE_COUNT, INODE_PER_FB, INODE_FB_COUNT,
		RES_AREA_OFFSET);
}

void bitmapCreate() {
	byte bitmapPage[SB_TAM_BLOCO_FISICO];
	memset(&bitmapPage, '0', SB_TAM_BLOCO_FISICO * sizeof(byte));
	for (size_t i = 0; i < BITMAP_FB_COUNT; i++)
		EscrevaBlocoFisico(i, &bitmapPage);
}

void dirTreeCreate() {
	DirectoryNode dirPage[DIR_FB_COUNT];
	memset(&dirPage, 0, SB_TAM_BLOCO_FISICO);
	for (size_t i = 0; i < DIR_FB_COUNT; i++) {
		for (size_t j = 0; j < DIR_PER_FB; j++) {
			dirPage[j].id = j + (i * DIR_PER_FB);
			dirPage[j].size = -1;
			dirPage[j].iNodeReference = -1;
			dirPage[j].next = 0;
		}
		EscrevaBlocoFisico(BITMAP_FB_COUNT + i, &dirPage); // BITMAP_FB_COUNT => OFFSET
	}
	LeiaBlocoFisico(BITMAP_FB_COUNT, &dirPage);
	strcpy(dirPage[0].filename, "/");
	strcpy(dirPage[0].description, "Root directory");
	EscrevaBlocoFisico(BITMAP_FB_COUNT, &dirPage);
}

void iNodesCreate() {
	iNode iNodePage[INODE_PER_FB];
	memset(&iNodePage, 0, SB_TAM_BLOCO_FISICO);
	for (size_t i = 0; i < INODE_FB_COUNT; i++) {
		for (size_t j = 0; j < INODE_PER_FB; j++)
			iNodePage[j].id = j + (i * INODE_PER_FB);
		EscrevaBlocoFisico(BITMAP_FB_COUNT + DIR_FB_COUNT + i, &iNodePage);
	}
}

void bitmapSetReservedArea() {
	byte bitmapPage[SB_TAM_BLOCO_FISICO];
	memset(&bitmapPage, '1', SB_TAM_BLOCO_FISICO * sizeof(byte));
	for (size_t i = 0; i < (RES_AREA_OFFSET / SB_TAM_BLOCO_FISICO); i++)
		EscrevaBlocoFisico(i, &bitmapPage);
	memset(&bitmapPage, '0', SB_TAM_BLOCO_FISICO * sizeof(byte));
	memset(&bitmapPage, '1', (RES_AREA_OFFSET % SB_TAM_BLOCO_FISICO));
	EscrevaBlocoFisico((RES_AREA_OFFSET / SB_TAM_BLOCO_FISICO), &bitmapPage);
}

void formatDisk() {
#ifdef DEBUG
	diskSpec();
#endif // DEBUG
	bitmapCreate();
	dirTreeCreate();
	iNodesCreate();
	bitmapSetReservedArea();
	// Primeiro bloco logico nao pode ser referenciado
	writeLB(0, "\0");
	// Primeiro inode nao vai ser referenciado
	iNode iNodePage[INODE_PER_FB];
	LeiaBlocoFisico(BITMAP_FB_COUNT + DIR_FB_COUNT, &iNodePage);
	iNodePage[0].flag = '1';
	EscrevaBlocoFisico(BITMAP_FB_COUNT + DIR_FB_COUNT, &iNodePage);
}
#pragma endregion

#pragma region DIRECTORY
void listAllDirNodes();
int findEmptyDirNode();
void dirNodeSetValues(DirectoryNode * dirNode, char * name, char * ext, char * descr, char * flag, int nextNode, int size);
int findDir(char * name);
int writeDir(char * name, char * ext, char * descr, char * flag, int size);

#define CUR_PAGE(x) (x / DIR_PER_FB)
#define CUR_ITEM(x) (x % DIR_PER_FB)
#define CURRENT (dirPage[CUR_ITEM(curItem)])
#define OFFSET (BITMAP_FB_COUNT)
void listAllDirNodes() {
	DirectoryNode dirPage[DIR_PER_FB];
	int curItem = 0, nextItem;
	LeiaBlocoFisico(OFFSET, &dirPage); // BITMAP_FB_COUT => OFFSET
	while (true) { // HORRIVEL, EU SEI
		printf("Filename: %s\n", CURRENT.filename);
		printf("FileExtention: %s\n", CURRENT.fileExtension);
		printf("Description: %s\n", CURRENT.description);
		printf("Flag: %c\n", CURRENT.flag);
		printf("Size: %d\n", CURRENT.size);
		printf("iNodeReference: %d\n", CURRENT.iNodeReference);
		printf("NextFCP: %d\n", CURRENT.next);
		printf("====================\n");
		if (dirPage[CUR_ITEM(curItem)].next == 0) return;
		nextItem = dirPage[CUR_ITEM(curItem)].next;
		if (CUR_PAGE(nextItem) != (CUR_PAGE(curItem)))
			LeiaBlocoFisico(OFFSET + CUR_PAGE(nextItem), &dirPage);
		curItem = nextItem;
	}
}

int findEmptyDirNode() {
	int curDirId = 0, counter = 0, curPage = 0, curItem = 0;
	DirectoryNode dirPage[DIR_PER_FB];
	LeiaBlocoFisico(OFFSET, &dirPage); // BITMAP_FB_COUNT => OFFSET
	do {
		if (curPage != CUR_PAGE(counter))
			LeiaBlocoFisico(OFFSET + CUR_PAGE(counter), &dirPage);
		curPage = CUR_PAGE(counter);
		curItem = CUR_ITEM(counter);
		curDirId = dirPage[curItem].id;
		counter++;
	} while (strcmp(dirPage[curItem].filename, ""));
	return curDirId;
}

void dirNodeSetValues(DirectoryNode * dirNode, char * name, char * ext, char * descr, char * flag, int nextNode, int size) {
	strcpy(dirNode->filename, name);
	strcpy(dirNode->fileExtension, ext);
	strcpy(dirNode->description, descr);
	dirNode->flag = flag;
	dirNode->next = nextNode;
	dirNode->size = size;
}

int findPrevDir(int dirId) {
	DirectoryNode dirPage[DIR_PER_FB];
	LeiaBlocoFisico(OFFSET + CUR_PAGE(dirId), &dirPage);
	while (!strcmp(dirPage[CUR_ITEM(--dirId)].filename, "")) {
		if ((CUR_PAGE(dirId)) != (CUR_PAGE(dirId - 1)))
			LeiaBlocoFisico(OFFSET + CUR_PAGE(dirId), &dirPage);
	}
	return dirId;
}

int findDir(char * name) {
	DirectoryNode dirPage[DIR_PER_FB];
	int curItem = 0, nextItem;
	LeiaBlocoFisico(OFFSET, &dirPage);
	while (strcmp(CURRENT.filename, name)) {
		if (dirPage[CUR_ITEM(curItem)].next == 0) return -1;
		nextItem = dirPage[CUR_ITEM(curItem)].next;
		if (CUR_PAGE(nextItem) != (CUR_PAGE(curItem)))
			LeiaBlocoFisico(OFFSET + CUR_PAGE(nextItem), &dirPage);
		curItem = nextItem;
	}
	return curItem;
}

#define PREV_PAGE(x) ((x - 1) / DIR_PER_FB)
#define PREV_ITEM(x) ((x - 1) % DIR_PER_FB)
int writeDir(char * name, char * ext, char * descr, char * flag, int size) {
	DirectoryNode dirPage[DIR_PER_FB];
	int exists = findDir(name);
	if (exists >= 0) {
		LeiaBlocoFisico(OFFSET + CUR_PAGE(exists), &dirPage);
		dirNodeSetValues(&dirPage[CUR_ITEM(exists)], name, ext, descr, flag, dirPage[CUR_ITEM(exists)].next, size);
		EscrevaBlocoFisico(OFFSET + CUR_PAGE(exists), &dirPage);
		return exists;
	} else {
		int emptyDirId = findEmptyDirNode();
		LeiaBlocoFisico(PREV_PAGE(emptyDirId) + OFFSET, &dirPage);
		int nextPointedNode = dirPage[PREV_ITEM(emptyDirId)].next;
		dirPage[PREV_ITEM(emptyDirId)].next = emptyDirId;
		if (CUR_PAGE(emptyDirId) != PREV_PAGE(emptyDirId)) {
			EscrevaBlocoFisico(PREV_PAGE(emptyDirId) + OFFSET, &dirPage);
			LeiaBlocoFisico(CUR_PAGE(emptyDirId) + OFFSET, &dirPage);
		}
		dirNodeSetValues(&dirPage[CUR_ITEM(emptyDirId)], name, ext, descr, flag, nextPointedNode, size);
		EscrevaBlocoFisico(CUR_PAGE(emptyDirId) + OFFSET, &dirPage);
		return emptyDirId;
	}
}

#undef OFFSET
#undef NEXT
#undef CURRENT
#undef CUR_PAGE(x)
#undef CUR_ITEM(x)
#undef PREV_PAGE(x) 
#undef PREV_ITEM(x)
#pragma endregion

#pragma region INODES
#define CUR_PAGE(x) (x / INODE_PER_FB)
#define CUR_ITEM(x) (x % INODE_PER_FB)
#define OFFSET (BITMAP_FB_COUNT + DIR_FB_COUNT)
void listAllINodes();
int findEmptyINode();
void freeINodeRef(int iNodeId);
int writeSequence(int iNodeRef, int size, byte * content);

void listAllINodes() {
	iNode iNodePage[INODE_PER_FB];
	for (size_t i = 0; i < 3; i++) {
		LeiaBlocoFisico(BITMAP_FB_COUNT + DIR_FB_COUNT + i, &iNodePage);
		for (size_t j = 0; j < INODE_PER_FB; j++) {
			printf("\nINode Id: %d Ref:", iNodePage[j].id);
			for (size_t z = 0; z < INODE_REFERENCES_COUNT; z++)
			{
				printf(" %d. %d ", z, iNodePage[j].blockReference[z]);
			}
		}
	}
}

int findEmptyINode() {
	int curInodeId = 0, counter = 0, curPage = 0, curItem = 0;
	iNode iNodePage[INODE_PER_FB];
	memset(&iNodePage, 0, SB_TAM_BLOCO_FISICO);
	LeiaBlocoFisico(OFFSET, &iNodePage);
	while (iNodePage[curItem].flag == '1') {
		counter++;
		if (curPage != CUR_PAGE(counter))
			LeiaBlocoFisico(OFFSET + CUR_PAGE(counter), &iNodePage);
		curPage = CUR_PAGE(counter);
		curItem = CUR_ITEM(counter);
		curInodeId = iNodePage[curItem].id;
	} 
	return curInodeId;
}

void freeINodeRef(int iNodeId) {
	iNode iNodePage[INODE_PER_FB];
	int curPage = CUR_PAGE(iNodeId), curItem = CUR_ITEM(iNodeId);
	LeiaBlocoFisico(OFFSET + CUR_PAGE(iNodeId), &iNodePage);
	while (iNodePage[iNodeId].id != 0) {
		int i = 0;
		if (curPage != CUR_PAGE(iNodeId)) {
			EscrevaBlocoFisico(OFFSET + curPage, &iNodePage);
			LeiaBlocoFisico(OFFSET + CUR_PAGE(iNodeId), &iNodePage);
		}
		curPage = CUR_PAGE(iNodeId);
		curItem = CUR_ITEM(iNodeId);
		iNodeId = iNodePage[CUR_ITEM(iNodeId)].nextNode;
		iNodePage[curItem].flag = 0;
		while (iNodePage[curItem].blockReference[i] != 0) {
			freeLB(iNodePage[curItem].blockReference[i]);
			iNodePage[curItem].blockReference[i] = 0;
			i++;
		}
	}
	EscrevaBlocoFisico(OFFSET + curPage, &iNodePage);
}

int writeSequence(int iNodeRef, int size, byte * content) {
	int lBNeeded = size / SB_TAM_BLOCO_LOGICO, curLB, i = 0;
	iNode iNodePage[INODE_PER_FB];
	bool ftExecution = true;
	if ((size % SB_TAM_BLOCO_LOGICO) > 0) lBNeeded++;
	LeiaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
	while (lBNeeded > i) {
		curLB = findEmptyLB();
		writeLB(curLB, &content[i * SB_TAM_BLOCO_LOGICO]);
		if (((i % INODE_REFERENCES_COUNT) == 0) && (ftExecution == false)) {
			EscrevaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
			int nextINodeRef = findEmptyINode();
			iNodePage[CUR_ITEM(iNodeRef)].nextNode = nextINodeRef;
			EscrevaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
			iNodeRef = nextINodeRef;
			LeiaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
		}
		iNodePage[CUR_ITEM(iNodeRef)].flag = '1';
		iNodePage[CUR_ITEM(iNodeRef)].blockReference[i % INODE_REFERENCES_COUNT] = curLB;
		i++;
		ftExecution = false;
	}
	EscrevaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
}

void readSequence(int iNodeRef, byte * content, int size) {
	int i = size / SB_TAM_BLOCO_LOGICO, curLB, counter = 0;
	iNode iNodePage[INODE_PER_FB];
	bool ftExecution = true;
	if ((size % SB_TAM_BLOCO_LOGICO) > 0) i++;
	LeiaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
	byte * localBuffer = malloc(sizeof(byte) * i * SB_TAM_BLOCO_LOGICO);
	while (counter < i) {
		if (iNodePage[CUR_ITEM(iNodeRef)].blockReference[counter % INODE_REFERENCES_COUNT] == 0) return;
		if (((counter % INODE_REFERENCES_COUNT) == 0) && (ftExecution == false)) {
			iNodeRef = iNodePage[CUR_ITEM(iNodeRef)].nextNode;
			LeiaBlocoFisico(OFFSET + CUR_PAGE(iNodeRef), &iNodePage);
		}
		curLB = iNodePage[CUR_ITEM(iNodeRef)].blockReference[counter % INODE_REFERENCES_COUNT];
		readLB(curLB, &localBuffer[counter * SB_TAM_BLOCO_LOGICO]);
		counter++;
		ftExecution = false;
	}
	memcpy(content, localBuffer, size);
	free(localBuffer);
}

#undef CUR_PAGE(x)
#undef CUR_ITEM(x)
#undef OFFSET
#pragma endregion

void writeFile(char * name, char * ext, char * flag, char * descr, int size, byte * content) {
	DirectoryNode dirPage[DIR_PER_FB];
	int dirWritedId = writeDir(name, ext, descr, flag, size);
	int curDirItem = dirWritedId % DIR_PER_FB;
	int curDirPage = dirWritedId / DIR_PER_FB;
	LeiaBlocoFisico(BITMAP_FB_COUNT + curDirPage, &dirPage);
	if (dirPage[curDirItem].iNodeReference == -1) {
		iNode iNodePage[INODE_PER_FB];
		int ftInodeId = findEmptyINode();
		int curInodeItem = ftInodeId % INODE_PER_FB;
		int curInodePage = ftInodeId / INODE_PER_FB;
		LeiaBlocoFisico(BITMAP_FB_COUNT + DIR_FB_COUNT + curInodePage, &iNodePage);
		dirPage[curDirItem].iNodeReference = iNodePage[curInodeItem].id;
		writeSequence(ftInodeId, size, content);
	} else {
		freeINodeRef(dirPage[curDirItem].iNodeReference);
		writeSequence(dirPage[curDirItem].iNodeReference, size, content);
	}
	EscrevaBlocoFisico(BITMAP_FB_COUNT + curDirPage, &dirPage);
}

bool deleteFile(char * name) {
	int dirId = findDir(name);
	if (dirId > 0) {
		int curDirItem = dirId % DIR_PER_FB;
		int curDirPage = dirId / DIR_PER_FB;
		DirectoryNode dirPage[DIR_PER_FB];
		LeiaBlocoFisico(BITMAP_FB_COUNT + curDirPage, &dirPage);
		int next = dirPage[curDirItem].next;
		int iNodeRef = dirPage[curDirItem].iNodeReference;
		freeINodeRef(iNodeRef);
		memset(&dirPage[curDirItem].filename, 0, sizeof(dirPage[curDirItem].filename));
		memset(&dirPage[curDirItem].fileExtension, 0, sizeof(dirPage[curDirItem].fileExtension));
		memset(&dirPage[curDirItem].description, 0, sizeof(dirPage[curDirItem].description));
		dirPage[curDirItem].flag = 0;
		dirPage[curDirItem].size = -1;
		dirPage[curDirItem].next = 0;
		dirPage[curDirItem].iNodeReference = -1;
		int prevDirId = findPrevDir(dirId);
		int prevDirItem = prevDirId % DIR_PER_FB;
		int prevDirPage = prevDirId / DIR_PER_FB;
		if (curDirPage != prevDirPage) {
			EscrevaBlocoFisico(BITMAP_FB_COUNT + curDirPage, &dirPage);
			LeiaBlocoFisico(BITMAP_FB_COUNT + prevDirPage, &dirPage);
		}
		dirPage[prevDirItem].next = next;
		EscrevaBlocoFisico(BITMAP_FB_COUNT + prevDirPage, &dirPage);
		return true;
	}
	return false;
}

void readFile(char * name, byte * dados) {
	int dirId = findDir(name);
	if (dirId > 0) {
		int curDirItem = dirId % DIR_PER_FB;
		int curDirPage = dirId / DIR_PER_FB;
		DirectoryNode dirPage[DIR_PER_FB];
		LeiaBlocoFisico(BITMAP_FB_COUNT + curDirPage, &dirPage);
		readSequence(dirPage[curDirItem].iNodeReference, dados, dirPage[curDirItem].size);
	}
	return false;
}

bool existsFile(char * name) {
	return findDir(name);
}
/*
int main() {
	formatDisk();
	byte a[100000];
	memset(&a, 'x', sizeof(a));
	writeFile("Marcelo", "exe", 'r', "Um arquivo", sizeof(a), &a);
	memset(&a, 'y', sizeof(a));
	writeFile("Pedro", "exe", 'r', "Um arquivo", sizeof(a), &a);
	readFile("Marcelo", &a);
	deleteFile("Marcelo");
	char b[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	writeFile("Lorem", "exe", 'r', "Um arquivo", sizeof(b), &b);

	system("cls");listAllDirNodes();
	listAllINodes();
	return 1;
}*/