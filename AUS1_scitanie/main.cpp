#include "structures/heap_monitor.h"
#include "Interface/interface.h"

#include <iostream>

int main()
{
	initHeapMonitor();
	Interface i;
	i.initialize();
	i.displayOptions();
	return 0;
}
