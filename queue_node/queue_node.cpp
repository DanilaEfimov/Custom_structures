#include "queue_node.h"

template<typename T>
bool queue_node<T>::defaultForkCondition() const {
	return this->_Right->empty() && this->_Left->empty();
}

template<typename T>
bool queue_node<T>::defaultStopCondition() const {
	return this->_Right->size() == this->_Left->size();
}

template<typename T>
void queue_node<T>::forkEvent()
{

}

template<typename T>
inline queue_node<T>::queue_node() : queue() {
	this->_Parent = new std::queue<T>();
	this->_Right = new std::queue<T>();
	this->_Left = new std::queue<T>();

	this->_forkCondition = this->defaultForkCondition;
	this->_stopCondition = this->defaultStopCondition;
}

template<typename T>
queue_node<T>::~queue_node()
{
	this->std::queue<T>::~queue();
}

template<typename T>
const T& queue_node<T>::getTrigger() const
{
	// TODO: вставьте здесь оператор return
}

template<typename T>
const T& queue_node<T>::getFront(int _branch) const
{
	// TODO: вставьте здесь оператор return
}

template<typename T>
void queue_node<T>::setForkCondition(bool(*forkCondition)(std::queue<T>&))
{
}

template<typename T>
void queue_node<T>::setStopCondition(bool(*stopCondition)(std::queue<T>&))
{
}

template<typename T>
void queue_node<T>::addItem(T& _item, int _branch)
{
}

template<typename T>
void queue_node<T>::popItem(T& _item, int _branch)
{
}

template<typename T>
bool queue_node<T>::isEmpty(int _branch) const
{
	return false;
}
