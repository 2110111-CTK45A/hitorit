#ifndef HANDLER_H
#define HANDLER_H


#include "HitoriGenerator/BinaryBoard.h"
#include "HitoriGenerator/ComplexBoard.h"
#include "HitoriGenerator/TestBoard.h"

namespace HitoriGenerator {

template<class I, class O>
class Handler<I, O> {
public:
	//Handler() : nextHandler(nullptr) {}
	//Handler *set_next(Handler *handler) override {
		//this->nextHandler = handler;
		//return handler;
	//}
	virtual O process(I input) = 0;

//private:
	//Handler *nextHandler;
};

class BinaryHandler : public Handler<int, BinaryBoard> {
	BinaryBoard process(int input) override {
		return BinaryBoard(input)
	}
};
class ComplexHandler : public Handler<BinaryBoard, ComplexBoard> {
	ComplexBoard process(BinaryBoard input) override {
		return ComplexBoard(input)
	}
};
class TestHandler : public Handler<ComplexBoard, TestBoard> {
	TestBoard process(ComplexBoard input) override {
		return TestBoard(input)
	}
};


template<class I, class O>
class Pipeline<I, O> {
private:
	Handler<I, O> *currentHandler;
public:
	Pipeline(Handler<I, O> *handler) {
		this->currentHandler - handler
	}
	template<class K>
	Pipeline<I, K> add_handler(Handler<O, K> newHandler) {
		return new Pipeline<>([](I input){newHandler.process(currentHandler.process(input))});
	}
	O execute(I input) {
		return currentHandler.process(input);
	}
};

}


#endif
