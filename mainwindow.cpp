//
// Created by AXuan on 2023/6/19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
	:
	QWidget(parent), ui(new Ui::MainWindow), map(new Map)
{
	ui->setupUi(this);

	//ui->labelMap->hide();
	ui->labelS->hide();
	ui->labelE->hide();
	bikeStatus(0); // 隐藏状态信息

	// 初始化
	map->mapInit();
	imgRow = map->mapArr.size();
	imgCol = map->mapArr[0].size();

	mapPointInit();
	cbInit();
	bikeInit();
	comboInit();
	gvMapInit();

	this->setWindowFlags(Qt::WindowCloseButtonHint); // 取消最大最小化
	this->setFixedSize(this->width(), this->height()); // 禁止调节大小

	//连接区域

	// [连接comboBox和地图的label显示]使用了Lambda表达式，使之可以传递两个参数给同一个槽函数，以此控制谁进行移动
	connect(ui->comboS, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, true); });
	connect(ui->comboE, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, false); });

	// [连接comboBox和信息显示框tbInfoOut显示]使用了Lambda
	connect(ui->comboS, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ bikeChecked(index, true); });
	connect(ui->comboE, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ bikeChecked(index, false); });

	// [连接radioButton和地图所有label显示]
	connect(ui->rbShowStation, &QPushButton::toggled, this, &MainWindow::showAllStationConnect);

	// [连接pushButton和重置]
	connect(ui->pbRecharge, &QPushButton::clicked, this, [this]()
	{ reCharge(-1); });

	// [连接pushButton和最短路径显示]
	connect(ui->pbRoute, &QPushButton::clicked, this, &MainWindow::routePaint);

	// [连接地图某个checkBox和comboBox显示]
	for (auto& cb : cbArr)
	{
		QString name = cb->text();
		connect(cb, &QCheckBox::stateChanged, this, [this, name](int state)
		{ chooseStation(state, name); });
	}
}

MainWindow::~MainWindow()
{
	delete ui;
	for (auto& vec : cbArr)
		delete vec;
}

/*
 * 函数名 : gvMapInit
 * In : void
 * Out : void
 * 作用 : 地图缩放设置
 */
void MainWindow::gvMapInit()
{
	QGraphicsScene* scene = new QGraphicsScene(this);
	QPixmap pixmap(":/img/image/map.png");

	QLabel* label = new QLabel;
	label->setFixedSize(pixmap.height(), pixmap.width());
	label->setPixmap(pixmap);
	//label->setScaledContents(true);  // 图片随label缩放

	scene->addWidget(label);    // 将 QLabel 添加到 QGraphicsScene 中

	ui->gvMap->setScene(scene);    // 设置 QGraphicsView 显示的场景
	ui->gvMap->setInteractive(true);                  // 允许交互
	ui->gvMap->setDragMode(QGraphicsView::ScrollHandDrag);         // 允许拖拽

	// 缩放平滑处理
	ui->gvMap->setRenderHint(QPainter::Antialiasing);
	ui->gvMap->setRenderHint(QPainter::SmoothPixmapTransform);

	// 隐藏滚动条
	ui->gvMap->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->gvMap->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// 安装事件过滤器，用于鼠标滚轮缩放
	ui->gvMap->installEventFilter(this);

	// 鼠标跟踪
	ui->gvMap->setMouseTracking(true);
}

/*
 * 函数名 : mapPointInit
 * In : void
 * Out : void
 * 作用 : 获取labelMap相对于主窗口的坐标
 */
void MainWindow::mapPointInit()
{
	// 获取地图对于主窗口的坐标
	QPoint mapP = ui->labelMap->mapToGlobal(QPoint(0, 0));
	mapX = mapP.x();
	mapY = mapP.y();
}

/*
 * 函数名 : comboInit
 * In : null
 * Out : null
 * 作用 : 填充comboBox
 */
