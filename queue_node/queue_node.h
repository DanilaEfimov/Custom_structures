#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include<queue>

template<typename T = int>
class queue_node : public std::queue<T>
{
	enum {
		parent, right, left
	};
private:
	std::queue<T>* _Parent;
	std::queue<T>* _Right;
	std::queue<T>* _Left;
	bool(*_forkCondition)(std::queue<T>&);
	bool(*_stopCondition)(std::queue<T>&);
	void(*_event)(queue_node<T>&);

	virtual bool defaultForkCondition() const;
	virtual bool defaultStopCondition() const;
	virtual void forkEvent();
public:
	queue_node();
	virtual ~queue_node();

	// ACCESSORS
	const T& getTrigger() const;
	const T& getFront(int _branch) const;
	void setForkCondition(bool(*forkCondition)(std::queue<T>&));
	void setStopCondition(bool(*stopCondition)(std::queue<T>&));

	void addItem(T& _item, int _branch);
	void popItem(T& _item, int _branch);
	virtual bool isEmpty(int _branch) const;
};

#endif

/*
Предыстория:
Я стоял недавно в очереди на почте. Там было два окна, соответственно, две ОЧЕРЕДИ. Была одна женщина,
которая не могла определиться, в какое окно ей нужно и "находилась в суперпозиции", ждала в обеих очередях.
Иллюстрация:
													-------------- Окно1
Моя очередь --------------------- Женщина-триггер	|
													-------------- Окно2

Я решил обобщить эту ситуацию в виде структуры данных queue_node. Почему _node? Здесь самое интересное.
Оказалось, что эта структура рекурсивная, то есть имеет место дерево такого вида:

														-------------------			и так далее
								--------------------- [								//////////////
							  /							-------------------			
------------------------------														//////////////
							  \							-------------------			
								--------------------- [								//////////////
														-------------------			

Здесь каждый узел дерева - очередь.
После я рассказал про эту идею своему приятелю, он сказал, что это очень похоже на load balancer 
(я посмотрел одним глазом - это некая сущность распределяющая нагрузку между серверами)
Действительно похоже - подумал я.
Но там дети были серверами, а в нашем случае - очередь.
В общем это точно интересно, может так можно описывать иерархию потоков например (не имею опыт в 
многопоточном программировании)
*/