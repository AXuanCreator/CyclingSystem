//
// Created by AXuan on 2023/6/19.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QDir>
#include <QTextStream>
#include <QLabel>
#include <QCheckBox>
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

constexpr double x_scale = 770 / 0.18778; // x轴比例因子
constexpr double y_scale = 490 / 0.11903; // y轴比例因子

#define ROW 28

static int chooseCount = 0; // 选择的次数
class MainWindow : public QWidget
{
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

private:
	Ui::MainWindow* ui;
	QVector<QCheckBox*> cbArr;
private:
	// .cpp每一个函数前都拥有该函数的参数注释信息

	void comboGet();                                       // 填充comboBox
	void cbInit();                                         // 站点初始化



	QPair<int, int> mapPointGet(int index);                // 获取指定行的地图对应坐标
	QString fileInfoGet(int row , int col);                // 获取csv文件中指定行列的内容
	QStringList csvInfoGet(int indexCol);                  // 返回指定列的指定信息 TODO:[优化]这里可以改为template

private slots:
	void reCharge(int mode);                                       // 重置
	void showStation(int index, bool sw);
	void showAllStationConnect(bool checked);
	void chooseStation(int state, QString name);

};


#endif //MAINWINDOW_H
