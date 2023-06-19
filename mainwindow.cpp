//
// Created by AXuan on 2023/6/19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
	:
	QWidget(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->labelS->hide();
	ui->labelE->hide();

	cbInit();
	comboGet();

	//连接区域

	// [连接comboBox和地图的label显示]使用了Lambda表达式，使之可以传递两个参数给同一个槽函数，以此控制谁进行移动
	connect(ui->comboS, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, true); });
	connect(ui->comboE, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, false); });

	// [连接radioButton和地图所有label显示]
	connect(ui->rbShowStation, &QPushButton::toggled, this, &MainWindow::showAllStationConnect);

	// [连接radioButton和重置]
	connect(ui->pbRecharge,&QPushButton::clicked,this,[this](){reCharge(3);});

	// [连接地图某个checkBox和comboBox显示]
	for (auto& cb : cbArr)
	{
		QString name = cb->text();
		connect(cb, &QCheckBox::stateChanged, this, [this, name](int state)
		{ chooseStation(state, name);});
	}



}

MainWindow::~MainWindow()
{
	delete ui;
	for (auto& vec : cbArr)
		delete vec;
}

/*
 * 函数名 : comboGet
 * In : null
 * Out : null
 * 作用 : 填充comboBox
 */
void MainWindow::comboGet()
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
		ui->tbInfoOut->setText("ERROR,Please Download The Software Again");
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
		ui->tbInfoOut->setText("ERROR");
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
	double min_x = 87.586924;
	double min_y = 41.80091;

	// 获取真实坐标
	double cur_x = abs(fileInfoGet(index, 6).toDouble());
	double cur_y = abs(fileInfoGet(index, 7).toDouble());

	// 获取换算坐标（这里使用了比例因子计算，公式为(original - min) * scale，(20,110)是地图的左上角坐标
	int x = round((cur_x - min_x) * x_scale) + 20; // 四舍五入
	int y = round((cur_y - min_y) * y_scale) + 110;

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
		if(chooseCount==1)
		{
			ui->comboS->setCurrentIndex(0);
			--chooseCount;
		}
		return;
	}


	if(chooseCount==0)
		reCharge(1);

	++chooseCount;

	if (state == Qt::Checked)   // 当勾选上时
	{
		if(chooseCount==1)
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
 *
 */
void MainWindow::reCharge(int mode)
{
	if(mode==1) // 重置comboBox
	{
		ui->comboS->setCurrentIndex(0);
		ui->comboE->setCurrentIndex(0);
	}
	else if(mode==2)   // 重置复选框
	{
		for(auto&cb:cbArr)
			cb->setChecked(false);
	}
	else if(mode==3)    // 全部重置
	{
		reCharge(1);
		reCharge(2);
	}
}





