#include<stdio.h>
int main()
{

	system("ps  > /root/`fw_printenv machineid`.txt 2>&1");
}
