#include "loop.h"
#include <stdio.h>

void loop_execute(void) {
	printf("X:%d x:%d z:%d\n", loop_variable_value('X'), loop_variable_value('x'),loop_variable_value('y'));

	if(loop_variable_value('x')%2==0)
		loop_continue('x');
}
