/**
 * @file FishStrategy.cpp
 * Strategy for ><> commands.
 * @author Conlan Wesson
 */

#include "FishStrategy.h"
#include "FungeRunner.h"
#include "FungeConfig.h"
#include "FungeUtilities.h"

namespace Funge {

FishStrategy::FishStrategy(FungeRunner& r) :
	FungeStrategy(r),
	regs()
{
	r.pushSemantic('0', std::bind(&FishStrategy::instructionPush, this,  0));
	r.pushSemantic('1', std::bind(&FishStrategy::instructionPush, this,  1));
	r.pushSemantic('2', std::bind(&FishStrategy::instructionPush, this,  2));
	r.pushSemantic('3', std::bind(&FishStrategy::instructionPush, this,  3));
	r.pushSemantic('4', std::bind(&FishStrategy::instructionPush, this,  4));
	r.pushSemantic('5', std::bind(&FishStrategy::instructionPush, this,  5));
	r.pushSemantic('6', std::bind(&FishStrategy::instructionPush, this,  6));
	r.pushSemantic('7', std::bind(&FishStrategy::instructionPush, this,  7));
	r.pushSemantic('8', std::bind(&FishStrategy::instructionPush, this,  8));
	r.pushSemantic('9', std::bind(&FishStrategy::instructionPush, this,  9));
	r.pushSemantic('a', std::bind(&FishStrategy::instructionPush, this, 10));
	r.pushSemantic('b', std::bind(&FishStrategy::instructionPush, this, 11));
	r.pushSemantic('c', std::bind(&FishStrategy::instructionPush, this, 12));
	r.pushSemantic('d', std::bind(&FishStrategy::instructionPush, this, 13));
	r.pushSemantic('e', std::bind(&FishStrategy::instructionPush, this, 14));
	r.pushSemantic('f', std::bind(&FishStrategy::instructionPush, this, 15));
	// Directions
	r.pushSemantic('>', std::bind(&FishStrategy::instructionRight, this));
	r.pushSemantic('<', std::bind(&FishStrategy::instructionLeft, this));
	r.pushSemantic('v', std::bind(&FishStrategy::instructionDown, this));
	r.pushSemantic('^', std::bind(&FishStrategy::instructionUp, this));
	// Mirrors
	r.pushSemantic('\\', std::bind(&FishStrategy::instructionMirror1, this));
	r.pushSemantic('/', std::bind(&FishStrategy::instructionMirror2, this));
	r.pushSemantic('|', std::bind(&FishStrategy::instructionMirrorVert, this));
	r.pushSemantic('_', std::bind(&FishStrategy::instructionMirrorHori, this));
	r.pushSemantic('#', std::bind(&FishStrategy::instructionMirrorAll, this));
	// Movement
	r.pushSemantic('x', std::bind(&FishStrategy::instructionRandom, this));
	r.pushSemantic('!', std::bind(&FishStrategy::instructionTrampoline, this));
	r.pushSemantic('?', std::bind(&FishStrategy::instructionConditional, this));
	r.pushSemantic('.', std::bind(&FishStrategy::instructionJump, this));
	// Arithmetic
	r.pushSemantic('+', std::bind(&FishStrategy::instructionAdd, this));
	r.pushSemantic('-', std::bind(&FishStrategy::instructionSub, this));
	r.pushSemantic('*', std::bind(&FishStrategy::instructionMult, this));
	r.pushSemantic(',', std::bind(&FishStrategy::instructionDiv, this));
	r.pushSemantic('%', std::bind(&FishStrategy::instructionModu, this));
	// Comparisons
	r.pushSemantic('=', std::bind(&FishStrategy::instructionEqual, this));
	r.pushSemantic(')', std::bind(&FishStrategy::instructionGreater, this));
	r.pushSemantic('(', std::bind(&FishStrategy::instructionLess, this));
	// Strings
	r.pushSemantic('\'', std::bind(&FishStrategy::instructionString, this, '\''));
	r.pushSemantic('\"', std::bind(&FishStrategy::instructionString, this, '\"'));
	// Stack Manipulation
	r.pushSemantic(':', std::bind(&FishStrategy::instructionDuplicate, this));
	r.pushSemantic('~', std::bind(&FishStrategy::instructionRemove, this));
	r.pushSemantic('$', std::bind(&FishStrategy::instructionSwap2, this));
	r.pushSemantic('@', std::bind(&FishStrategy::instructionSwap3, this));
	r.pushSemantic('l', std::bind(&FishStrategy::instructionLength, this));
	r.pushSemantic('{', std::bind(&FishStrategy::instructionShiftLeft, this));
	r.pushSemantic('}', std::bind(&FishStrategy::instructionShiftRight, this));
	r.pushSemantic('r', std::bind(&FishStrategy::instructionReverse, this));
	r.pushSemantic('[', std::bind(&FishStrategy::instructionCreateStack, this));
	r.pushSemantic(']', std::bind(&FishStrategy::instructionRemoveStack, this));
	// I/O
	r.pushSemantic('o', std::bind(&FishStrategy::instructionOutChar, this));
	r.pushSemantic('n', std::bind(&FishStrategy::instructionOutInt, this));
	r.pushSemantic('i', std::bind(&FishStrategy::instructionIn, this));
	// Miscellaneous
	r.pushSemantic('&', std::bind(&FishStrategy::instructionRegister, this));
	r.pushSemantic('g', std::bind(&FishStrategy::instructionGet, this));
	r.pushSemantic('p', std::bind(&FishStrategy::instructionPut, this));
	r.pushSemantic(';', std::bind(&FishStrategy::instructionEnd, this));

	regs.push({false, 0});
}

bool FishStrategy::instructionPush(stack_t n){
	stack.top().push(n);
	return true;
}

bool FishStrategy::instructionRight(){
	ip.setDelta(Vector{1, 0});
	return true;
}

bool FishStrategy::instructionLeft(){
	ip.setDelta(Vector{-1, 0});
	return true;
}

bool FishStrategy::instructionDown(){
	ip.setDelta(Vector{0, 1});
	return true;
}

bool FishStrategy::instructionUp(){
	ip.setDelta(Vector{0, -1});
	return true;
}

bool FishStrategy::instructionMirror1(){
	ip.setDelta(Vector{ip.getDelta().get(1), ip.getDelta().get(0)});
	return true;
}

bool FishStrategy::instructionMirror2(){
	ip.setDelta(Vector{-ip.getDelta().get(1), -ip.getDelta().get(0)});
	return true;
}

bool FishStrategy::instructionMirrorVert(){
	ip.setDelta(Vector{-ip.getDelta().get(0), ip.getDelta().get(1)});
	return true;
}

bool FishStrategy::instructionMirrorHori(){
	ip.setDelta(Vector{ip.getDelta().get(0), -ip.getDelta().get(1)});
	return true;
}

bool FishStrategy::instructionMirrorAll(){
	ip.setDelta(Vector{-ip.getDelta().get(0), -ip.getDelta().get(1)});
	return true;
}

bool FishStrategy::instructionRandom(){
	size_t d = funge_config.dimensions*2;
	int r = random(0, d-1);
	Vector v;
	if(r & 1){
		v.set(r>>1, -1);
	}else{
		v.set(r>>1, 1);
	}
	ip.setDelta(v);
	return true;
}

bool FishStrategy::instructionTrampoline(){
	ip.next();
	return true;
}

bool FishStrategy::instructionConditional(){
	if(!stack.top().pop()){
		ip.next();
	}
	return true;
}

bool FishStrategy::instructionJump(){
	stack_t y = stack.top().pop();
	stack_t x = stack.top().pop();
	ip.setPos(Vector{x,y} - ip.getDelta());
	return true;
}

bool FishStrategy::instructionAdd(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(y + x);
	return true;
}

bool FishStrategy::instructionSub(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(y - x);
	return true;
}

bool FishStrategy::instructionMult(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(y * x);
	return true;
}

bool FishStrategy::instructionDiv(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	if(x == 0){
		return false;
	}
	stack.top().push(y / x);
	return true;
}

bool FishStrategy::instructionModu(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	if(x == 0){
		return false;
	}
	stack.top().push(y % x);
	return true;
}

bool FishStrategy::instructionEqual(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(y == x);
	return true;
}

bool FishStrategy::instructionGreater(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(y > x);
	return true;
}

bool FishStrategy::instructionLess(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(y < x);
	return true;
}

bool FishStrategy::instructionString(inst_t i){
	runner.setState(runner.getStringState(i));
	return true;
}

bool FishStrategy::instructionDuplicate(){
	stack_t x = stack.top().pop();
	stack.top().push(x);
	stack.top().push(x);
	return true;
}

bool FishStrategy::instructionRemove(){
	stack.top().pop();
	return true;
}

bool FishStrategy::instructionSwap2(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack.top().push(x);
	stack.top().push(y);
	return true;
}

bool FishStrategy::instructionSwap3(){
	stack_t x = stack.top().pop();
	stack_t y = stack.top().pop();
	stack_t z = stack.top().pop();
	stack.top().push(x);
	stack.top().push(z);
	stack.top().push(y);
	return true;
}

bool FishStrategy::instructionLength(){
	stack.top().push(stack.top().size());
	return true;
}

bool FishStrategy::instructionShiftLeft(){
	stack_t len = stack.top().size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.top().pop();
	}
	for(stack_t i = len-1; i > 0; --i){
		stack.top().push(temp[i-1]);
	}
	stack.top().push(temp[len-1]);
	return true;
}

