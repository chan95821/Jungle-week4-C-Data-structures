///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
void foo(int (*a)[10])
{
	printf("%zu\n", sizeof((*a)[0]));
	printf("%zu\n", sizeof(*a)); // sizeof 용 데이터 타입 - zu는 시스템이 담을 수 있는 변수 최대 크기, unsigned . %d는 signed int
}

void decay_avoidance(int (*a)[10])
{
    printf("%zu\n", sizeof(*a));
	printf(" 원소 개수%zu\n", sizeof *a / sizeof(*a)[0]);
}
int main()
{
	int k[10];
	k[9] = 5;
	printf("%d ", k[9]);
	printf("%d \n", 9[k]);

	decay_avoidance(&k);
	printf("size of int [10]\n : %zu", sizeof (int[10]));
	foo(&k);
}