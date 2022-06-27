#ifndef GraphicsH_Included
#include<graphics.h>
#define GraphicsH_Included
#endif // !GraphicsH_Included

#ifndef MapH_Included
#include"map.h"
#endif //!MapH_Included
class Graphics 
{

public:
	int grid_x;
	int grid_y;
	int grid_size;
public:
	Graphics(int _gridx, int _gridy,int _gridsize)
	{
		grid_size = _gridsize;
		grid_x = _gridx;
		grid_y = _gridy;
	}
	COLORREF gradient__color(COLORREF c_begin, COLORREF c_end, int divstage, int stage)
	{
		int r_begin = GetRValue(c_begin);
		int g_begin = GetGValue(c_begin);
		int b_begin = GetBValue(c_begin);
		int r_end = GetRValue(c_end);
		int g_end = GetGValue(c_end);
		int b_end = GetBValue(c_end);
		return COLORREF(RGB(r_begin + (r_end - r_begin) * stage / divstage, \
			g_begin + (g_end - g_begin) * stage / divstage, \
			b_begin + (b_end - b_begin) * stage / divstage));
	}
	void draw(int x, int y,COLORREF color = WHITE)
	{
		setfillcolor(color);
		solidrectangle(x * grid_size, y * grid_size, (x + 1) * (grid_size), (y + 1) * grid_size);
	}
	void drawpath(Path path, COLORREF color )
	{
		setlinecolor(color);
		setlinestyle(PS_SOLID, grid_size/2, PS_ENDCAP_ROUND, PS_JOIN_ROUND);
		for (int i = 0; i < path.path.size() - 1; i++)
		{
			line(path.path[i].y * grid_size + grid_size / 2,\
				path.path[i].x * grid_size + grid_size / 2, \
				path.path[i + 1].y * grid_size + grid_size / 2,\
				path.path[i + 1].x * grid_size + grid_size / 2);
		}
	}
	void draw_map(Map map)
	{
		for (int i = 0; i < map.x_edge; i++)
		{
			for (int j = 0; j < map.y_edge; j++)
			{
				if (map.map[i][j] == -1)
				{
					draw(j, i);
				}
			}
		}
	}
	void draw_search_zone(HPRESULT result,COLORREF begin_color,COLORREF end_color)
	{
		//find max
		int maxf = 0;
		for (int i = 0; i < result.search_zone.size(); i++)
		{
			for (int j = 0; j < result.search_zone[0].size(); j++)
			{
				if (result.search_zone[i][j] > maxf)
				{
					maxf = result.search_zone[i][j];
				}
			}
		}
		maxf++;
		//generate gradient color
		COLORREF color[15];
		for (int i = 0; i < 10; i++)
		{
			color[i] = gradient__color(begin_color, end_color,10,i+1);
		}

		for (int i = 0; i < result.search_zone.size(); i++)
		{
			for (int j = 0; j < result.search_zone[0].size(); j++)
			{
				if (result.search_zone[i][j] > 0)
				{
					switch (result.search_zone[i][j]*10/maxf)
					{
					case(0):	draw(j, i, color[0]);	break;
					case(1):	draw(j, i, color[1]);	break;
					case(2):	draw(j, i, color[2]);	break;
					case(3):	draw(j, i, color[3]);	break;
					case(4):	draw(j, i, color[4]);	break;
					case(5):	draw(j, i, color[5]);	break;
					case(6):	draw(j, i, color[6]);	break;
					case(7):	draw(j, i, color[7]);	break;
					case(8):	draw(j, i, color[8]);	break;
					case(9):	draw(j, i, color[9]);	break;
					case(10):	draw(j, i, color[10]);	break;
					case(11):	draw(j, i, color[11]);	break;
					case(12):	draw(j, i, color[12]);	break;
					case(13):	draw(j, i, color[13]);	break;
					case(14):	draw(j, i, color[14]);	break;
					}
					//draw(j, i, RGB(2,115,115));
				}
			}
		}
	}

};