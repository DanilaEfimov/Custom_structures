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
Ïðåäûñòîðèÿ:
ß ñòîÿë íåäàâíî â î÷åðåäè íà ïî÷òå. Òàì áûëî äâà îêíà, ñîîòâåòñòâåííî, äâå Î×ÅÐÅÄÈ. Áûëà îäíà æåíùèíà,
êîòîðàÿ íå ìîãëà îïðåäåëèòüñÿ, â êàêîå îêíî åé íóæíî è "íàõîäèëàñü â ñóïåðïîçèöèè", æäàëà â îáåèõ î÷åðåäÿõ.
Èëëþñòðàöèÿ:
													-------------- Îêíî1
Ìîÿ î÷åðåäü --------------------- Æåíùèíà-òðèããåð	|
													-------------- Îêíî2

ß ðåøèë îáîáùèòü ýòó ñèòóàöèþ â âèäå ñòðóêòóðû äàííûõ queue_node. Ïî÷åìó _node? Çäåñü ñàìîå èíòåðåñíîå.
Îêàçàëîñü, ÷òî ýòà ñòðóêòóðà ðåêóðñèâíàÿ, òî åñòü èìååò ìåñòî äåðåâî òàêîãî âèäà:

														-------------------			è òàê äàëåå
								--------------------- [								//////////////
							  /							-------------------			
------------------------------														//////////////
							  \							-------------------			
								--------------------- [								//////////////
														-------------------			

Çäåñü êàæäûé óçåë äåðåâà - î÷åðåäü.
Ïîñëå ÿ ðàññêàçàë ïðî ýòó èäåþ ñâîåìó ïðèÿòåëþ, îí ñêàçàë, ÷òî ýòî î÷åíü ïîõîæå íà load balancer 
(ÿ ïîñìîòðåë îäíèì ãëàçîì - ýòî íåêàÿ ñóùíîñòü ðàñïðåäåëÿþùàÿ íàãðóçêó ìåæäó ñåðâåðàìè)
Äåéñòâèòåëüíî ïîõîæå - ïîäóìàë ÿ.
Íî òàì äåòè áûëè ñåðâåðàìè, à â íàøåì ñëó÷àå - î÷åðåäü.
Â îáùåì ýòî òî÷íî èíòåðåñíî, ìîæåò òàê ìîæíî îïèñûâàòü èåðàðõèþ ïîòîêîâ íàïðèìåð (íå èìåþ îïûò â 
ìíîãîïîòî÷íîì ïðîãðàììèðîâàíèè)
*/
