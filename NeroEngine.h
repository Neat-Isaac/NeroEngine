#ifndef _NERO_DLL_H_
#define _NERO_DLL_H_

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

namespace nero
{
	const int MAX_HEIGHT=16384;		//地图和相机的最大高度
	const int MAX_WIDTH=16384;		//地图和相机的最大宽度
	const int N=MAX_HEIGHT;			//最大高度别称
	const int M=MAX_WIDTH;			//最大宽度别称
	
	char tmap[N][M];			//地图字符矩阵
	/*

	坐标系：
	x轴水平，y轴竖直；
	x越往左越大，y越往下越大。

	*/
	struct Pos						//也许可以用STL的pair代替
	{
		int x,y;
		
		Pos();
		Pos(int xx,int yy);
		
		void Set(int xx,int yy);	//Set什么？Set坐标
		
		bool operator ==(const Pos &g) const;
		Pos operator +(const Pos &g) const;
		Pos operator -(const Pos &g) const;
	};
	
	struct Box						//抽象的盒子类
	{
		Pos size;					//盒子长宽
		
		//构造函数们
		//你只能用Pos结构体来初始化盒子长宽	
		Box();
		Box(Pos s);
		
		//但是你可以用两个变量来设置盒子长宽
		void SetSize(Pos s);
		void SetSize(int w,int h);
		Pos GetSize();
	};
	
	struct Map:Box
	{
		Pos size;
		
		Map(Pos s,char c);
		
		void SetDefaultChar(char c);
		Pos GetSize();
	};
	
	struct Camera:Box
	{
		//如果你用Refresh函数的话，
		//不要在游戏画面最上面输出一些乱七八糟的东西，
		//不然这玩意会乱
		
		Pos seat;					//左上角顶点坐标
		Pos size;
		char lmap[N][M];			//上一个屏幕，用于判断脏区
		
		Camera(Pos s,Pos p);		//先传大小后传坐标
		
		void Init();				//输出画面
		void SetPos(Pos p);
		void SetPos(int xx,int yy);
		void Move(Pos p);			//传入x和y的变化量
		Pos GetPos();
		void Refresh();				//脏区重绘
	};
}

#endif
