#include"map.h"

int m_distance(Point point1, Point point2)
{
	return (fabs(point1.x - point2.x) + fabs(point1.y - point2.y)) * 10;
}

Map::Map(int X_edge, int Y_edge)
{
	x_edge = X_edge;
	y_edge = Y_edge;
	vector<int>Line;
	for (int i = 0; i < X_edge; i++)
	{
		Line.push_back(0);
	}
	for (int j = 0; j < Y_edge; j++)
	{
		map.push_back(Line);
	}
	//setting edge
	for(int i =0;i<X_edge;i++)
	{
		map[0][i] = -1;
		map[y_edge - 1][i] = -1;
	}
	for (int j = 0; j < y_edge; j++)
	{
		map[j][0] = -1;
		map[j][x_edge - 1]= - 1;
	}
}
int Map::Gen_obstacles(int o_num = 0)
{
	if (o_num > (x_edge - 2) * (y_edge - 2))
	{
		std::cout << "fail to generate obstacles\n";
		return -1;
	}
	while (o_num)
	{
		int x = 2 + rand() % (x_edge - 2);
		int y = 2 + rand() % (y_edge - 2);
		if (map[x][y] != -1)
		{
			map[x][y] = -1;
			o_num--;
		}
	}
	return 0;
}

Point Map::Gen_begin()
{
	int x = 2 + rand() % (x_edge - 2);
	int y = 2 + rand() % (y_edge - 2);
	while ((map[x][y] == -1))
	{
		x = 2 + rand() % (x_edge - 2);
		y = 2 + rand() % (y_edge - 2);
	}
	map[x][y] = 1;
	return Point(x,y);
}

Point Map::Gen_end()
{
	int x = 2 + rand() % (x_edge - 2);
	int y = 2 + rand() % (y_edge - 2);
	while ((map[x][y] == -1))
	{
		x = 2 + rand() % (x_edge - 2);
		y = 2 + rand() % (y_edge - 2);
	}
	map[x][y] = 1;
	return Point(x, y);
}


void insert(vector<Point>&list,Point point)
{
	if (list.size() == 0)
	{
		list.push_back(point);
		return;
	}
	int i = 0;
	while ((i < list.size()) &&(point.f > list[i].f))
	{
		i++;
	}
	list.insert(list.begin() + i,point);
}

