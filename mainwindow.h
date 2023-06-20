//
// Created by AXuan on 2023/6/19.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"

#include <QWidget>
#include <QFile>
#include <QString>
#include <QDir>
#include <QTextStream>
#include <QLabel>
#include <QCheckBox>
#include <QThread>
#include <QDebug>
#include <QTextBrowser>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

constexpr double x_scale = 770 / 0.18778; // x���������
constexpr double y_scale = 490 / 0.11903; // y���������

#define ROW 28

static int chooseCount = 0; // ѡ��Ĵ���

class MainWindow : public QWidget
{
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

private:
	Ui::MainWindow* ui;
	Map* map;
	QVector<QCheckBox*> cbArr;
	QVector<QVector<int>> bikeArr;
private:
	// .cppÿһ������ǰ��ӵ�иú����Ĳ���ע����Ϣ

	void comboInit();                                       // ���comboBox
	void cbInit();                                         // վ���ʼ��
	void bikeInit();                                       // ���г�������ʼ��
	void bikeStatus(int mode);                                     // ���г�״̬


	QPair<int, int> mapPointGet(int index);                // ��ȡָ���еĵ�ͼ��Ӧ����
	QString fileInfoGet(int row , int col);                // ��ȡcsv�ļ���ָ�����е�����
	QStringList csvInfoGet(int indexCol);                  // ����ָ���е�ָ����Ϣ TODO:[�Ż�]������Ը�Ϊtemplate

	// �ۺ���
private slots:
	void reCharge(int mode);                                       // ����
	void showStation(int index, bool sw);
	void showAllStationConnect(bool checked);
	void chooseStation(int state, QString name);
	void bikeChecked(int index, bool checked);

};


#endif //MAINWINDOW_H
