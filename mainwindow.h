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
#include <QQueue>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QScrollBar>
#define ROW 28

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE


/* ����� */
struct Point4
{
	int x1;
	int y1;
	int x2;
	int y2;
	Point4(int _x1, int _y1, int _x2, int _y2)
		: x1(_x1), y1(_y1), x2(_x2), y2(_y2)
	{
	}
};

constexpr double x_scale = 770 / 0.18778; // x���������
constexpr double y_scale = 490 / 0.11903; // y���������

static int chooseCount = 0; // ѡ��Ĵ���

class MainWindow : public QWidget
{
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

private:
	Ui::MainWindow* ui;

	int mapX;
	int mapY;
	int imgRow;
	int imgCol;


	Map* map;
	QVector<QCheckBox*> cbArr;
	QVector<QLabel*> labelArr;
	QVector<QVector<int>> bikeArr;


private:
	// .cppÿһ������ǰ��ӵ�иú����Ĳ���ע����Ϣ

	void gvMapInit();
	void mapPointInit();                                            // ��ͼ�����ʼ��
	void comboInit();                                               // ���comboBox
	void cbInit();                                                  // վ���ʼ��
	void bikeInit();                                                // ���г�������ʼ��
	void bikeStatus(int mode);                                      // ���г�״̬
	void mapPointDraw(int x, int y);                                // {x,y}���

	bool eventFilter(QObject* obj, QEvent* event);                  // �����¼�����


	QPoint checkPoint(int row, int col, int m, int n);               // ��⵱ǰ����·�ڵ��������
	Point4 pointGet();                                               // ��ȡlabel����
	QPair<int, int> mapPointGet(int index);                          // ��ȡָ���еĵ�ͼ��Ӧ����
	QString fileInfoGet(int row, int col);                           // ��ȡcsv�ļ���ָ�����е�����
	QStringList csvInfoGet(int indexCol);                            // ����ָ���е�ָ����Ϣ

	// �ۺ���
private slots:
	void routePaint();                                                  // ·�߻���
	void reCharge(int mode);                                            // ����
	void showStation(int index, bool sw);                               // վ����ʾ
	void showAllStationConnect(bool checked);                           // վ��ȫ����ʾ
	void chooseStation(int state, QString name);                        // վ��ѡ��
	void bikeChecked(int index, bool checked);                          // ���г����ϵͳ


};

#endif //MAINWINDOW_H
