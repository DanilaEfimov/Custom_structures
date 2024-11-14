#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include<queue>

template<typename T>
class queue_node
{
	enum {
		parent, right, left
	};
private:
	std::queue<T>* _Parent;
	std::queue<T>* _Right;
	std::queue<T>* _Left;
	bool(*_forkCondition)(queue_node<T>&);
	bool(*_stopCondition)(queue_node<T>&);
	void(*_event)(queue_node<T>&);

	virtual bool defaultForkCondition(queue_node<T>&) const {
		return !(this->_Right->empty() || this->_Left->empty());
	};
	virtual bool defaultStopCondition(queue_node<T>&) const {
		return this->_Right->size() == this->_Left->size();
	};
	virtual void defaultForkEvent(queue_node<T>&) const {
		static bool isEmpty = false;	// "cash"
		if (isEmpty) {
			return;
		}
		if (!this->_Parent->empty()) {
			isEmpty = true;
			if (this->_Right->size() < this->_Left->size()) {
				const T trigger = this->_Parent->front(); // trigger-woman
				this->_Right->push(trigger);
				this->_Parent->pop();
			}
			else if (this->_Right->size > this->_Left->size()) {
				const T trigger = this->_Parent->front(); // trigger-woman
				this->_Left->push(trigger);
				this->_Parent->pop();
			}
		}
		else {
			isEmpty = true;
		}
	};
public:
	queue_node() {
		this->_Parent = new std::queue<T>();
		this->_Right = new std::queue<T>();
		this->_Left = new std::queue<T>();

		this->_forkCondition = (bool)this->defaultForkCondition(queue_node<T>&);
		this->_stopCondition = (bool)this->defaultStopCondition(queue_node<T>&);
		this->_event = (void)this->defaultForkEvent(queue_node<T>&);
	};
	virtual ~queue_node() {
		delete this->_Parent;
		delete this->_Right;
		delete this->_Left;
	};

	// ACCESSORS
	const T& getTrigger() const {
		return this->getTrigger();
	};
	const T& getFront(int _branch) const {
		switch (_branch) {
		case parent: return this->_Perent->front(); break;
		case left: return this->_Left->front(); break;
		case right: return this->_Right->front(); break;
		default: return this->getTrigger(); break;
		}
		return this->getTrigger();
	};
	void setForkCondition(bool(*forkCondition)(std::queue<T>&)) {
		this->_forkCondition = forkCondition;
	};
	void setStopCondition(bool(*stopCondition)(std::queue<T>&)) {
		this->_stopCondition = stopCondition;
	}
	void setEvent(void(*event)(queue_node<T>&)) {
		this->_event = event;
	}

	void addItem(T& _item, int _branch) {
		switch (_branch) {
		case parent: this->_Parent->push(_item); break;
		case left: this->_Left->push(_item); break;
		case right: this->_Right->push(_item); break;
		default: break;
		}
	};
	void popItem(int _branch) {
		switch (_branch) {
		case parent: return this->getTrigger(); break;
		case left: return this->_Left->front(); break;
		case right: return this->_Right->front(); break;
		default: return this->getTrigger(); break;
		}
	};
	bool isEmpty(int _branch) const{
	return this->_Parent->empty();
};
};

#endif

/*
�����������:
� ����� ������� � ������� �� �����. ��� ���� ��� ����, ��������������, ��� �������. ���� ���� �������,
������� �� ����� ������������, � ����� ���� �� ����� � "���������� � ������������", ����� � ����� ��������.
�����������:
													-------------- ����1
��� ������� --------------------- �������-�������	|
													-------------- ����2

� ����� �������� ��� �������� � ���� ��������� ������ queue_node. ������ _node? ����� ����� ����������.
���������, ��� ��� ��������� �����������, �� ���� ����� ����� ������ ������ ����:

														-------------------			� ��� �����
								--------------------- [								//////////////
							  /							-------------------			
------------------------------														//////////////
							  \							-------------------			
								--------------------- [								//////////////
														-------------------			

����� ������ ���� ������ - �������.
����� � ��������� ��� ��� ���� ������ ��������, �� ������, ��� ��� ����� ������ �� load balancer 
(� ��������� ����� ������ - ��� ����� �������� �������������� �������� ����� ���������)
������������� ������ - ������� �.
�� ��� ���� ���� ���������, � � ����� ������ - �������.
� ����� ��� ����� ���������, ����� ��� ����� ��������� �������� ������� �������� (�� ���� ���� � 
������������� ����������������)
*/