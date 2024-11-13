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