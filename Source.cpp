#include <iostream>

#include "GLContext.h"



int main() {
	std::unique_ptr<GLContext> context = std::make_unique<GLContext>();

	context->run();

	return 0;
}