#include "loop.h"
#include <stdio.h>

void loop_execute(void) {
	printf("x:%d y:%d z:%d\n", loop_variable_value('x'), loop_variable_value('y'),loop_variable_value('z'));
}
