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
	bikeStatus(0); // ����״̬��Ϣ

	// ��ʼ��
	map->mapInit();
	imgRow = map->mapArr.size();
	imgCol = map->mapArr[0].size();

	mapPointInit();
	cbInit();
	bikeInit();
	comboInit();
	gvMapInit();

	this->setWindowFlags(Qt::WindowCloseButtonHint); // ȡ�������С��
	this->setFixedSize(this->width(), this->height()); // ��ֹ���ڴ�С

	//��������

	// [����comboBox�͵�ͼ��label��ʾ]ʹ����Lambda���ʽ��ʹ֮���Դ�������������ͬһ���ۺ������Դ˿���˭�����ƶ�
	connect(ui->comboS, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, true); });
	connect(ui->comboE, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, false); });

	// [����comboBox����Ϣ��ʾ��tbInfoOut��ʾ]ʹ����Lambda
	connect(ui->comboS, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ bikeChecked(index, true); });
	connect(ui->comboE, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ bikeChecked(index, false); });

	// [����radioButton�͵�ͼ����label��ʾ]
	connect(ui->rbShowStation, &QPushButton::toggled, this, &MainWindow::showAllStationConnect);

	// [����pushButton������]
	connect(ui->pbRecharge, &QPushButton::clicked, this, [this]()
	{ reCharge(-1); });

	// [����pushButton�����·����ʾ]
	connect(ui->pbRoute, &QPushButton::clicked, this, &MainWindow::routePaint);

	// [���ӵ�ͼĳ��checkBox��comboBox��ʾ]
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
 * ������ : gvMapInit
 * In : void
 * Out : void
 * ���� : ��ͼ��������
 */
void MainWindow::gvMapInit()
{
	QGraphicsScene* scene = new QGraphicsScene(this);
	QPixmap pixmap(":/img/image/map.png");

	QLabel* label = new QLabel;
	label->setFixedSize(pixmap.height(), pixmap.width());
	label->setPixmap(pixmap);
	//label->setScaledContents(true);  // ͼƬ��label����

	scene->addWidget(label);    // �� QLabel ��ӵ� QGraphicsScene ��

	ui->gvMap->setScene(scene);    // ���� QGraphicsView ��ʾ�ĳ���
	ui->gvMap->setInteractive(true);                  // ������
	ui->gvMap->setDragMode(QGraphicsView::ScrollHandDrag);         // ������ק

	// ����ƽ������
	ui->gvMap->setRenderHint(QPainter::Antialiasing);
	ui->gvMap->setRenderHint(QPainter::SmoothPixmapTransform);

	// ���ع�����
	ui->gvMap->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->gvMap->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// ��װ�¼�����������������������
	ui->gvMap->installEventFilter(this);

	// ������
	ui->gvMap->setMouseTracking(true);
}

/*
 * ������ : mapPointInit
 * In : void
 * Out : void
 * ���� : ��ȡlabelMap����������ڵ�����
 */
void MainWindow::mapPointInit()
{
	// ��ȡ��ͼ���������ڵ�����
	QPoint mapP = ui->labelMap->mapToGlobal(QPoint(0, 0));
	mapX = mapP.x();
	mapY = mapP.y();
}

/*
 * ������ : comboInit
 * In : null
 * Out : null
 * ���� : ���comboBox
 */
void MainWindow::comboInit()
{
	QStringList stationNameList = csvInfoGet(1); // ��ȡ�ڶ�����Ϣ
	QStringList stationIdList = csvInfoGet(0);   // ��ȡ��һ����Ϣ

	ui->comboS->addItems(stationNameList);          // ����
	ui->comboE->addItems(stationNameList);
}

/*
 * ������ : csvInfoGet
 * In : int
 * Out : QStringList
 * ���� : ����csvָ���е���Ϣ
 */
QStringList MainWindow::csvInfoGet(int indexCol)
{
	// ����·�� TODO:[�Ż�]�޸�Ϊ���·����ȡ����ʽ
	QString filePath = "D:/Files_Work/Code/JetBrains/CLion/Project/CyclingSystem/data/info.csv";

	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return {};
	}

	QStringList colDataList;           // �����б�
	QTextStream in(&file);
	int lineCount = 0;
	while (!in.atEnd() && lineCount < ROW)              // ���б������һ��
	{
		QString line = in.readLine();
		QStringList col = line.split(',');
		if (col.size() > 1)
		{
			QString colData = col.at(indexCol);        // ��ȡ�ڶ������ݣ�Ҳ����Station Name
			colDataList.append(colData);               // �����������б�
		}
		++lineCount;
	}
	file.close();                                  // �ر��ļ�

	return colDataList;
}

/*
 *  ������ : showStation
 *  In : index
 *  Out : null
 *  ���� : ��ʵ������ӳ�䵽��ͼ��
 */
