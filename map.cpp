//
// Created by AXuan on 2023/6/20.
//

#include "map.h"


Map::Map()
{

}

/*
 * ������ : mapInit
 * In : void
 * Out : void
 * ���� : ��ʼ����ͼ������ͼ�ϵĵ�·ӳ�䵽����
 * ע�� : �˺���ʹ�õ�opencv��ȡͼ�񣬲�����ת��Ϊ0��1��������ʹ��astarѰ�����·��
 */
void Map::mapInit()
{
	/* image */
	QImage mapImg(":/img/image/testB.png"); // �򿪵�ͼ
	if (mapImg.isNull())
	{
		qDebug() << "ERROR";
		return;
	}
	/* image */

	/* opencv */
	// �� QImage ת��Ϊ OpenCV �� Mat ��ʽ
	cv::Mat mapMat(mapImg.height(), mapImg.width(), CV_8UC4, mapImg.bits(), mapImg.bytesPerLine());
	// ��ͼ��ת��Ϊ�Ҷ�ͼ
	cv::Mat grayMat;
	cv::cvtColor(mapMat, grayMat, cv::COLOR_BGR2GRAY);
	// �ԻҶ�ͼ������ֵ�ָ��ȡ��·����
	cv::Mat thresholdMat;
	cv::threshold(grayMat, thresholdMat, 200, 255, cv::THRESH_BINARY);
	/* opencv */

	/* File */ //TODO:[�Ż�]���ļ�����Ϣʱ�����ļ���������
	QFile file("D:/Files_Work/Code/JetBrains/CLion/Project/CyclingSystem/data/map.txt");
	QTextStream out(&file); // �����ļ����������ļ�����
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
				mapArr[i][j] = 0; // ��֮��Ϊ����ͨ��

			//out<<mapArr[i][j]; file
		}
		//out<<"\n"; file
	}

}

/*
 * ������ : ��������
 * In : Node*
 * Out : bool
 * ���� : �������ȶ��еıȼۺ���
 */
bool CompareNodes::operator()(const Node* na, const Node* nb)
{
	return na->f > nb->f;
}


/*
 * ������ : calManhattan
 * In : int[Ŀ���{x,y}]
 * Out : void
 * ���� : ���㵱ǰ�㵽Ŀ���������پ���
 */
void Node::calManhattan(int targetX, int targetY)
{
	h = abs(targetX - x) + abs(targetY - y);
}


/*
 * ������ : addF [��Ƕ����]
 * In : void
 * Out : void
 * ���� : ���ټ���f��ֵ
 */
inline void Node::addF()
{
	f = g + h;
}


/*
 * ������ : aStar
 * In : int[start{x,y} target{x,y}]
 * Out : QVector<Node*> [·��]
 * ���� : AStar�㷨�������·��
 */
QVector<Node*> Map::aStar(int startX, int startY, int targetX, int targetY)
{
	int row = mapArr.size();
	int col = mapArr[0].size();

	// �ڵ��ͼ�������������˵�ͼ����������
	QVector<QVector<Node*>> nodeMap(row, QVector<Node*>(col));
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			nodeMap[i][j] = new Node(i, j);

	// �����б� �պ��б� �ڱ�
	// �����б��������б������С�����پ���Ľڵ�
	// �պ��б�����������ŷ������·���Ľڵ㣬��·��
	// �ڱ�������ͬ�ڿ����б�ĵײ���������������Ѿ�������������
	std::priority_queue<Node*, QVector<Node*>, CompareNodes> openList;
	QVector<Node*> closeList;
	QVector<Node*> visited;

	// ���Ŀ��Node��ʼ��
	Node* startNode = nodeMap[startX][startY];
	Node* targetNode = nodeMap[targetX][targetY];
	startNode->calManhattan(targetX, targetY);  // �����h
	startNode->addF();  // ����f

	// �������
	openList.push(startNode);
	visited.push_back(startNode);

	// AStar����
	while (!openList.empty())
	{
		Node* currNode = openList.top();
		openList.pop();
		visited.removeAll(currNode); // ��openListͬ��

		// ·���������
		if (currNode == targetNode)
		{
			QVector<Node*> path;

			// ���ڵ�����Path
			while (currNode != nullptr)
			{
				path.push_back(currNode);    // ����
				currNode = currNode->parent;      // �ص��丸�ڵ�
			}
			return path;
		}

		// ·��δ�������

		// ����ǰ�ڵ���ӵ��պ��б���ʱ�Ŀ����б�����Ѿ������˵�ǰ��������Ž�
		// ��˿���ֱ�Ӽ���պ��б��Ҳ��ٶԸýڵ���б���
		closeList.push_back(currNode);

		// �����ĸ�����
		for (int i = 0; i < 4; ++i)
		{
			int neighborX = currNode->x + dx[i];
			int neighborY = currNode->y + dy[i];

			// ���ڵ��Ƿ��ڷ�Χ��
			if (neighborX > 0 && neighborX < row && neighborY > 0 && neighborY < col)
			{
				Node* neighborNode = nodeMap[neighborX][neighborY]; // �½��ھӽڵ�

				// �ϰ�������Ѿ�λ��·���Ľڵ�
				if (mapArr[neighborX][neighborY] == 0
					|| std::find(closeList.begin(), closeList.end(), neighborNode) != closeList.end())
				{
					continue; // �Թ��ýڵ�
				}

				int newCost = currNode->g + 1; // g��ʾ�߹��ĳ���

				// �����ڽڵ�[����openList]����[���Ѹ���]ʱ�����½ڵ���Ϣ
				if (std::find(visited.begin(),visited.end(),neighborNode)==visited.end() || newCost < neighborNode->g))
				{
					neighborNode->g = newCost;
					neighborNode->calManhattan(targetX,targetY);
					neighborNode->addF();
					neighborNode->parent=currNode;

					// �������ڽڵ�[����openList(�ڱ�visited)],������openList���ڱ���������
					if(std::find(visited.begin(),visited.end(),neighborNode)==visited.end())
					{
						openList.push(neighborNode);
						visited.push_back(neighborNode);    // ��openListͬ��
					}
				}
			}
		}
	}

	return {}; // null��δ�ҵ�
}



