#include "My20210124.h"

void MyStudy20210124::main()
{
	Player p1(20);
	Player p2(44);

	PlayerObserver po;
	p1.Subscribe(&po);
	p2.Subscribe(&po);

	p1.move(3);
	p2.move(6);
	
}
