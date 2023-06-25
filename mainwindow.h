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

#define ROW 28

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE



/* 坐标点 */
struct Point4
{
	int x1;
	int y1;
	int x2;
	int y2;
	Point4(int _x1, int _y1, int _x2, int _y2)
		: x1(_x1), y1(_y1), x2(_x2), y2(_y2){}
};

constexpr double x_scale = 770 / 0.18778; // x轴比例因子
constexpr double y_scale = 490 / 0.11903; // y轴比例因子

static int chooseCount = 0; // 选择的次数

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
	// .cpp每一个函数前都拥有该函数的参数注释信息

	void mapPointInit();                                    // 地图坐标初始化
	void comboInit();                                       // 填充comboBox
	void cbInit();                                         // 站点初始化
	void bikeInit();                                       // 自行车数量初始化
	void bikeStatus(int mode);                                     // 自行车状态
	void mapPointDraw(int x, int y);

	QPoint checkPoint(int row, int col, int m, int n);

	Point4 pointGet();
	QPair<int, int> mapPointGet(int index);                // 获取指定行的地图对应坐标
	QString fileInfoGet(int row, int col);                // 获取csv文件中指定行列的内容
	QStringList csvInfoGet(int indexCol);                  // 返回指定列的指定信息 TODO:[优化]这里可以改为template

	// 槽函数
private slots:
	void routePaint();
	void reCharge(int mode);                                       // 重置
	void showStation(int index, bool sw);
	void showAllStationConnect(bool checked);
	void chooseStation(int state, QString name);
	void bikeChecked(int index, bool checked);

};


#endif //MAINWINDOW_H
