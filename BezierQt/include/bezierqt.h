#pragma once

#include "ui_bezierqt.h"
#include "GLWidget.h"

using namespace std;

class BezierQt : public QMainWindow
{
	Q_OBJECT

public:
	BezierQt(QWidget *parent = 0);
	~BezierQt();
	
private slots:
	void nouveau();
	void ajouter();
	void modeCalcul();
	void changeColor();
	void colorDialog(int id);
	void parametrage();
	void transformation();
	void changerPas();
	void enableMenu();
	void updateStatus();
	void raccordement();
	void quitter();

private:
	Ui::BezierQtClass ui;
	GLWidget *glWidget;
	QButtonGroup *groupButtonColor;
};