//
// Created by AXuan on 2023/6/20.
// ���ಢ�ǲ����࣬���ڶ�ȡ��ͼ����
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


/* �����ƶ����� */
constexpr int dx[4] = {0,1,0,-1};
constexpr int dy[4] = {1,0,-1,0};

/* �ڵ���Ϣ */
struct Node
{
	int x, y;           // ����{x,y}
	int g, h, f;        // g->����㵽Ŀ���Ĵ��� h->�ӵ�ǰ�㵽Ŀ���Ĵ��� f->g+h
	Node* parent;       // ���ڵ�

	// ���캯��
	Node(int _x, int _y)
		: x(_x), y(_y), g(0), h(0), f(0), parent(nullptr)
	{
	}


	void calManhattan(int targetX, int targetY);           // �����پ���,���㵱ǰ�ڵ㵽Ŀ��ڵ������ʽ����
	inline void addF();                                    // f=g+h

};

/* ���ȶ��бȽϺ��� */
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

	void mapInit();         // ��ͼ��ʼ��


	QVector<Node*> aStar(int startX,int startY,int targetX,int targetY);    // ���·��
};


#endif //MAP_H