void MainWindow::comboInit()
{
	QStringList stationNameList = csvInfoGet(1); // 获取第二列信息
	QStringList stationIdList = csvInfoGet(0);   // 获取第一列信息

	ui->comboS->addItems(stationNameList);          // 载入
	ui->comboE->addItems(stationNameList);
}

/*
 * 函数名 : csvInfoGet
 * In : int
 * Out : QStringList
 * 作用 : 返回csv指定列的信息
 */
QStringList MainWindow::csvInfoGet(int indexCol)
{
	// 绝对路径 TODO:[优化]修改为相对路径获取塌方式
	QString filePath = "D:/Files_Work/Code/JetBrains/CLion/Project/CyclingSystem/data/info.csv";

	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return {};
	}

	QStringList colDataList;           // 数据列表
	QTextStream in(&file);
	int lineCount = 0;
	while (!in.atEnd() && lineCount < ROW)              // 当列表不再最后一列
	{
		QString line = in.readLine();
		QStringList col = line.split(',');
		if (col.size() > 1)
		{
			QString colData = col.at(indexCol);        // 读取第二列数据，也就是Station Name
			colDataList.append(colData);               // 将数据载入列表
		}
		++lineCount;
	}
	file.close();                                  // 关闭文件

	return colDataList;
}

/*
 *  函数名 : showStation
 *  In : index
 *  Out : null
 *  作用 : 将实际坐标映射到地图上
 */
void MainWindow::showStation(int index, bool sw) //TODO:[?]这里可能可以通过vector labels进行优化
{
	QPair<int, int> pair = mapPointGet(index);       // 获取指定行的地图对应坐标

	if (sw)
	{
		ui->labelS->move(pair.first, pair.second);     // 移动
		ui->labelS->show();                // 显示
	}
	else
	{
		ui->labelE->move(pair.first, pair.second);     // 移动
		ui->labelE->show();                // 显示
	}
}

/*
 * 函数名 : fileInfoGet
 * In : int row , col
 * Out : QString
 * 作用 : 获取csv文件里[row,col]坐标的信息，并以QString的形式返回
 */
QString MainWindow::fileInfoGet(int row, int col)
{
	QString filePath = "D:/Files_Work/Code/JetBrains/CLion/Project/CyclingSystem/data/info.csv";
	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return {};
	}

	QTextStream in(&file);
	QStringList fields;     // 存储每一列的每一个元素，这些元素使用逗号分割
	int lineCount = 0;
	QString coordinate;

	while (!in.atEnd())
	{
		QString line = in.readLine();   // 读取当前行，并移动至下一行

		if (lineCount == row)
		{
			fields = line.split(',');   // 分割并存储
			coordinate = fields.at(col); // 定位，转换，取绝对值
			file.close();
			return coordinate;
		}

		++lineCount;
	}

	return {}; // 错误返回
}

/*
 *  函数名 : showAllStationConnect
 *  In : bool
 *  Out : void
 *  作用 : 显示地图上所有的站点
 *  属性 : SLOT
 */
void MainWindow::showAllStationConnect(bool checked)
{
	if (!checked)
	{
		for (auto& vec : cbArr)
			vec->hide();
		reCharge(2);
		reCharge(3);
		return;
	}

	// 隐藏之前的ui
	ui->labelS->hide();
	ui->labelE->hide();

	for (const auto& vec : cbArr)
	{
		vec->show();
	}

}

/*
 * 函数名 : mapPointGet
 * In : index  指定行
 * Out : QPair<int,int>  {x,y}
 * 作用 : 获取指定行的地图对应坐标
 */
QPair<int, int> MainWindow::mapPointGet(int index)
{
	// csv中坐标的x，y最小值
	double min_x = 87.586924;
	double min_y = 41.80091;

	// 获取真实坐标
	double cur_x = abs(fileInfoGet(index, 6).toDouble());
	double cur_y = abs(fileInfoGet(index, 7).toDouble());

	// 获取换算坐标（这里使用了比例因子计算，公式为(original - min) * scale，(20,110)是地图的左上角坐标
	int x = round((cur_x - min_x) * x_scale) + mapX; // 四舍五入
	int y = round((cur_y - min_y) * y_scale) + mapY;

	return QPair<int, int>(x, y);
}

