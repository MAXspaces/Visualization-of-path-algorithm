#include<iostream>
#include"Grap.h"
#include"map.h"

//#include"Grap.h"
int main()
{
	int size = 100;
	HPRESULT PathResult;
	Map map(size, size);
	map.Gen_obstacles(2500);
	Point begin = map.Gen_begin();
	Point end = map.Gen_end();
	PathResult = map.A_Path(map, begin, end);
	

//out put the map in command line 
#ifdef Char_Map_Output
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (map.map[i][j] == -1)
			{
				std::cout << '#';
			}
			else
			{
				std::cout << ' ';
			}
		}
	}

#endif // Char_Map_Output

	//print out the path
	std::cout << "PATH:\n";
	for (int i = 0; i < PathResult.path.path.size(); i++)
	{
		if (i != PathResult.path.path.size() - 1)
			std::cout << "(" << PathResult.path.path[i].x << "," << PathResult.path.path[i].y << ")" << "-->";
		else
			std::cout << "(" << PathResult.path.path[i].x << "," << PathResult.path.path[i].y << ")" ;
	}
	std::cout << "\n";
	initgraph(1000, 1000);
	Graphics* graphics = new Graphics(size,size,10);

	graphics->draw_map(map);
	graphics->draw_search_zone(PathResult,COLORREF(RGB(189, 227, 242)), COLORREF(RGB(29, 82, 115)));
	graphics->drawpath(PathResult.path, RGB(1, 40, 64));

	system("pause");
	delete graphics;
	closegraph();


	//to do the path should have a Reverse gradient color of the search zone
}