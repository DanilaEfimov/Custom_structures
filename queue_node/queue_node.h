#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include<queue>
#include<iostream>

enum {
	parent, right, left
};

template<typename T>
class queue_node {
protected:
	std::queue<T>* _Parent;
	std::queue<T>* _Right;
	std::queue<T>* _Left;

public:
	queue_node() {
		this->_Parent = new std::queue<T>();
		this->_Right = new std::queue<T>();
		this->_Left = new std::queue<T>();
	};
	virtual ~queue_node() {
		delete this->_Parent;
		delete this->_Right;
		delete this->_Left;
	};

	void push() {
		static bool isEmpty = false;	// "cash"
		if (isEmpty) {
			return;
		}
		if (!this->_Parent->empty()) {
			isEmpty = false;
			if (this->_Right->size() < this->_Left->size()) {
				const T trigger = this->_Parent->front(); // trigger-woman
				this->_Right->push(trigger);
				this->_Parent->pop();
			}
			else if (this->_Right->size() > this->_Left->size()) {
				const T trigger = this->_Parent->front(); // trigger-woman
				this->_Left->push(trigger);
				this->_Parent->pop();
			}
		}
		else {
			isEmpty = true;
		}
	}

	// ACCESSORS
	const T& getTrigger() const {
		return this->getTrigger();
	};

	const T& getFront(int _branch) const {
		switch (_branch) {
		case parent: return this->_Parent->front(); break;
		case left: return this->_Left->front(); break;
		case right: return this->_Right->front(); break;
		default: return this->getTrigger(); break;
		}
		return this->getTrigger();
	};

	virtual std::queue<T>* getChild(int _branch = parent) const {	// cringe
		switch (_branch) {
		case parent: return this->_Parent;
		case right: return this->_Right;
		case left: return this->_Left;
		default:
			return this->_Parent;
			break;
		}
	}

	void add(const T _item, int _branch) {
		switch (_branch) {
		case parent: this->_Parent->push(_item); break;
		case left: this->_Left->push(_item); break;
		case right: this->_Right->push(_item); break;
		default: break;
		}
	};

	void pop(int _branch) {
		switch (_branch) {
		case parent: this->_Parent->pop(); break;
		case left: this->_Left->pop(); break;
		case right: this->_Right->pop(); break;
		default: 
			break;
		}
	};

	virtual bool isEmpty(int _branch) const {
		switch (_branch) {
		case parent: return this->_Parent->empty(); break;
		case right: return this->_Right->empty(); break;
		case left: return this->_Left->empty(); break;
		default:
			return true;
			break;
		}
	};

	virtual void terminate() {
		std::cout << "\t";
		while (!this->isEmpty(left)) {
			std::cout << this->getFront(left) << ' ';
			this->pop(left);
		}
		std::cout << "\n\t\t\t\t";
		while (!this->isEmpty(parent)) {
			std::cout << this->getFront(parent) << ' ';
			this->pop(parent);
		}
		std::cout << "\n\t";
		while (!this->isEmpty(right)) {
			std::cout << this->getFront(right) << ' ';
			this->pop(right);
		}
		std::cout << std::endl;
	}
};

#endif

/*
Background:
I was standing in line at the post office recently. There were two windows, respectively, two QUEUES. There was one woman
who could not decide which window she needed and was "in superposition", waiting in both queues.
Illustration:
													-------------- 1st window
My queue --------------------- trigger-woman	|
													-------------- 2nd window

I decided to summarize this situation in the form of a queue_node data structure. Why _node? This is the most interesting part.
It turned out that this structure is recursive, that is, there is a tree of this type:

														-------------------			ect.
								--------------------- [								//////////////
							  /							-------------------			
------------------------------														//////////////
							  \							-------------------			
								--------------------- [								//////////////
														-------------------			

Here, each node of the tree is a queue.
After I told my friend about this idea, he said it was very similar to load balancer
(I looked with one eye - this is some kind of entity distributing the load between the servers)
It really looks like it, I thought.
But there the children were servers, and in our case, the queue.
In general, it's definitely interesting, maybe this is how you can describe the hierarchy of threads, for example 
(I have no experience in multithreaded programming)
*/