void MainWindow::showStation(int index, bool sw) //TODO:[?]������ܿ���ͨ��vector labels�����Ż�
{
	QPair<int, int> pair = mapPointGet(index);       // ��ȡָ���еĵ�ͼ��Ӧ����

	if (sw)
	{
		ui->labelS->move(pair.first, pair.second);     // �ƶ�
		ui->labelS->show();                // ��ʾ
	}
	else
	{
		ui->labelE->move(pair.first, pair.second);     // �ƶ�
		ui->labelE->show();                // ��ʾ
	}
}

/*
 * ������ : fileInfoGet
 * In : int row , col
 * Out : QString
 * ���� : ��ȡcsv�ļ���[row,col]�������Ϣ������QString����ʽ����
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
	QStringList fields;     // �洢ÿһ�е�ÿһ��Ԫ�أ���ЩԪ��ʹ�ö��ŷָ�
	int lineCount = 0;
	QString coordinate;

	while (!in.atEnd())
	{
		QString line = in.readLine();   // ��ȡ��ǰ�У����ƶ�����һ��

		if (lineCount == row)
		{
			fields = line.split(',');   // �ָ�洢
			coordinate = fields.at(col); // ��λ��ת����ȡ����ֵ
			file.close();
			return coordinate;
		}

		++lineCount;
	}

	return {}; // ���󷵻�
}

/*
 *  ������ : showAllStationConnect
 *  In : bool
 *  Out : void
 *  ���� : ��ʾ��ͼ�����е�վ��
 *  ���� : SLOT
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

	// ����֮ǰ��ui
	ui->labelS->hide();
	ui->labelE->hide();

	for (const auto& vec : cbArr)
	{
		vec->show();
	}

}

/*
 * ������ : mapPointGet
 * In : index  ָ����
 * Out : QPair<int,int>  {x,y}
 * ���� : ��ȡָ���еĵ�ͼ��Ӧ����
 */
QPair<int, int> MainWindow::mapPointGet(int index)
{
	// csv�������x��y��Сֵ
	double min_x = 87.586924;
	double min_y = 41.80091;

	// ��ȡ��ʵ����
	double cur_x = abs(fileInfoGet(index, 6).toDouble());
	double cur_y = abs(fileInfoGet(index, 7).toDouble());

	// ��ȡ�������꣨����ʹ���˱������Ӽ��㣬��ʽΪ(original - min) * scale��(20,110)�ǵ�ͼ�����Ͻ�����
	int x = round((cur_x - min_x) * x_scale) + mapX; // ��������
	int y = round((cur_y - min_y) * y_scale) + mapY;

	return QPair<int, int>(x, y);
}

/*
 * ������ : cbInit
 * In : void
 * Out : void
 * ���� : ��ʼ��labels����
 */
void MainWindow::cbInit()
{
	for (int i = 1; i < ROW; ++i)
	{
		cbArr.push_back(new QCheckBox(this));

		QPair<int, int> qp = mapPointGet(i);
		cbArr.back()->move(qp.first, qp.second); // �ƶ�����
		cbArr.back()->setText(QString::number(i));     // ��������ֵ���������ѡȡʱ��λcomboBox TODO:[�Ż�]���ı�����
		cbArr.back()->hide();
	}
}

/*
 * ������ : chooseStation
 * In : int[��ѡ״̬] , QString[��ѡ������]
 * Out : void
 * ���� : ��ѡ��ѡ�е�ʱ��comboBox���и���
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

	if (state == Qt::Checked)   // ����ѡ��ʱ
	{
		if (chooseCount == 1)
		{
			ui->comboS->setCurrentIndex(name.toInt());  // ��Start��ѡ���ƶ�
		}

		else
			ui->comboE->setCurrentIndex(name.toInt());  // ��End��ѡ���ƶ�
	}

	if (chooseCount > 1)
	{
		chooseCount = 0;                        // ����
		showAllStationConnect(false);   // ��������ѡ��
		ui->rbShowStation->setChecked(false);   // ȡ��ѡ��
	}
}

/*
 * ������ : recharge
 * In : mode[ģʽѡ��]
 * Out : void
 * ���� : ����mode��������
 */
void MainWindow::reCharge(int mode)
{
	if (mode == 1) // ����comboBox
	{
		ui->comboS->setCurrentIndex(0);
		ui->comboE->setCurrentIndex(0);
	}
	else if (mode == 2)   // ���ø�ѡ��
	{
		for (auto& cb : cbArr)
			cb->setChecked(false);
	}
	else if (mode == 3)
	{
		for (auto& lb : labelArr)
			lb->setHidden(true);
	}
	else if (mode == -1)    // ȫ������
	{
		reCharge(1);
		reCharge(2);
		reCharge(3);
		bikeStatus(0);
	}
}