/*
 * 函数名 : cbInit
 * In : void
 * Out : void
 * 作用 : 初始化labels容器
 */
void MainWindow::cbInit()
{
	for (int i = 1; i < ROW; ++i)
	{
		cbArr.push_back(new QCheckBox(this));

		QPair<int, int> qp = mapPointGet(i);
		cbArr.back()->move(qp.first, qp.second); // 移动坐标
		cbArr.back()->setText(QString::number(i));     // 设置索引值，方便后续选取时定位comboBox TODO:[优化]将文本隐藏
		cbArr.back()->hide();
	}
}

/*
 * 函数名 : chooseStation
 * In : int[复选状态] , QString[复选框名字]
 * Out : void
 * 作用 : 复选框选中的时候，comboBox进行更改
 */
void MainWindow::chooseStation(int state, QString name)
{
	if (!state)
	{
		if (chooseCount == 1)
		{
			ui->comboS->setCurrentIndex(0);
			--chooseCount;
		}
		return;
	}


	if (chooseCount == 0)
		reCharge(1);

	++chooseCount;

	if (state == Qt::Checked)   // 当勾选上时
	{
		if (chooseCount == 1)
		{
			ui->comboS->setCurrentIndex(name.toInt());  // 将Start复选框移动
		}

		else
			ui->comboE->setCurrentIndex(name.toInt());  // 将End复选框移动
	}

	if (chooseCount > 1)
	{
		chooseCount = 0;                        // 归零
		showAllStationConnect(false);   // 隐藏所有选项
		ui->rbShowStation->setChecked(false);   // 取消选择
	}
}

/*
 * 函数名 : recharge
 * In : mode[模式选择]
 * Out : void
 * 作用 : 根据mode进行重置
 */
void MainWindow::reCharge(int mode)
{
	if (mode == 1) // 重置comboBox
	{
		ui->comboS->setCurrentIndex(0);
		ui->comboE->setCurrentIndex(0);
	}
	else if (mode == 2)   // 重置复选框
	{
		for (auto& cb : cbArr)
			cb->setChecked(false);
	}
	else if (mode == 3)
	{
		for (auto& lb : labelArr)
			lb->setHidden(true);
	}
	else if (mode == -1)    // 全部重置
	{
		reCharge(1);
		reCharge(2);
		reCharge(3);
		bikeStatus(0);
	}
}

/*
 * 函数名 : bikeInit
 * In : void
 * Out : void
 * 作用 : 根据csv信息来初始化单车总量和单车可用量
 */
void MainWindow::bikeInit()
{
	QStringList bikeTotal = csvInfoGet(3);
	QStringList bikeService = csvInfoGet(4);

	bikeArr.resize(2);
	bikeArr[0].resize(bikeTotal.size());
	bikeArr[1].resize(bikeService.size());

	for (int i = 1; i < ROW; ++i)
	{
		bool checkedA, checkedB;
		int valT = bikeTotal.at(i).toInt(&checkedA);
		int valS = bikeService.at(i).toInt(&checkedB);
		if (checkedA && checkedB)
		{
			bikeArr[0][i] = valT;
			bikeArr[1][i] = valS;
		}
	}
}

/*
 * 函数名 : bikeChecked
 * In : index[combo的索引]
 * Out : void
 * 作用 : 根据索引查询相对应的单车总量和可用单车
 */