HPRESULT Map::A_Path(Map& original_map, Point begin, Point end)
{
	//Note:
	// 1.The distance for F would be Manhattan distance 
	// 
	//A* ini
	vector<Point> openlist;
	vector<Point> closelist;

	//gennerate pathmap for path calculation
	Pathmath pathmap;
	int x_edge = original_map.x_edge;
	int y_edge = original_map.y_edge;
	for (int i = 0; i < y_edge; i++)
	{
		vector<Pstatue> Pst_line;
		vector<Point> father_line;
		for (int j = 0; j < y_edge; j++)
		{
			if (original_map.map[i][j] == -1)
			{
				Pst_line.push_back(Pstatue(INF, INF, Obstacles));
			}

			else
			{
				Pst_line.push_back(Pstatue(INF, INF, Not_Access));
			}

			father_line.push_back(Point(0,0));
		}
		pathmap.pathmap.push_back(Pst_line);
		pathmap.fathermap.push_back(father_line);
	}

	pathmap.pathmap[begin.x][begin.y].g = 0;
	pathmap.pathmap[begin.x][begin.y].f = m_distance(begin,end);

	openlist.push_back(Point(begin.x,begin.y,m_distance(begin,end),0));


	while ((pathmap.pathmap[end.x][end.y].Point_statue != Close)&&(openlist.size()!=0))
	{
		//pick the best value point from openlist 
		Point AnalyzieP = openlist[0];
		openlist.erase(openlist.begin());//delete Analyzie Point in open list

		//search 8 direction
		// f = g + h 
		{
			//left
			if (((pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x ][AnalyzieP.y - 1].Point_statue == Open))\
				&& (pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].g > AnalyzieP.g + 10))
			{
				pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].g = AnalyzieP.g + 10;	// update distance
				pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].f = AnalyzieP.g + 10 + m_distance(Point(AnalyzieP.x, AnalyzieP.y - 1), end);//update f
				pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x][AnalyzieP.y - 1] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x, AnalyzieP.y - 1, m_distance(Point(AnalyzieP.x, AnalyzieP.y - 1), end) + AnalyzieP.g + 10, AnalyzieP.g + 10);
				insert(openlist, insertpoint);
			}

			//right
			if (((pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x][AnalyzieP.y +1].Point_statue == Open)) \
				&& (pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].g > AnalyzieP.g + 10))
			{
				pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].g = AnalyzieP.g + 10;	// update distance
				pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].f = AnalyzieP.g + 10 + m_distance(Point(AnalyzieP.x, AnalyzieP.y + 1), end);//update f
				pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x][AnalyzieP.y + 1] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x, AnalyzieP.y + 1, m_distance(Point(AnalyzieP.x, AnalyzieP.y + 1), end) + AnalyzieP.g + 10, AnalyzieP.g + 10);
				insert(openlist, insertpoint);
			}

			//front
			if (((pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].Point_statue == Open)) \
				&& (pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].g > AnalyzieP.g + 10))
			{
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].g = AnalyzieP.g + 10;	// update distance
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y ].f = AnalyzieP.g + 10 + m_distance(Point(AnalyzieP.x - 1, AnalyzieP.y), end);//update f
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x - 1][AnalyzieP.y] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x - 1, AnalyzieP.y, m_distance(Point(AnalyzieP.x - 1, AnalyzieP.y), end) + AnalyzieP.g + 10, AnalyzieP.g + 10);
				insert(openlist, insertpoint);
			}

			//rare
			if (((pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].Point_statue == Open))\
				&& (pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].g > AnalyzieP.g + 10))
			{
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].g = AnalyzieP.g + 10;	// update distance
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].f = AnalyzieP.g + 10 + m_distance(Point(AnalyzieP.x + 1, AnalyzieP.y), end);//update f
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x + 1][AnalyzieP.y] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x + 1, AnalyzieP.y, m_distance(Point(AnalyzieP.x + 1, AnalyzieP.y), end) + AnalyzieP.g + 10, AnalyzieP.g + 10);
				insert(openlist, insertpoint);
			}
		}

		//now we set the rule that if there is a obstacles at the corner we can't walk through it
		{
			//front left
		
			if (((pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y - 1].Point_statue == Not_Access)||(pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y - 1].Point_statue == Open))\
				&& pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].Point_statue != Obstacles \
				&& pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].Point_statue != Obstacles \
				&& (pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y - 1].g > AnalyzieP.g + 14))
				//line2&line3 are the judgement of corner obstacles
			{
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y - 1].g = AnalyzieP.g + 14;	// update distance
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y - 1].f = AnalyzieP.g + 14 + m_distance(Point(AnalyzieP.x - 1, AnalyzieP.y - 1), end);//update f
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y - 1].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x - 1][AnalyzieP.y - 1] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x - 1, AnalyzieP.y - 1, m_distance(Point(AnalyzieP.x - 1, AnalyzieP.y - 1), end) + AnalyzieP.g + 14, AnalyzieP.g + 14);
				insert(openlist, insertpoint);
			}

			//front right
			if (((pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].Point_statue == Open))\
				&& pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y].Point_statue != Obstacles \
				&& pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].Point_statue != Obstacles \
				&& (pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].g > AnalyzieP.g + 14))
				//line2&line3 are the judgement of corner obstacles
			{
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].g = AnalyzieP.g + 14;	// update distance
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].f = AnalyzieP.g + 14 + m_distance(Point(AnalyzieP.x - 1, AnalyzieP.y + 1), end);//update f
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x - 1][AnalyzieP.y + 1] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x - 1, AnalyzieP.y + 1, m_distance(Point(AnalyzieP.x - 1, AnalyzieP.y + 1), end) + AnalyzieP.g + 14, AnalyzieP.g + 14);
				insert(openlist, insertpoint);
			}

			//rare left
			if (((pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y - 1].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y - 1].Point_statue == Open))\
				&& pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].Point_statue != Obstacles \
				&& pathmap.pathmap[AnalyzieP.x][AnalyzieP.y - 1].Point_statue != Obstacles \
				&& (pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y - 1].g > AnalyzieP.g + 14))
				//line2&line3 are the judgement of corner obstacles
			{
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y - 1].g = AnalyzieP.g + 14;	// update distance
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y - 1].f = AnalyzieP.g + 14 + m_distance(Point(AnalyzieP.x + 1, AnalyzieP.y - 1), end);//update f
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y - 1].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x + 1][AnalyzieP.y - 1] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x + 1, AnalyzieP.y - 1, m_distance(Point(AnalyzieP.x + 1, AnalyzieP.y - 1), end) + AnalyzieP.g + 14, AnalyzieP.g + 14);
				insert(openlist, insertpoint);
			}

			//rare right
			if (((pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y + 1].Point_statue == Not_Access) || (pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y + 1].Point_statue == Open))\
				&& pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y].Point_statue != Obstacles \
				&& pathmap.pathmap[AnalyzieP.x][AnalyzieP.y + 1].Point_statue != Obstacles \
				&& (pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y + 1].g > AnalyzieP.g + 14))
				//line2&line3 are the judgement of corner obstacles
			{
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y + 1].g = AnalyzieP.g + 14;	// update distance
				pathmap.pathmap[AnalyzieP.x - 1][AnalyzieP.y + 1].f = AnalyzieP.g + 14 + m_distance(Point(AnalyzieP.x + 1, AnalyzieP.y + 1), end);//update f
				pathmap.pathmap[AnalyzieP.x + 1][AnalyzieP.y + 1].Point_statue = Open; // update statute
				pathmap.fathermap[AnalyzieP.x + 1][AnalyzieP.y + 1] = AnalyzieP;	// update point's father
				Point insertpoint(AnalyzieP.x + 1, AnalyzieP.y + 1, m_distance(Point(AnalyzieP.x + 1, AnalyzieP.y + 1), end) + AnalyzieP.g + 14, AnalyzieP.g + 14);
				insert(openlist, insertpoint);
			}
		}



		pathmap.pathmap[AnalyzieP.x][AnalyzieP.y].Point_statue = Close;//upstate the statute of the ana point

	}