/*
 * ������ : bikeInit
 * In : void
 * Out : void
 * ���� : ����csv��Ϣ����ʼ�����������͵���������
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
 * ������ : bikeChecked
 * In : index[combo������]
 * Out : void
 * ���� : ����������ѯ���Ӧ�ĵ��������Ϳ��õ���
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
			bikeStatus(-2); // ����״̬
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
			bikeStatus(-4); // ����״̬
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
 * ������ : bikeStatus
 * In : mode[ģʽѡ��]
 * Out : void
 * ���� : ����ģʽ�������STATUS״̬����Ϣ
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
 * ����Ҫ������
 * ������ : routePaint
 * In : void
 * Out : void
 * ���� : ·�߻���
 */
void MainWindow::routePaint()
{
	Point4 p4 = pointGet();

	bool checkedStart = false;
	bool checkedTarget = false;

	// �ƶ�p4�ĵ�,ʹ���λ��map��1��
	int startX = p4.x1 - mapX;
	int startY = p4.y1 - mapY;
	int targetX = p4.x2 - mapX;
	int targetY = p4.y2 - mapY;

	if (startX < 0 || startX > imgCol || targetX < 0 || targetX > imgCol || startY < 0 || startY > imgRow || targetY < 0
		|| targetY > imgRow)
		return;

	// ���������·�����·��
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
		if (checkedStart && checkedTarget) // ����Ŀ����λ��·�ϣ�����ѭ��
			break;

		if (!checkedStart)
		{
			QPoint pStartTemp = checkPoint(startY, startX, dx[i], dy[i]);
			if (abs(pStartTemp.x() + pStartTemp.y()) < abs(pStart.x() + pStart.y()))
				pStart = pStartTemp;
		}
		if (!checkedTarget)
		{
			// {0,1}���� {1,0}���� {0,-1}���� {-1,0}����
			QPoint pTargetTemp = checkPoint(targetY, targetX, dx[i], dy[i]);
			if (abs(pTargetTemp.x() + pTargetTemp.y()) < abs(pTarget.x() + pTarget.y()))
				pTarget = pTargetTemp;
		}

	}
	int TempX;
	int TempY;

	// ���
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

	// Ŀ���
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

	QVector<Node*> nodes = map->aStar(startY, startX, targetY, targetX);       // ��map.h�л�ȡ���·�������

	for (const auto& n : nodes)
	{
		mapPointDraw(n->y, n->x);  // mapArr��{y,x}�൱��labelMap��{x,y}
	}
}

/*
 * ������ : pointGet
 * In : void
 * Out : Point4[�����ĸ�����Ľṹ��]
 * ���� : ��������label������
 */
Point4 MainWindow::pointGet()
{
	//TODO:[�Ż�]�����ٻ���һ�����������������ȡָ������������

	// ��ȡ������ͼ�ϵ�Label��ȫ������
	QPoint startPoint = ui->labelS->pos();
	QPoint endPoint = ui->labelE->pos();

	int startX = startPoint.x();
	int startY = startPoint.y();
	int targetX = endPoint.x();
	int targetY = endPoint.y();

	return Point4(startX, startY, targetX, targetY);
}

/*
 * ������ : mapPointDraw
 * In : {x,y} [������Ϣ]
 * Out : void
 * ���� : ����������labelMap���Ƶ�ͼ
 */
void MainWindow::mapPointDraw(int x, int y)
{
	labelArr.push_back(new QLabel(this));
	labelArr.back()->setGeometry(QRect(x + mapX, y + mapY, 2, 2));   // �����{x,y}����������Ƿ�������
	labelArr.back()->setPixmap(QPixmap(QString::fromUtf8(":/img/image/spot.png")));
	labelArr.back()->setScaledContents(true);
	labelArr.back()->show();
}

/*
 * ������ : checkedPoint
 * In : int [�С��С��б仯�����б仯��]
 * Out : QPoint [{�б仯�����б仯��}]
 * ���� : ����{row,col}�������·�ľ���
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
 * ����������ϵͳ��
 * ������ : eventFilter
 * In : QObject QEvent
 * Out : void
 * ���� : ���ƻ���������
 */
bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	// �¼����� : ����+-
	if (obj == ui->gvMap && event->type() == QEvent::KeyPress)
	{
		// ���¼�ת��Ϊ�����¼�
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if(keyEvent->key() == '-')
		{
			ui->gvMap->scale(0.8,0.8);

		}
		else if(keyEvent->key() == '=')
		{
			ui->gvMap->scale(1.2,1.2);
		}
		// ���� true ��ʾ�Ѵ�����¼�
		return true;
	}

	return QObject::eventFilter(obj, event);
}








