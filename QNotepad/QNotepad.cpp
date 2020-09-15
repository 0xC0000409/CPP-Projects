//NOT FOR COMMERCIAL USE if built statically!!!
//Simple notepad application made with Qt 5.15.0
//Requires Qt's MSVC 2019 or statically built Qt's MSCV 2019
//Version: 0.0.2d - [9/15/2020]

#include "QNotepad.h"
#include "stdafx.h"
#include <QApplication>
#include <QMessageBox>
#include <fstream>

int QNotepad::TabCounter = 1;
std::map<QString, QString> QNotepad::files;

//Getting pure filename
QString getFilename(const QString& str) {
	size_t slashPosition = 0;
	for (size_t i = str.count(); i-- > 0;)
		if (str.at(i) == "/") {
			slashPosition = i + 1;
			break;
		}
	QString filename = "";
	for (size_t i = slashPosition; i < str.count(); i++)
		filename += str.at(i);

	return filename;
}

void QNotepad::addNewTab(const QString& filePath = "New ", const QString& content = "") {
	//Create new tab with QTextEdit widget in it
	QWidget* newTab = new QWidget(this);
	QVBoxLayout* layout = new QVBoxLayout(newTab);
	layout->addWidget(new QTextEdit(newTab));
	QString tabName = filePath + QString::number(++TabCounter);

	//Set default filename to "New #"
	if (content.count() != 0)
		tabName = getFilename(filePath);

	//Add new tab in QTabWidget
	ui.tabWidget->addTab(newTab, tabName);
	ui.tabWidget->setCurrentIndex(ui.tabWidget->count() - 1);
	ui.tabWidget->setTabIcon(ui.tabWidget->currentIndex(), QIcon(":/QNotepad/icons/fileIcon.png"));
	QList<QTextEdit*> textEdit = ui.tabWidget->currentWidget()->findChildren<QTextEdit*>(); //Find QTextWidget inside tab
	textEdit[0]->setPlainText(content);
	connect(textEdit[0], SIGNAL(textChanged()), this, SLOT(unsetIcon()));

}

void QNotepad::open() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open text file"), "", tr("Text files(*.txt)"));
	std::ifstream fin; fin.open(filePath.toStdString()); //Opening file for output

	if (fin.is_open()) {
		QString content = "";
		std::string temp = "";
		QString fileRltv = getFilename(filePath);
		while (fin >> temp)
			content.append(QString::fromStdString(temp));
		
		fin.close();

		addNewTab(fileRltv, content);
		files[fileRltv] = filePath; //Adding relative and full file path in std::map for further use
	}
	else if (!fin.is_open() && filePath.count() != 0)
		QMessageBox::critical(this, "Error", "File can't be opened", QMessageBox::Ok);

}

void QNotepad::save() {
	QList<QTextEdit*> textEdit = ui.tabWidget->currentWidget()->findChildren<QTextEdit*>();
	QString content = textEdit[0]->toPlainText();
	QString filename = ui.tabWidget->tabText(ui.tabWidget->currentIndex());

	auto file = files.find(filename);
	if (file != files.end()) { //File already exists
		ui.tabWidget->setTabIcon(ui.tabWidget->currentIndex(), QIcon(":/QNotepad/icons/fileSavedIcon.png"));
		std::ofstream fout(file->second.toStdString(), std::ios::out);
		fout << content.toStdString();
		fout.close();
	}
	else
		ui.actionSave_As->trigger();
}

void QNotepad::saveAs() {
	QList<QTextEdit*> textEdit = ui.tabWidget->currentWidget()->findChildren<QTextEdit*>();
	QString content = textEdit[0]->toPlainText();
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save text file"), "New text file", tr("Text files(*.txt)"));

	std::ofstream fout(filePath.toStdString(), std::ios::out | std::ios::trunc); //Create new or open existing file and discard it's contents
	if (!fout.is_open() && filePath.count() != 0) {
		QMessageBox::critical(this, "Error", "File couldn't be created", QMessageBox::Ok);
		return;
	}

	fout << content.toStdString() << std::endl; //Writing to file
	fout.close();

	if (filePath != "") {
		QString rltvFilename = getFilename(filePath);
		ui.tabWidget->setTabText(ui.tabWidget->currentIndex(), rltvFilename);
		files[rltvFilename] = filePath;
		ui.tabWidget->setTabIcon(ui.tabWidget->currentIndex(), QIcon(":/QNotepad/icons/fileSavedIcon.png"));
	}
}

void QNotepad::closeTab(const int& index) {
	if (index == -1)
		return;
	
	QWidget* tabItem = ui.tabWidget->widget(index);
	disconnect(ui.tabWidget->widget(index)->findChildren<QTextEdit*>()[0], SIGNAL(textChanged()), this, SLOT(unsetIcon()));
	ui.tabWidget->removeTab(index);
	delete tabItem;
}

void QNotepad::unsetIcon() {
	ui.tabWidget->setTabIcon(ui.tabWidget->currentIndex(), QIcon(":/QNotepad/icons/fileIcon.png"));
}

QNotepad::QNotepad(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	setWindowIcon(QIcon(":/QNotepad/icons/QNotepadIcon.png"));
	ui.tabWidget->setTabIcon(ui.tabWidget->currentIndex(), QIcon(":/QNotepad/icons/fileIcon.png"));

	connect(ui.actionNew, &QAction::triggered, [&] { addNewTab(); });
	connect(ui.actionOpen, &QAction::triggered, this, &QNotepad::open);
	connect(ui.actionSave, &QAction::triggered, this, &QNotepad::save);
	connect(ui.actionSave_As, &QAction::triggered, this, &QNotepad::saveAs);

	connect(ui.tabWidget->currentWidget()->findChildren<QTextEdit*>()[0], SIGNAL(textChanged()), this, SLOT(unsetIcon()));
	connect(ui.tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));


	connect(ui.actionCopy, &QAction::triggered, [&] {
		if (ui.tabWidget->currentIndex() == -1)
			return;
		ui.textEdit->copy();
	});

	connect(ui.actionCut, &QAction::triggered, [&] {
		if (ui.tabWidget->currentIndex() == -1)
			return;
		ui.textEdit->cut();
	});

	connect(ui.actionPaste, &QAction::triggered, [&] {
		if (ui.tabWidget->currentIndex() == -1)
			return;
		ui.textEdit->paste();
	});

	connect(ui.actionUndo, &QAction::triggered, [&] {
		if (ui.tabWidget->currentIndex() == -1)
			return;
		
		ui.textEdit->undo();
	});

	connect(ui.actionRedo, &QAction::triggered, [&] {
		if (ui.tabWidget->currentIndex() == -1)
			return;
		
		ui.textEdit->redo();
	});

	connect(ui.actionQuit, &QAction::triggered, [&] {
		QApplication::quit();
	});

	connect(ui.actionAbout, &QAction::triggered, [&] {
		QMessageBox::about(this, "About", "QNotepad application 0.0.1d - [9/15/2020]");
	});

	connect(ui.actionAbout_Qt, &QAction::triggered, [&] {
		QMessageBox::aboutQt(this, "About Qt");
	});
}