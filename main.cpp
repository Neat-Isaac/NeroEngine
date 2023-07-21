#include "neroengine.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>

//Globals
void MoveCur(short xx,short yy)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{yy,xx});
}

//Pos
nero::Pos::Pos() {};
nero::Pos::Pos(int xx,int yy)
{
	x=xx;
	y=yy;
}
void nero::Pos::Set(int xx,int yy)
{
	x=xx;
	y=yy;
}
bool nero::Pos::operator ==(const Pos &g) const
{
	return x==g.x&&y==g.y;
}
nero::Pos nero::Pos::operator +(const Pos &g) const
{
	return {x+g.x,y+g.y};
}
nero::Pos nero::Pos::operator -(const Pos &g) const
{
	return {x-g.x,y-g.y};
}

//Box
nero::Box::Box() {}
nero::Box::Box(Pos s)
{
	size=s;
}
//SetSize注意不要超过16383，SetPos同
void nero::Box::SetSize(Pos s)
{
	size=s;
}
void nero::Box::SetSize(int w,int h)
{
	size.x=w;
	size.y=h;
}
nero::Pos nero::Box::GetSize()
{
	return size;
}

//Map
nero::Map::Map(Pos s,char c)
{
	memset(tmap,c,sizeof(tmap));
	size=s;
}
void nero::Map::SetDefaultChar(char c)
{
	memset(tmap,c,sizeof(tmap));
}

//Camera
//特别地，相机的坐标与相机长宽的和（seat+size）不能超过16383
nero::Camera::Camera(Pos s,Pos p)
{
	size=s;
	seat=p;
}
void nero::Camera::Init()
{
	system("cls");
	for(int i=seat.y;i<seat.y+size.y;i++)
	{
		for(int j=seat.x;j<seat.x+size.x;j++)
		{
			printf("%c",tmap[i][j]);
			lmap[i-seat.y][j-seat.x]=tmap[i][j];
		}
		printf("\n");
	}
}
void nero::Camera::SetPos(Pos p)
{
	seat=p;
}
void nero::Camera::SetPos(int xx,int yy)
{
	seat.x=xx;
	seat.y=yy;
}
void nero::Camera::Move(Pos p)
{
	seat=seat+p;
}
void nero::Camera::Refresh()
{
	//我认为脏区重绘是好的，毕竟谁愿意看到屏幕一闪一闪的呢
	for(int i=seat.y;i<seat.x+size.y;i++)
	{
		for(int j=seat.x;j<seat.x+size.x;j++)
		{
			if(lmap[i-seat.y][j-seat.x]!=tmap[i][j])
			{
				MoveCur(j-seat.x,i-seat.y);
				printf("%c",tmap[i][j]);
			}
		}
	}
	//当然，如果你想的话，再运行一次Init函数也能达到该函数同样的效果
	//就是屏幕有些过于“闪耀”了
}