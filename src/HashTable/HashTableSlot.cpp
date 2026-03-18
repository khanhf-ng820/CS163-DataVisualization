#include "HashTable/HashTableSlot.h"





TableSlot::TableSlot() {}

TableSlot::TableSlot(int index)
	: index(index)
{}

TableSlot::TableSlot(int index, int key)
	: index(index), key(key), empty(false)
{}

TableSlot::TableSlot(int index, TableSlotInput input)
	: index(index), key(input.key), empty(input.empty)
{}



bool TableSlot::hasKey(int keyVal) {
	return key == keyVal && !empty && !deleted;
}
