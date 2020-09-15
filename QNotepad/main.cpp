#include "QNotepad.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QNotepad w;
	w.show();
	return a.exec();
}
