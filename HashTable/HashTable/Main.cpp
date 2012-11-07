#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Main.h"

void add(int value)
{
	printf("add %d into hash table\n", value);
	putIntoHashTable(value);
}

void remove(int value)
{
	printf("remove %d from hash table\n", value);
	(void)removeFormHashTable(value);
}

void querry(int value)
{
	if(querryHashTable(value))
	{
		printf("%d exist\n",value);
	}
	else
	{
		printf("%d not exist\n",value);
	}
}

int main()
{
	(void)setHashFunc(modeFunc);
	initHashTable();

	test1();
	test2();
	test3();
	
	destroyHashTable();
	system("pause");
}

void test1()
{
	add(0);
	querry(0);
	remove(0);
	querry(0);
}

void test2()
{
	add(0);
	querry(0);
	remove(0);
	querry(0);

	add(100);
	querry(100);
	remove(100);
	querry(0);
}

void test3()
{
	for(int i=0;i<100;i++)
	{
		add(i);
		querry(i);
	}
	add(122);
	remove(22);
	querry(22);
	querry(122);
}
