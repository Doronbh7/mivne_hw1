#ifndef DS_EX1_HELPER_FUNCS
#define DS_EX1_HELPER_FUNCS

#include <memory>
#include "Player.h"

/**
 * merge two sorted arrays to a new sorted array
 * @param array_a
 * @param array_a_size array_a size
 * @param array_b
 * @param array_b_size array_b size
 * @param array_c The new merged sorted array
 */
void mergePlayerArrays(Player** array_a, int array_a_size, Player** array_b, int array_b_size, 
	Player** array_c) {

	int i = 0;
	int j = 0;
	int k = 0;

	while (i < array_a_size && j < array_b_size) {
		Key tmp_key_a(array_a[i]->getPlayerID(), array_a[i]->getLevel());
		Key tmp_key_b(array_b[j]->getPlayerID(), array_b[j]->getLevel());
		if (tmp_key_a < tmp_key_b) {
			array_c[k++] = array_a[i++];
		}
		else {
			array_c[k++] = array_b[j++];
		}
	}
	while (i < array_a_size) {
		array_c[k++] = array_a[i++];
	}
	while (j < array_b_size) {
		array_c[k++] = array_b[j++];
	}
}

#endif
