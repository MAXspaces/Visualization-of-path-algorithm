#pragma once
#ifndef Iostream_Included
#include<iostream>
#define Iostream_Included
#endif // !Iostream_Included
#ifndef Vector_Included
#include<vector>
#define Vector_Included
using std::vector;
#endif // !Vector_Included

//max distance
#define INF 65535

//point statue
#define Open 0
#define Close 1
#define Not_Access 2
#define Obstacles 3

class Pstatue
{
public:
	int f;
	int g;
	int Point_statue;
	Pstatue( int _f, int _g, int statue)
	{
		f = _f;
		g = _g;
		Point_statue = statue;
	}
};
class Point 
{
public:
	int x;
	int y;
	int f;
	int g;
	int Point_statue;

	Point(int _x,int _y)
	{
		x = _x;
		y = _y;
	}
	Point(int _x, int _y, int _f, int _g)
	{
		x = _x;
		y = _y;
		f = _f;
		g = _g;
	}

	Point() {}

};

class Pathmath
{
public:
	vector<vector<Pstatue>> pathmap;
	vector<vector<Point>> fathermap;

};
class Path
{
public:
	vector<Point> path;
	int length;
};

class HPRESULT
{
public:
	Path path;
	vector<vector<int>> search_zone;


};
class Map 
{
public:
	//par & arg
	vector<vector<int>> map;
	int x_edge, y_edge;

	//function
	Map(int X_edge, int Y_edge);

	int Gen_obstacles(int o_num);
	Point Gen_begin();
	Point Gen_end();
	HPRESULT A_Path(Map& original_map, Point begin, Point end);
	~Map() {}
};
