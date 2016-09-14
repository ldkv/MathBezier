#pragma once

#include <QtOpenGL>
#include "GL/glu.h"
#include "AlgoMath.h"

using namespace std;

#define POINT_SIZE 10

struct PolyCourbe
{
	vector<QPoint> poly;
	vector<QPoint> polyCC;
	vector<QPoint> courbe;
	vector<QPoint> courbeCC;
	vector<int> r;
	QColor colorPoly = QColor(0, 0, 255);
	QColor colorPolyCC = QColor(0, 255, 0);
	QColor colorCourbe = QColor(255, 0, 0);
	QColor colorCourbeCC = QColor(0, 255, 0);
	bool selected = false;
	bool needUpdate = false;
};

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GLWidget(QWidget *parent);
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	void UpdateData(int i);
	void ClearSelected();
	void drawLines(vector<QPoint> points, QColor col);
	void drawPoints(vector<QPoint> points, QColor col);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	
	pair<int, int> findNearestPoint(QPoint p, vector<PolyCourbe> polyCourbe);
	int pas() { return nbPas; }
	void pas(int p) { nbPas = p; }
	void backgroundColor(QColor col) { bgColor = col; }
	QPoint mouse() { return mousePos; }

	~GLWidget()
	{
		delete[] t_Timer;
	}
	
public slots:
	void timeOutSlot();

signals:
	void polySelected();
	void mouseMoved();

private:
	QPoint mousePos;
	QTimer *t_Timer;
	int nbPas = 10;
	QColor bgColor;
};