void MainWindow::bikeChecked(int index, bool checked)
{
	int totalInt = bikeArr[0][index];
	int serviceInt = bikeArr[1][index];


	if (checked)
	{
		ui->lcdStartTotal->display(totalInt);
		ui->lcdStartService->display(serviceInt);
		if (serviceInt > 0)
		{
			bikeStatus(-2); // 更改状态
			bikeStatus(1);
		}
		else
		{
			bikeStatus(-1);
			bikeStatus(2);
		}

	}
	else
	{
		ui->lcdEndTotal->display(totalInt);
		ui->lcdEndService->display(serviceInt);
		if (totalInt > serviceInt)
		{
			bikeStatus(-4); // 更改状态
			bikeStatus(3);
		}
		else
		{
			bikeStatus(-3);
			bikeStatus(4);
		}

	}

}

/*
 * 函数名 : bikeStatus
 * In : mode[模式选择]
 * Out : void
 * 作用 : 根据模式代码控制STATUS状态栏信息
 */
void MainWindow::bikeStatus(int mode)
{
	switch (mode)
	{
	case 0:
		bikeStatus(-1);
		bikeStatus(-2);
		bikeStatus(-3);
		bikeStatus(-4);
		break;

	case 1:
		ui->labelBikeStartGood->show();
		break;
	case -1:
		ui->labelBikeStartGood->hide();
		break;

	case 2:
		ui->labelBikeStartBad->show();
		break;
	case -2:
		ui->labelBikeStartBad->hide();
		break;

	case 3:
		ui->labelBikeEndGood->show();
		break;
	case -3:
		ui->labelBikeEndGood->hide();
		break;

	case 4:
		ui->labelBikeEndBad->show();
		break;
	case -4:
		ui->labelBikeEndBad->hide();
		break;
	default:
		return;
	}
}

/*
 * 【重要函数】
 * 函数名 : routePaint
 * In : void
 * Out : void
 * 作用 : 路线绘制
 */
void MainWindow::routePaint()
{
	Point4 p4 = pointGet();

	bool checkedStart = false;
	bool checkedTarget = false;

	// 移动p4的点,使其均位于map的1处
	int startX = p4.x1 - mapX;
	int startY = p4.y1 - mapY;
	int targetX = p4.x2 - mapX;
	int targetY = p4.y2 - mapY;

	if (startX < 0 || startX > imgCol || targetX < 0 || targetX > imgCol || startY < 0 || startY > imgRow || targetY < 0
		|| targetY > imgRow)
		return;

	// 求出距离马路的最短路径
	QPoint pStart;
	QPoint pTarget;
	pStart = { 10000, 10000 };
	pTarget = { 10000, 10000 };
	for (int i = 0; i < 4; ++i)
	{
		if (map->mapArr[startY][startX])
		{
			checkedStart = true;
			pStart = { 0, 0 };
		}

		if (map->mapArr[targetY][targetX])
		{
			pTarget = { 0, 0 };
			checkedTarget = true;
		}
		if (checkedStart && checkedTarget) // 起点和目标点均位于路上，跳出循环
			break;

		if (!checkedStart)
		{
			QPoint pStartTemp = checkPoint(startY, startX, dx[i], dy[i]);
			if (abs(pStartTemp.x() + pStartTemp.y()) < abs(pStart.x() + pStart.y()))
				pStart = pStartTemp;
		}
		if (!checkedTarget)
		{
			// {0,1}向下 {1,0}向右 {0,-1}向上 {-1,0}向左
			QPoint pTargetTemp = checkPoint(targetY, targetX, dx[i], dy[i]);
			if (abs(pTargetTemp.x() + pTargetTemp.y()) < abs(pTarget.x() + pTarget.y()))
				pTarget = pTargetTemp;
		}

	}
	int TempX;
	int TempY;

	// 起点
	TempX = startX;
	TempY = startY;
	if (pStart.x() != 0)
		if (pStart.x() > 0)
			for (int i = 0; i < pStart.x(); ++i)
				mapPointDraw(TempX, TempY++);
		else
			for (int i = 0; i > pStart.x(); --i)
				mapPointDraw(TempX, TempY--);
	else if (pStart.y() != 0)
		if (pStart.y() > 0)
			for (int i = 0; i < pStart.y(); ++i)
				mapPointDraw(TempX++, TempY);
		else
			for (int i = 0; i > pStart.y(); --i)
				mapPointDraw(TempX--, TempY);

	// 目标点
	TempX = targetX;
	TempY = targetY;
	if (pTarget.x() != 0)
		if (pTarget.x() > 0)
			for (int i = 0; i < pTarget.x(); ++i)
				mapPointDraw(TempX, TempY++);
		else
			for (int i = 0; i > pTarget.x(); --i)
				mapPointDraw(TempX, TempY--);
	else if (pTarget.y() != 0)
		if (pTarget.y() > 0)
			for (int i = 0; i < pTarget.y(); ++i)
				mapPointDraw(TempX++, TempY);
		else
			for (int i = 0; i > pTarget.y(); --i)
				mapPointDraw(TempX--, TempY);

	startY += pStart.x();
	startX += pStart.y();
	targetY += pTarget.x();
	targetX += pTarget.y();

	QVector<Node*> nodes = map->aStar(startY, startX, targetY, targetX);       // 在map.h中获取最短路径坐标点

	for (const auto& n : nodes)
	{
		mapPointDraw(n->y, n->x);  // mapArr的{y,x}相当于labelMap的{x,y}
	}
}

