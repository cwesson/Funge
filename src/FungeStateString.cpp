/**
 * @file FungeStateString.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateString.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {

FungeStateString::FungeStateString(FungeRunner& r, StackStack& s, InstructionPointer& i) :
	FungeState(r, s, i),
	previous('\0')
{
	
}

bool FungeStateString::execute(inst_t i){
	if(i == '\"'){
		runner.setState(runner.getNormalState());
	}else{
		if(funge_config.strings == STRING_MULTISPACE){
			stack.top().push(static_cast<int>(i));
		}else{
			if(i != ' ' || previous != ' '){
				stack.top().push(static_cast<int>(i));
				previous = i;
			}
			if(i == ' '){
				return false;
			}
		}
	}
	return true;
}

}
