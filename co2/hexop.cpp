#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <iomanip>

using namespace std;

int main(void)
{
//	char *hex1;
//	hex1 = new char[5];
	char hex1[5] = {0x68, 0x65, 0x6c, 0x6c, 0x6f};
	char hex2[3] = {0xFF, 0xFA, 0x00};
	printf("%s\n",hex1);
	printf("%X\n",hex1[1]);
	std::cout << std::hex << hex1[1] << std::endl;


	return 0;
}
