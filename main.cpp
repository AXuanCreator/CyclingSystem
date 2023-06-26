#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	w.show();



	return QApplication::exec();
}




//TODO:[优化]指针缩放
//TODO:[优化]路线生成的逻辑重做，要求选择button后recharge，清空路线，等一系列符合逻辑的改动

//TODO:[新功能]功能性泛用，如地图可以更换，且会自动生成新的对应数组
