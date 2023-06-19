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

	//��������

	// [����comboBox�͵�ͼ��label��ʾ]ʹ����Lambda���ʽ��ʹ֮���Դ�������������ͬһ���ۺ������Դ˿���˭�����ƶ�
	connect(ui->comboS, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, true); });
	connect(ui->comboE, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
	{ showStation(index, false); });

	// [����radioButton�͵�ͼ����label��ʾ]
	connect(ui->rbShowStation, &QPushButton::toggled, this, &MainWindow::showAllStationConnect);

	// [����radioButton������]
	connect(ui->pbRecharge,&QPushButton::clicked,this,[this](){reCharge(3);});

	// [���ӵ�ͼĳ��checkBox��comboBox��ʾ]
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
 * ������ : comboGet
 * In : null
 * Out : null
 * ���� : ���comboBox
 */
void MainWindow::comboGet()
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
		ui->tbInfoOut->setText("ERROR,Please Download The Software Again");
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
		ui->tbInfoOut->setText("ERROR");
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
	double min_x = 87.586924;
	double min_y = 41.80091;

	// ��ȡ��ʵ����
	double cur_x = abs(fileInfoGet(index, 6).toDouble());
	double cur_y = abs(fileInfoGet(index, 7).toDouble());

	// ��ȡ�������꣨����ʹ���˱������Ӽ��㣬��ʽΪ(original - min) * scale��(20,110)�ǵ�ͼ�����Ͻ�����
	int x = round((cur_x - min_x) * x_scale) + 20; // ��������
	int y = round((cur_y - min_y) * y_scale) + 110;

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

	if (state == Qt::Checked)   // ����ѡ��ʱ
	{
		if(chooseCount==1)
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
 *
 */
void MainWindow::reCharge(int mode)
{
	if(mode==1) // ����comboBox
	{
		ui->comboS->setCurrentIndex(0);
		ui->comboE->setCurrentIndex(0);
	}
	else if(mode==2)   // ���ø�ѡ��
	{
		for(auto&cb:cbArr)
			cb->setChecked(false);
	}
	else if(mode==3)    // ȫ������
	{
		reCharge(1);
		reCharge(2);
	}
}





