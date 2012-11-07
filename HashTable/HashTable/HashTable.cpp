#include <stdio.h>
#include <stdlib.h>

#define DEFUALT_HASHTABLE_SIZE 100
#define DEFUALT_MODEFACTOR 100

typedef int (*HashFunc)(int factor);
typedef struct HASH_TABLE_NODE
{
	int value;
	HASH_TABLE_NODE *pNext;
} HashTable;

HashTable *(g_pHashTable[DEFUALT_HASHTABLE_SIZE]) = {NULL}; 
HashFunc g_HashFunc = NULL;            

void destroyLink(HashTable* pHead)
{
	HashTable* pTemp = pHead;
	HashTable* pNext = NULL;
	while(pTemp != NULL)
	{
		pNext = pTemp->pNext;
		free(pTemp);
		pTemp = pNext;
	}
	pHead = NULL;
}

void destroyHashTable()
{
	int i = 0;
	for(i=0; i<DEFUALT_HASHTABLE_SIZE; i++)
	{
		destroyLink(g_pHashTable[i]);
		g_pHashTable[i] = NULL;
	}
}

HASH_TABLE_NODE* createNode(int value)
{
	HASH_TABLE_NODE* pHashNode = (HASH_TABLE_NODE*)malloc(sizeof(HASH_TABLE_NODE));
	pHashNode->value = value;
	pHashNode->pNext = NULL;
	return pHashNode;
}

void initHashTable()
{
	destroyHashTable();
	if(g_HashFunc == NULL)
	{
		printf("warning:please set hash function before using hash table");
	}
}

bool putIntoHashTable(int value)
{
	if(g_HashFunc == NULL)
	{
		printf("error:hash function unset");
		return false;
	}
    int key = g_HashFunc(value);
	HashTable *pHead = g_pHashTable[key];
	if(pHead == NULL)
	{
		pHead = createNode(value);
		g_pHashTable[key] = pHead;
		return true;
	}
	HashTable *pSlotTemp = pHead;
	while(pSlotTemp != NULL)
	{
		if(pSlotTemp->value == value)
		{
			return true;
		}
		if(pSlotTemp->pNext == NULL)
		{
			break;
		}
		pSlotTemp = pSlotTemp->pNext;
	}
	HASH_TABLE_NODE* pHashNode = createNode(value);
	if(pHashNode == NULL)
	{
		printf("create new node failed\n");
		return false;
	}
	pSlotTemp->pNext = pHashNode;
	return true;
}

bool querryHashTable(int value)
{
	int key = g_HashFunc(value);
	HashTable *pSlotTemp = g_pHashTable[key];
	while(pSlotTemp != NULL)
	{
		if(pSlotTemp->value == value)
		{
			return true;
		}
		pSlotTemp = pSlotTemp->pNext;

	}
	return false;
}

bool removeFormHashTable(int value)
{
	int key = g_HashFunc(value);
	HashTable *pSlotHead = g_pHashTable[key];
	HashTable *pSlotTemp = pSlotHead;
	HashTable *pNext = NULL;
	if(pSlotHead == NULL)
	{
		return false;
	}
	//remove head
	if(pSlotHead->value == value)
	{
		pSlotHead = pSlotHead->pNext;
		g_pHashTable[key] = pSlotHead;
		free(pSlotTemp);
		return true;
	}
	//remove nonhead
	pNext = pSlotHead->pNext;
	while(pNext != NULL)
	{
		if(pNext->value == value)
		{
			pSlotTemp->pNext = pNext->pNext;
			free(pNext);
			return true;
		}
		pSlotTemp = pSlotTemp->pNext;
		pNext = pSlotTemp->pNext;
	}
	return false;
}

HashFunc setHashFunc(HashFunc fnHashFunc)
{
	HashFunc fnOldHashFunc = g_HashFunc;
	g_HashFunc = fnHashFunc;
	return fnOldHashFunc;
}

int modeFunc(int input)
{
	return (input%DEFUALT_MODEFACTOR);
}