/*
 * 函数名 : pointGet
 * In : void
 * Out : Point4[涵盖四个坐标的结构体]
 * 作用 : 返回两个label的坐标
 */
Point4 MainWindow::pointGet()
{
	//TODO:[优化]将其再化多一个函数，这个函数获取指定部件的坐标

	// 获取两个地图上的Label的全局坐标
	QPoint startPoint = ui->labelS->pos();
	QPoint endPoint = ui->labelE->pos();

	int startX = startPoint.x();
	int startY = startPoint.y();
	int targetX = endPoint.x();
	int targetY = endPoint.y();

	return Point4(startX, startY, targetX, targetY);
}

/*
 * 函数名 : mapPointDraw
 * In : {x,y} [坐标信息]
 * Out : void
 * 作用 : 根据坐标在labelMap绘制地图
 */
void MainWindow::mapPointDraw(int x, int y)
{
	labelArr.push_back(new QLabel(this));
	labelArr.back()->setGeometry(QRect(x + mapX, y + mapY, 2, 2));   // 这里的{x,y}相对于坐标是反着来的
	labelArr.back()->setPixmap(QPixmap(QString::fromUtf8(":/img/image/spot.png")));
	labelArr.back()->setScaledContents(true);
	labelArr.back()->show();
}

/*
 * 函数名 : checkedPoint
 * In : int [行、列、行变化量、列变化量]
 * Out : QPoint [{行变化量，列变化量}]
 * 作用 : 返回{row,col}里最近道路的距离
 */
QPoint MainWindow::checkPoint(int row, int col, int m, int n)
{
	if (row + m < 0 || col + n < 0 || row + m >= imgRow || col + n >= imgCol)
		return { 20000, 20000 };

	while (!map->mapArr[row + m][col + n])
	{
		if (row + m < 0 || col + n < 0 || row + m >= imgRow || col + n >= imgCol)
			return { 20000, 20000 };
		m == 0 ? n > 0 ? ++n : --n : m > 0 ? ++m : --m;
	}

	return { m, n };
}

/*
 * 【按键跟踪系统】
 * 函数名 : eventFilter
 * In : QObject QEvent
 * Out : void
 * 作用 : 控制滑轮与缩放
 */
bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	// 事件类型 : 缩放+-
	if (obj == ui->gvMap && event->type() == QEvent::KeyPress)
	{
		// 将事件转换为滚轮事件
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if(keyEvent->key() == '-')
		{
			ui->gvMap->scale(0.8,0.8);

		}
		else if(keyEvent->key() == '=')
		{
			ui->gvMap->scale(1.2,1.2);
		}
		// 返回 true 表示已处理该事件
		return true;
	}

	return QObject::eventFilter(obj, event);
}








