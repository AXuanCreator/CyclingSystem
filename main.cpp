#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	w.show();



	return QApplication::exec();
}



//TODO:[BUG]�ж�����ĵ�·����Ҫ����������������ʵ��

//TODO:[�Ż�]·�����ɵ��߼�������Ҫ��ѡ��button��recharge�����·�ߣ���һϵ�з����߼��ĸĶ�

//TODO:[�¹���]��ͼ�Ŵ�
//TODO:[�¹���]�����Է��ã����ͼ���Ը������һ��Զ������µĶ�Ӧ����
