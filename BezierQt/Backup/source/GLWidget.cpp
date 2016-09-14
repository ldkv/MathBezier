#include "GLWidget.h"

extern vector<PolyCourbe> polyCourbe;
extern bool polyCreating;
extern bool cornerCutting;
extern int polySelect;
int pointSelect = -1;
QColor lastColor;

// Initialisation de la scène OpenGL
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	int seconde = 1000; // 1 seconde = 1000 ms
	int timerInterval = seconde / 60;
	t_Timer = new QTimer(this);
	connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
	t_Timer->start(timerInterval);
	setMouseTracking(true);
}

// Callback pour les click de la souris
void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		if (polySelect != -1)
		{
			polyCourbe[polySelect].colorPoly = lastColor;
			polySelect = -1;
			pointSelect = -1;
		}
		if (polyCreating)
		{
			int i = polyCourbe.size() - 1;
			polyCourbe[i].poly.push_back(event->pos());
			polyCourbe[i].r.push_back(1);
			polyCourbe[i].needUpdate = true;
		}
		else
		{
			pair<int, int> selected = findNearestPoint(event->pos(), polyCourbe);
			if (selected.first != -1 && selected.second != -1)
			{
				polySelect = selected.first;
				pointSelect = selected.second;
				lastColor = polyCourbe[polySelect].colorPoly;
				polyCourbe[polySelect].colorPoly = QColor(255, 255, 255);
				polyCourbe[polySelect].needUpdate = true;
			}
			emit polySelected();
		}
	}
	else if (event->buttons() & Qt::RightButton)
		polyCreating = false;
}

// Callback pour le mouvement de la souris
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	mousePos = event->pos();
	emit mouseMoved();
	if (event->buttons() & Qt::LeftButton)
	{
		if (polySelect != -1)
		{
			polyCourbe[polySelect].poly[pointSelect] = event->pos();
			polyCourbe[polySelect].needUpdate = true;
		}
	}
}

// Callback pour la relâche de la souris
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && polySelect != -1)
		polyCourbe[polySelect].needUpdate = true;
}

// Recherche du point cliqué par la souris
pair<int,int> GLWidget::findNearestPoint(QPoint p, vector<PolyCourbe> polyCourbe)
{
	int nbPoly = polyCourbe.size();
	for (int i = 0; i < nbPoly; i++)
	{
		int nbPoints = polyCourbe[i].poly.size();
		for (int j = 0; j < nbPoints; j++)
		{
			QPoint d = p - polyCourbe[i].poly[j];
			if (sqrt(pow(d.x(),2) + pow(d.y(),2)) <= POINT_SIZE)
				return make_pair(i, j);
		}
	}
	return make_pair(-1, -1);
}

// Pour garder les FPS à 60
void GLWidget::timeOutSlot()
{
	updateGL();
}

// Initialisation du module OpenGL
void GLWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(bgColor.red() / 255.0f, bgColor.green() / 255.0f, bgColor.blue() / 255.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// Redimensionner de la scène pour adapter à la fenêtre principale
void GLWidget::resizeGL(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
}

// Fonction mettre à jour de la scène OpenGL
void GLWidget::paintGL()
{
	glClearColor(bgColor.red() / 255.0f, bgColor.green() / 255.0f, bgColor.blue() / 255.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int nbPoly = polyCourbe.size();
	for (int i = 0; i < nbPoly; i++)
	{
		if (polyCourbe[i].needUpdate)
			UpdateData(i);

		drawLines(polyCourbe[i].poly, polyCourbe[i].colorPoly);
		drawPoints(polyCourbe[i].poly, polyCourbe[i].colorPoly);
		drawLines(polyCourbe[i].courbe, polyCourbe[i].colorCourbe);
		drawPoints(polyCourbe[i].polyCC, polyCourbe[i].colorPolyCC);
		drawLines(polyCourbe[i].courbeCC, polyCourbe[i].colorCourbeCC);
	}
}

// Mettre à jour des données d'un groupe des points de contrôle
void GLWidget::UpdateData(int i)
{
	polyCourbe[i].courbe.clear();
	polyCourbe[i].polyCC.clear();
	polyCourbe[i].courbeCC.clear();
	if (cornerCutting)
	{
		polyCourbe[i].polyCC = calculateCornerCutting(i == polySelect+1000 ? pointSelect : -1, polyCourbe[i].poly, polyCourbe[i].r, nbPas);
		polyCourbe[i].courbeCC = generateCourbeCC(i == polySelect+1000 ? pointSelect : -1, polyCourbe[i].polyCC, 0, 1, polyCourbe[i].r, nbPas);
	}
	else
		polyCourbe[i].courbe = calculateCasteljau(polyCourbe[i].poly, 0, 1, nbPas);
	polyCourbe[i].needUpdate = false;
}

// Dessiner des côtés à partir des points
void GLWidget::drawLines(vector<QPoint> points, QColor col)
{
	int nbPoints = points.size();
	if (nbPoints < 2)
		return;
	glColor3f(col.red() / 255.0f, col.green() / 255.0f, col.blue() / 255.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nbPoints; i++)
		glVertex2i(points[i].x(), points[i].y());
	glEnd();
}

// Dessiner des points
void GLWidget::drawPoints(vector<QPoint> points, QColor col)
{
	int nbPoints = points.size();
	if (nbPoints == 0)
		return;
	glColor3f(col.red() / 255.0f, col.green() / 255.0f, col.blue() / 255.0f);
	glPointSize(POINT_SIZE);
	glBegin(GL_POINTS);
	for (int i = 0; i < nbPoints; i++)
		glVertex2i(points[i].x(), points[i].y());
	glEnd();
}