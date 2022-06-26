/**
 * @file FingerprintMODU.cpp
 * Modulo Arithmetic Extension.
 * @author Conlan Wesson
 */

#include "FingerprintMODU.h"
#include <cmath>

namespace Funge {

FingerprintMODU::FingerprintMODU(FungeRunner& r) :
	Fingerprint(r, {'M', 'R', 'U'})
{}

FungeError FingerprintMODU::execute(inst_t cmd){
	switch(cmd){
		case 'M':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			if(a == 0){
				stack.top().push(0);
			}else{
				stack.top().push(b - std::floor(static_cast<double>(b) / static_cast<double>(a)) * a);
			}
		} break;
		case 'U':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			if(a == 0){
				stack.top().push(0);
			}else{
				stack.top().push(std::abs(b)%std::abs(a));
			}
		} break;
		case 'R':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			if(a == 0){
				stack.top().push(0);
			}else{
				stack.top().push(b%a);
			}
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

}
