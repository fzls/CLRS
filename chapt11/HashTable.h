# pragma once
const int RANGE = 80;
enum Status
{
	EMPTY = -1,
	FAILED = -2,
	SUCCESS = -3,
	DELETED = -4,
};

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <list>

using namespace std;

class HashTableWithChaining
{
private:
	vector<list<int>> _table;
	int _capcity;
	int _size;
	int hash(int key);
public:
	HashTableWithChaining(int capcity): _table(capcity), _capcity(capcity) , _size(0) {}
	~HashTableWithChaining() {}
	void Insert(int key);
	int Search(int key);
	int Delete(int key);
	void Print();
};

class HashTableWithOpenAddressing
{
private:
	vector<int> _table;
	int _capcity;
	int _size;
	int hash(int key, int counter);
	int hash1(int key);
	int hash2(int key);
public:
	HashTableWithOpenAddressing(int capcity): _table(capcity, EMPTY), _capcity{capcity}, _size{0} {}
	~HashTableWithOpenAddressing() {}
	void Insert(int key);
	int Search(int key);
	int Delete(int key);
	void Print();
};

/* implementation of HashTableWithChaining */

void HashTableWithChaining::Insert(int key) {
	int hashValue = hash(key);
	bool alreadyIn = false;
	for (auto i = _table[hashValue].begin(); i != _table[hashValue].end(); ++i)
	{
		if (*i == key) {
			alreadyIn = true;
			break;
		}
	}
	if (!alreadyIn)
		_table[hashValue].push_back(key);
}
int HashTableWithChaining::Search(int key) {
	int hashValue = hash(key);
	for (auto i = _table[hashValue].begin(); i != _table[hashValue].end(); ++i)
	{
		if (*i == key)
			return hashValue;
	}
	return FAILED;
}
int HashTableWithChaining::Delete(int key) {
	int hashValue = hash(key);
	for (auto i = _table[hashValue].begin(); i != _table[hashValue].end(); ++i)
	{
		if (*i == key) {
			_table[hashValue].erase(i);
			return SUCCESS;
		}
	}
	return FAILED;
}
int HashTableWithChaining::hash(int key) {
	int hashValue;
	// /* division */
	// hashValue = key % _capcity;
	// /* multiplication */
	// hashValue = (int)(_capcity * (key * 0.618 - (int)(key * 0.618)));
	/* universal hasing */
	hashValue = ((2 * key + 3) % 83) % _capcity;
	return hashValue;
}

void HashTableWithChaining::Print() {
	cout << "--------------------------------------------------------------" << endl;
	cout << "-----start of print HashTable with Chaining-----" << endl;
	int count = 0;
	for (auto List : _table) {
		cout << count++ << " : " ;
		for (auto k : List)
			cout << k << "  ";
		cout << endl;
	}
}

/* HashTableWithOpenAddressing */
void HashTableWithOpenAddressing::Insert(int key) {
	int hashValue = hash(key, 0);
	for (int i = 0; i < _capcity && _table[hashValue] != EMPTY && _table[hashValue] != DELETED;)
		hashValue = hash(key, ++i);
	if (_table[hashValue] == EMPTY || _table[hashValue] == DELETED)
		_table[hashValue] = key;
	else
		cout << "hash table is full, " << key << " can not be inserted" << endl;
}
int HashTableWithOpenAddressing::Search(int key) {
	int hashValue = hash(key, 0);
	for (int i = 0; i < _capcity && _table[hashValue] != EMPTY;)
		if (_table[hashValue] == key)
			return hashValue;
		else
			hashValue = hash(key, ++i);
	return FAILED;
}
int HashTableWithOpenAddressing::Delete(int key) {
	int hashValue = hash(key, 0);
	for (int i = 0; i < _capcity && _table[hashValue] != EMPTY;)
		if (_table[hashValue] == key) {
			_table[hashValue] = DELETED;
			return SUCCESS;
		}
		else
			hashValue = hash(key, ++i);
	return FAILED;
}
int HashTableWithOpenAddressing::hash1(int key) {
	int hashValue;
	/* division */
	hashValue = key % _capcity;
	// /* multiplication */
	// hashValue = (int)(_capcity * (key * 0.618 - (int)(key * 0.618)));
	// /* universal hasing */
	// hashValue = ((2 * key + 3) % 83) % _capcity;
	return hashValue;
}

int HashTableWithOpenAddressing::hash2(int key) {
	int hashValue;
	// /* division */
	// hashValue = key % _capcity;
	/* multiplication */
	// hashValue = (int)(_capcity * (key * 0.618 - (int)(key * 0.618)));
	/* universal hasing */
	hashValue = ((2 * key + 3) % 83) % _capcity;
	return hashValue;
}

int HashTableWithOpenAddressing::hash(int key, int counter) {
	int hashValue;
	/* linear probing */
	hashValue = (hash1(key) + counter) % _capcity;
	// /* quadratic probing */
	// hashValue = (hash1(key) + counter * (counter + 1) / 2) % _capcity;
	// /* double hashing */
	// hashValue = (hash1(key) + counter * hash2(key)) % _capcity;
	return hashValue;
}
void HashTableWithOpenAddressing::Print() {
	cout << "--------------------------------------------------------------" << endl;
	cout << "-----start of print HashTable with OPEN ADRESS-----" << endl;
	int count = 0;
	for (auto k : _table) {
		cout << count++ << " : " ;
		if (k == EMPTY || k == DELETED)
			cout << " ";
		else
			cout << k;
		cout << endl;
	}
	cout << endl;
}
