//
// Created by AXuan on 2023/6/20.
//

#include "map.h"


Map::Map()
{

}

/*
 * 函数名 : mapInit
 * In : void
 * Out : void
 * 作用 : 初始化地图，讲地图上的道路映射到数组
 * 注意 : 此函数使用到opencv读取图像，并将其转化为0和1，供后续使用astar寻求最短路径
 */
void Map::mapInit()
{
	/* image */
	QImage mapImg(":/img/image/testB.png"); // 打开地图
	if (mapImg.isNull())
	{
		qDebug() << "ERROR";
		return;
	}
	/* image */

	/* opencv */
	// 将 QImage 转换为 OpenCV 的 Mat 格式
	cv::Mat mapMat(mapImg.height(), mapImg.width(), CV_8UC4, mapImg.bits(), mapImg.bytesPerLine());
	// 将图像转换为灰度图
	cv::Mat grayMat;
	cv::cvtColor(mapMat, grayMat, cv::COLOR_BGR2GRAY);
	// 对灰度图进行阈值分割，提取道路区域
	cv::Mat thresholdMat;
	cv::threshold(grayMat, thresholdMat, 200, 255, cv::THRESH_BINARY);
	/* opencv */

	/* File */ //TODO:[优化]当文件有信息时，从文件读入数组
	QFile file("D:/Files_Work/Code/JetBrains/CLion/Project/CyclingSystem/data/map.txt");
	QTextStream out(&file); // 创建文件流对象，与文件关联
	file.open(QIODevice::ReadWrite | QIODevice::Text);
	/* File */

	int row = mapImg.height();
	int col = mapImg.width();
	mapArr.resize(row, QVector<int>(col));

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (thresholdMat.at<uchar>(i, j) == 255)
				mapArr[i][j] = 1;
			else
				mapArr[i][j] = 0; // 反之，为不可通行

			//out<<mapArr[i][j]; file
		}
		//out<<"\n"; file
	}

}

/*
 * 函数名 : 运算重载
 * In : Node*
 * Out : bool
 * 作用 : 用于优先队列的比价函数
 */
bool CompareNodes::operator()(const Node* na, const Node* nb)
{
	return na->f > nb->f;
}


/*
 * 函数名 : calManhattan
 * In : int[目标点{x,y}]
 * Out : void
 * 作用 : 计算当前点到目标点的曼哈顿距离
 */
void Node::calManhattan(int targetX, int targetY)
{
	h = abs(targetX - x) + abs(targetY - y);
}


/*
 * 函数名 : addF [内嵌函数]
 * In : void
 * Out : void
 * 作用 : 快速计算f的值
 */
inline void Node::addF()
{
	f = g + h;
}


/*
 * 函数名 : aStar
 * In : int[start{x,y} target{x,y}]
 * Out : QVector<Node*> [路径]
 * 作用 : AStar算法，求最短路径
 */
QVector<Node*> Map::aStar(int startX, int startY, int targetX, int targetY)
{
	int row = mapArr.size();
	int col = mapArr[0].size();

	// 节点地图，此容器代表了地图的所有像素
	QVector<QVector<Node*>> nodeMap(row, QVector<Node*>(col));
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			nodeMap[i][j] = new Node(i, j);

	// 开放列表 闭合列表 哨兵
	// 开放列表——优先列表，存放最小曼哈顿距离的节点
	// 闭合列表——容器，存放符合最短路径的节点，即路径
	// 哨兵——等同于开放列表的底层容器，用来存放已经遍历过的数据
	std::priority_queue<Node*, QVector<Node*>, CompareNodes> openList;
	QVector<Node*> closeList;
	QVector<Node*> visited;

	// 起点目标Node初始化
	Node* startNode = nodeMap[startX][startY];
	Node* targetNode = nodeMap[targetX][targetY];
	startNode->calManhattan(targetX, targetY);  // 计算出h
	startNode->addF();  // 计算f

	// 推入队列
	openList.push(startNode);
	visited.push_back(startNode);

	// AStar主体
	while (!openList.empty())
	{
		Node* currNode = openList.top();
		openList.pop();
		visited.removeAll(currNode); // 与openList同步

		// 路径搜索完成
		if (currNode == targetNode)
		{
			QVector<Node*> path;

			// 将节点载入Path
			while (currNode != nullptr)
			{
				path.push_back(currNode);    // 载入
				currNode = currNode->parent;      // 回到其父节点
			}
			return path;
		}

		// 路径未搜索完成

		// 将当前节点添加到闭合列表，此时的开放列表最顶端已经代表了当前局面的最优解
		// 因此可以直接加入闭合列表且不再对该节点进行遍历
		closeList.push_back(currNode);

		// 遍历四个方向
		for (int i = 0; i < 4; ++i)
		{
			int neighborX = currNode->x + dx[i];
			int neighborY = currNode->y + dy[i];

			// 检测节点是否在范围内
			if (neighborX > 0 && neighborX < row && neighborY > 0 && neighborY < col)
			{
				Node* neighborNode = nodeMap[neighborX][neighborY]; // 新建邻居节点

				// 障碍物或则已经位于路径的节点
				if (mapArr[neighborX][neighborY] == 0
					|| std::find(closeList.begin(), closeList.end(), neighborNode) != closeList.end())
				{
					continue; // 略过该节点
				}

				int newCost = currNode->g + 1; // g表示走过的长度

				// 当相邻节点[不在openList]或者[花费更少]时，更新节点信息
				if (std::find(visited.begin(),visited.end(),neighborNode)==visited.end() || newCost < neighborNode->g))
				{
					neighborNode->g = newCost;
					neighborNode->calManhattan(targetX,targetY);
					neighborNode->addF();
					neighborNode->parent=currNode;

					// 若此相邻节点[不在openList(哨兵visited)],则载入openList和哨兵进行排列
					if(std::find(visited.begin(),visited.end(),neighborNode)==visited.end())
					{
						openList.push(neighborNode);
						visited.push_back(neighborNode);    // 与openList同步
					}
				}
			}
		}
	}

	return {}; // null，未找到
}



