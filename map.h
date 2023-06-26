//
// Created by AXuan on 2023/6/20.
// 此类并非部件类，用于读取地图数据
//

#ifndef MAP_H
#define MAP_H

#include <queue>
#include <algorithm>
#include <vector>

#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QIODevice>


#include <opencv2/opencv.hpp>


/* 方向移动数组 */
constexpr int dx[4] = {0,1,0,-1};
constexpr int dy[4] = {1,0,-1,0};

/* 节点信息 */
struct Node
{
	int x, y;           // 坐标{x,y}
	int g, h, f;        // g->从起点到目标点的代价 h->从当前点到目标点的代价 f->g+h
	Node* parent;       // 父节点

	// 构造函数
	Node(int _x, int _y)
		: x(_x), y(_y), g(0), h(0), f(0), parent(nullptr)
	{
	}


	void calManhattan(int targetX, int targetY);           // 曼哈顿距离,计算当前节点到目标节点的启发式代价
	inline void addF();                                    // f=g+h

};

/* 优先队列比较函数 */
struct CompareNodes
{
	bool operator()(const Node* na, const Node* nb);
};


class Map
{
private:


public:
	QVector<QVector<int>> mapArr;

public:
	Map();
	~Map();

	void mapInit();         // 地图初始化


	QVector<Node*> aStar(int startX,int startY,int targetX,int targetY);    // 最短路径
};


#endif //MAP_H
