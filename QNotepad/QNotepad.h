#pragma once

#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include "ui_QNotepad.h"
#include <map>

class QNotepad : public QMainWindow {
	Q_OBJECT
private:
	static int TabCounter;
	static std::map<QString, QString> files;
public:
	QNotepad(QWidget *parent = Q_NULLPTR);
private:
	Ui::QNotepadClass ui;
	void addNewTab(const QString& filename, const QString& content);
	void open();
	void save();
	void saveAs();
private slots:
	void closeTab(const int& index);
	void unsetIcon();
};