//show the searching path for test
#ifdef A_Path_Test



	std::cout << begin.x << "  " << begin.y << "\n";
	for (int i = 0; i < x_edge; i++)
	{
		for (int j = 0; j < y_edge; j++)
		{
			std::cout.width(9);
			std::cout << pathmath.pathmap[i][j].g;
		}
		std::cout << "\n";
	}
	std::cout << begin.x << "  " << begin.y << "\n";
	for (int i = 0; i < x_edge; i++)
	{
		for (int j = 0; j < y_edge; j++)
		{
			std::cout.width(9);
			std::cout << pathmath.fathermap[i][j].x<<","<< pathmath.fathermap[i][j].y;
		}
		std::cout << "\n";
	}

#endif // A_Path_Test


	//if A* can't find a way to the end point -_-
	if (openlist.size() == 0)
	{
		std::cout << "There is no path from(" << begin.x << "," << begin.y << ") to (" << end.x << "," << end.y << ")";
		return HPRESULT();// return none to the callermember;
	}
	//trace back the path
	Path path;
	Point TracePoint(end.x,end.y);
	vector<Point> ReversePath;
	int len = 0;
	while ((TracePoint.x != begin.x) || (TracePoint.y != begin.y))
	{
		//one push_back one pop_back
		ReversePath.push_back(TracePoint);
		int cach_x = pathmap.fathermap[TracePoint.x][TracePoint.y].x;
		int cach_y = pathmap.fathermap[TracePoint.x][TracePoint.y].y;
		TracePoint.x = cach_x;
		TracePoint.y = cach_y;
		map[cach_x][cach_y] = 2;
		len++;

	}
	ReversePath.push_back(begin);
	int reversize = ReversePath.size();
	path.length = len;
	for (int i = 0; i < reversize ; i++)
	{
		path.path.push_back(ReversePath[reversize - 1 - i]);
	}



#ifdef A_Path_Test
	for (int i = 0; i < path.path.size(); i++)
	{
		std::cout << path.path[i].x << "," << path.path[i].y<<"\n";
	}
#endif // A_Path_Test
	HPRESULT result;
	result.path = path;
	vector<int> cache_Line;
	for (int i = 0; i < x_edge; i++)
	{	
		for (int j = 0; j < y_edge; j++)
		{
			if ((pathmap.pathmap[i][j].Point_statue == Open) || (pathmap.pathmap[i][j].Point_statue == Close))
			{
				cache_Line.push_back(pathmap.pathmap[i][j].g);
			}
			else
			{
				cache_Line.push_back(0);
			}
		}
		result.search_zone.push_back(cache_Line);
		vector<int>().swap(cache_Line);
	}

	return result;
}
