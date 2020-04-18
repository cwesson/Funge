/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @Conlan Wesson
 */

#include "FungeConfig.h"

namespace Funge {

struct FungeConfig funge_config = {
	.dimensions = 0,
	.standard = 98,
	.concurrent = true,
	.filesystem = true,
};

}