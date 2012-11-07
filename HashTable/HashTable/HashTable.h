typedef int (*HashFunc)(int factor);

extern void initHashTable();
extern bool putIntoHashTable(int value);
extern bool querryHashTable(int value);
extern bool removeFormHashTable(int value);
extern void destroyHashTable();
extern HashFunc setHashFunc(HashFunc fnHashFunc);
extern int modeFunc(int input);
