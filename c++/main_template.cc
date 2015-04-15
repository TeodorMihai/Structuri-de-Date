#include <stdio.h>
#include "KeyStorage.h"

int main(int argc, char const *argv[]) {
	/* code */
	KeyStorage<float> keyElement(6, 345634.43);
	KeyStorage<int> number(7);



	number.setMember(124);
	printf("%f \n", keyElement.getMember() );
	printf("number.member= %d \n", number.getMember());

	number.getMember() = 999;
	printf("number.member= %d \n", kenumber.getMember() );
	return 0;
}