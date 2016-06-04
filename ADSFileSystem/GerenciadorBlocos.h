#define INODE_REFERENCES_COUNT 13
// DADOS DO SUPER BLOCO

typedef struct I_NODE{
	int id;					// -> self identifier
	int blockReference[INODE_REFERENCES_COUNT]; // -> pointer to block address
	int nextNode;			// -> pointer to another iNode
	int flag;
} iNode;

typedef struct DIR_NODE{
	int id;
	char filename[21]; 
	char fileExtension[4];
	unsigned char flag;
	char description[21];
	int size;
	int iNodeReference;
	int next;
} DirectoryNode;



