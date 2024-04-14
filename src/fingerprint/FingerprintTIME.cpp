/**
 * @file FingerprintTIME.cpp
 * Time and Date functions.
 * @author Conlan Wesson
 */

#include "FingerprintTIME.h"
#include <chrono>

namespace Funge {

FingerprintTIME::FingerprintTIME(FungeRunner& r) :
	Fingerprint(r, {'D', 'F', 'G', 'H', 'L', 'M', 'O', 'S', 'W', 'Y'}),
	gmt(false)
{}

FungeError FingerprintTIME::execute(inst_t cmd){
	const std::tm* t = getTime();
	if(t == nullptr){
		return ERROR_UNSPEC;
	}
	switch(cmd){
		case 'D':
			stack.top().push(t->tm_mday);
			break;
		case 'F':
			stack.top().push(t->tm_yday);
			break;
		case 'G':
			gmt = true;
			break;
		case 'H':
			stack.top().push(t->tm_hour);
			break;
		case 'L':
			gmt = false;
			break;
		case 'M':
			stack.top().push(t->tm_min);
			break;
		case 'O':
			stack.top().push(t->tm_mon+1);
			break;
		case 'S':
			stack.top().push(t->tm_sec);
			break;
		case 'W':
			stack.top().push(t->tm_wday+1);
			break;
		case 'Y':
			stack.top().push(t->tm_year+1900);
			break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

const std::tm* FingerprintTIME::getTime(){
	std::time_t t = std::time(nullptr);
	if(gmt){
		return std::gmtime(&t);
	}else{
		return std::localtime(&t);
	}
}

}
