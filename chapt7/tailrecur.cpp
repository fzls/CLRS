/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 tailrecur.cpp
* @version:
* @Time: 		 2015-11-10 16:16:59
* @Description:
*
+----------------------------------------------------------
*/
#include <stdio.h>
#include <iostream>

int partition(int[], int, int);

static int stack_depth = 0;
static int max_stack_depth = 0;

void reset_stack_depth_counter();
void increment_stack_depth();
void decrement_stack_depth();

void tail_recursive_quicksort(int A[], int p, int r) {
	increment_stack_depth();

	while (p < r - 1) {
		int q = partition(A, p, r);

		if (q < (p + r) / 2) {
			tail_recursive_quicksort(A, p, q);
			p = q;
		} else {
			tail_recursive_quicksort(A, q + 1, r);
			r = q;
		}
	}

	decrement_stack_depth();
}

int partition(int A[], int p, int r) {
	int x, i, j, tmp;

	x = A[r - 1];
	i = p;

	for (j = p; j < r - 1; j++) {
		if (A[j] <= x) {
			tmp = A[i]; A[i] = A[j]; A[j] = tmp;
			i++;
		}
	}

	tmp = A[i]; A[i] = A[r - 1]; A[r - 1] = tmp;

	return i;
}

void increment_stack_depth() {
	stack_depth++;
	if (max_stack_depth < stack_depth) {
		max_stack_depth = stack_depth;
	}
}

void decrement_stack_depth() {
	stack_depth--;
}

void reset_stack_depth_counter() {
	max_stack_depth = 0;
	stack_depth = 0;
}

int main(int argc, char const *argv[])
{
	reset_stack_depth_counter();
	int data[15] = { 66	,
	                 88 , 15	,
	                 87	, 96	, 26,	51	,
	                 26,	98,	13,	59,	45,	63,	91,	2,
	               } ;

	tail_recursive_quicksort(data, 0, 14);
	std::cout << max_stack_depth << std::endl;
	system("pause");

	return 0;
}
