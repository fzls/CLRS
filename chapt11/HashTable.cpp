/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 HashTable.cpp
* @version:
* @Time: 		 2015-11-19 20:22:46~2015-11-19 22:59:02
* @Description:  implement the hashtable (including hash function, collision strategy)
* Hash Function:
	division
	multiplication
	universal hashing
collision strategy:
	chaining
	open addressing
		linear probing
		Quadratic probing
		double hashing
*
*
+----------------------------------------------------------
*/
#include "HashTable.h"

int main() {

	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	int capcity = 41;
	int times = 2 * capcity;
	HashTableWithChaining tableChaining(capcity);
	HashTableWithOpenAddressing tableOpenAddressing(capcity);
	clock_t _time = clock();
	default_random_engine _e(_time);
	int element;

	/* test INSERT */
	for (int i = 0; i < times; ++i) {
		element = _e() % RANGE;
		tableChaining.Insert(element);
		tableOpenAddressing.Insert(element);
	}
	tableChaining.Print();
	tableOpenAddressing.Print();

	/* test SEARCH */
	for (int i = 0; i < times; ++i) {
		element = _e() % RANGE;
		int result1 = tableChaining.Search(element);
		int result2 = tableOpenAddressing.Search(element);
		if (result1 != FAILED)
			cout << "DID find " << element << " in " << result1 << " in the tableChaining" << endl;
		else
			cout << "NOT find " << element  << " in the tableChaining" << endl;
		if (result2 != FAILED)
			cout << "DID find " << element << " in " << result2	<< " in the tableOpenAddressing" << endl;
		else
			cout << "NOT find " << element  << " in the tableOpenAddressing" << endl;
	}

	/* test DELETE */
	for (int i = 0; i < times; ++i) {
		element = _e() % RANGE;
		tableChaining.Delete(element);
		tableOpenAddressing.Delete(element);
	}
	tableChaining.Print();
	tableOpenAddressing.Print();


	cout << endl;
	system("pause");
	return 0;
}
