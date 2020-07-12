#include "loop.h"
#include <stdio.h>

void loop_execute(void) {
	printf("x:%d\n", loop_variable_value('x'));
}