bool FishStrategy::instructionShiftRight(){
	stack_t len = stack.top().size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.top().pop();
	}
	stack.top().push(temp[0]);
	for(stack_t i = len-1; i > 0; --i){
		stack.top().push(temp[i]);
	}
	return true;
}

bool FishStrategy::instructionReverse(){
	stack_t len = stack.top().size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.top().pop();
	}
	for(stack_t i = 0; i < len; ++i){
		stack.top().push(temp[i]);
	}
	return true;
}

bool FishStrategy::instructionCreateStack(){
	stack_t x = stack.top().pop();
	stack.push();
	for(stack_t i = 0; i < x; ++i){
		stack.top().push(stack.second().pop());
	}
	regs.push({false, 0});
	return true;
}

bool FishStrategy::instructionRemoveStack(){
	while(stack.top().size() > 0){
		stack.second().push(stack.top().pop());
	}
	stack.pop();
	regs.pop();
	return true;
}

bool FishStrategy::instructionOutChar(){
	stack_t x = stack.top().pop();
	std::cout << static_cast<char>(x);
	return true;
}

bool FishStrategy::instructionOutInt(){
	stack_t x = stack.top().pop();
	std::cout << x;
	return true;
}

bool FishStrategy::instructionIn(){
	int q = getchar();
	if(q == EOF){
		q = -1;
	}
	stack.top().push(q);
	return true;
}

bool FishStrategy::instructionGet(){
	const Vector& storage = ip.getStorage();
	Vector v = popVector(stack.top());
	stack.top().push(static_cast<stack_t>(field.get(v+storage)));
	return true;
}

bool FishStrategy::instructionPut(){
	const Vector& storage = ip.getStorage();
	Vector v = popVector(stack.top());
	field.set(v+storage, stack.top().pop());
	return true;
}

bool FishStrategy::instructionEnd(){
	ip.stop();
	return true;
}

bool FishStrategy::instructionRegister(){
	reg& top = regs.top();

	if(top.set){
		top.value = 0;
		top.set = false;
	}else{
		top.value = stack.top().pop();
		top.set = true;
	}

	return true;
}

FungeStrategy* FishStrategy::clone(FungeRunner& r) const{
	return new FishStrategy(r);
}

}