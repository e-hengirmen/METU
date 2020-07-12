#include "loop.h"
#include <stdio.h>

void loop_execute(void) {
	printf("x:%d y:%d\n", loop_variable_value('x'),loop_variable_value('y'));
}
