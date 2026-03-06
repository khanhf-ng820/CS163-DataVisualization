#include "HashTable/HashTableSlot.h"





TableSlot::TableSlot() {}

TableSlot::TableSlot(int index)
	: index(index)
{}

TableSlot::TableSlot(int index, int key)
	: index(index), key(key), empty(false)
{}
