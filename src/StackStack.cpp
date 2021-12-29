/**
 * @file StackStack.cpp
 * Stack of Stacks
 * @author Conlan Wesson
 */

#include "StackStack.h"

namespace Funge {

StackStack::StackStack(FungeRunner& r) :
	runner(r),
	stack()
{
	stack.push_back(Stack(*this));
}

StackStack::StackStack(const StackStack& orig, FungeRunner& r) :
	runner(r),
	stack()
{
	for(size_t i = 0; i < orig.size(); ++i){
		stack.push_back(Stack(orig.at(i), *this));
	}
}

Stack& StackStack::top(){
	return stack.back();
}

Stack& StackStack::second(){
	return stack[stack.size()-2];
}

Stack& StackStack::at(size_t x){
	return stack[x];
}

const Stack& StackStack::top() const{
	return stack.back();
}

const Stack& StackStack::second() const{
	return stack[stack.size()-2];
}

const Stack& StackStack::at(size_t x) const{
	return stack[stack.size()-x-1];
}

void StackStack::pop(){
	stack.pop_back();
}

void StackStack::push(){
	stack.push_back(Stack(*this));
}

size_t StackStack::size() const{
	return stack.size();
}

FungeRunner& StackStack::getRunner(){
	return runner;
}

}
