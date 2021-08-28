/**
 * @file Trefunge98Strategy.cpp
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Trefunge98Strategy.h"

namespace Funge {


Trefunge98Strategy::Trefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s, FungeRunner& r) :
	FungeStrategy(f, i, s, r, {'h', 'l', 'm'})
{
	
}

bool Trefunge98Strategy::execute(inst_t cmd){
	switch(cmd){
		case 'h':
			ip.setDelta(Vector{0, 0, 1}); break;
		case 'l':
			ip.setDelta(Vector{0, 0, -1}); break;
		case 'm':
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, -1});
			}
			break;
		
		default:
			return false;
	}
	return true;
}

}
