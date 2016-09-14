#pragma once

#include <QGLWidget>

using namespace std;

vector<QPoint> calculateCasteljau(vector<QPoint> poly, double a, double b, int nbPas);
QPoint getCasteljauPoint(vector<QPoint> poly, int r, int i, double t);
vector<QPoint> calculateCornerCutting(int pointSelect, vector<QPoint> poly, vector<int> r, int nbPas);
vector<QPoint> generateCourbeCC(int pointSelect, vector<QPoint> corners, double a, double b, vector<int> r, int nbPas);
vector<QPoint> calculatePointsRaccordement(vector<QPoint> poly, int raccord, int r1, int r2);
vector<QPoint> Raccordement(vector<QPoint> poly1, vector<QPoint> poly2, int raccord, int r1, int r2);
QPoint findProportionalPoint(QPoint P1, QPoint P2, int r1, int r2);
QPoint findMediumPoint(QPoint P1, QPoint P2, int r1, int r2);