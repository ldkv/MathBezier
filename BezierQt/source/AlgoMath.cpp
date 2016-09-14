#include "AlgoMath.h"

// Génération de la courbe de Bézier par l'algorithme de Casteljau
vector<QPoint> calculateCasteljau(vector<QPoint> poly, double a, double b, int nbPas)
{
	vector<QPoint> bezier;
	if (poly.size() > 0)
	{
		double pas = (b - a) / nbPas;
		for (double t = a; t <= b; t += pas)
			bezier.push_back(getCasteljauPoint(poly, poly.size() - 1, 0, t));
	}
	return bezier;
}

// Fonction intermédiaire pour l'algo de Casteljau
QPoint getCasteljauPoint(vector<QPoint> poly, int r, int i, double t)
{
	if (r == 0) return poly[i];
	QPoint p1 = getCasteljauPoint(poly, r - 1, i, t);
	QPoint p2 = getCasteljauPoint(poly, r - 1, i + 1, t);
	return QPoint((int)((1 - t) * p1.x() + t * p2.x()), (int)((1 - t) * p1.y() + t * p2.y()));
}

// Détermination des nouveau points de contrôle pour la méthode Corner Cutting
vector<QPoint> calculateCornerCutting(int pointSelect, vector<QPoint> poly, vector<int> r, int nbPas)
{
	vector<QPoint> corners;
	int nbPoints = poly.size();
	if (pointSelect <= 0 || pointSelect == nbPoints - 1)
	{
		if (nbPoints >= 5)
		{
			QPoint Q1, Q2, R1, R2;
			
			corners.push_back(poly[0]);
			corners.push_back(poly[1]);
			Q1 = findMediumPoint(poly[1], poly[2], r[0], r[1]);
			Q2 = findMediumPoint(poly[2], poly[3], r[0], r[1] + r[2]);
			corners.push_back(Q1);
			corners.push_back(findMediumPoint(Q1, Q2, r[0], r[1]));
			Q1 = Q2;
			R1 = findMediumPoint(Q1, poly[3], r[1], r[2]);
			for (int i = 3; i < nbPoints - 2; i++)
			{
				Q2 = findMediumPoint(poly[i], poly[i + 1], r[i - 2], r[i - 1] + r[i]);
				R2 = findMediumPoint(Q2, poly[i + 1], r[i - 1], r[i]);
				corners.push_back(Q1);
				corners.push_back(R1);
				corners.push_back(findMediumPoint(R1, Q2, r[0], r[1]));
				Q1 = Q2;
				R1 = R2;
			}
			corners.push_back(Q1);
			corners.push_back(poly[nbPoints - 2]);
			corners.push_back(poly[nbPoints - 1]);
		}
	}
	else if (nbPoints >= 5)
	{
		if (pointSelect == 1)
		{
			QPoint Q1 = findMediumPoint(poly[1], poly[2], r[0], r[1]);
			QPoint Q2 = findMediumPoint(poly[2], poly[3], r[0], r[1] + r[2]);
			QPoint R1, R2;
		}
	}
	return corners;
}

// Engendrement spline cubique C2 par la méthode Corner Cutting
vector<QPoint> generateCourbeCC(int pointSelect, vector<QPoint> corners, double a, double b, vector<int> r, int nbPas)
{
	vector<QPoint> courbes;
	int nbPoints = corners.size();
	for (int i = 0; i < nbPoints - 3; i += 3)
	{
		vector<QPoint> poly4;
		poly4.push_back(corners[i]);
		poly4.push_back(corners[i + 1]);
		poly4.push_back(corners[i + 2]);
		poly4.push_back(corners[i + 3]);

		vector<QPoint> bezier3 = calculateCasteljau(poly4, a, b, nbPas);
		int nbPts = bezier3.size();
		for (int j = 0; j < nbPts; j++)
			courbes.push_back(bezier3[j]);
	}
	return courbes;
}

// Calculation des points de raccordement à partir d'une liste des points de contrôle
vector<QPoint> calculatePointsRaccordement(vector<QPoint> poly, int raccord, int r1, int r2)
{
	vector<QPoint> pts;
	int nbPts = poly.size();
	QPoint tmp, P1, P2;
	switch (raccord)
	{
	case 0:
		if (nbPts > 0)
			pts.push_back(poly[nbPts - 1]);
		break;
	case 1:
		if (nbPts > 1)
		{
			P1 = findProportionalPoint(poly[nbPts - 2], poly[nbPts - 1], r1, r2);
			pts.push_back(poly[nbPts - 1]);
			pts.push_back(P1);
		}
		break;
	case 2:
		if (nbPts > 2)
		{
			tmp = findProportionalPoint(poly[nbPts - 3], poly[nbPts - 2], r1, r2);
			P1 = findProportionalPoint(poly[nbPts - 2], poly[nbPts - 1], r1, r2);
			P2 = findProportionalPoint(tmp, P1, r1, r2);
			pts.push_back(poly[nbPts - 1]);
			pts.push_back(P1);
			pts.push_back(P2);
		}
		break;
	default:
		pts.clear();
		break;
	}
	return pts;
}

// Raccordement de 2 courbes
vector<QPoint> Raccordement(vector<QPoint> poly1, vector<QPoint> poly2, int raccord, int r1, int r2)
{
	QTransform transform;
	QPoint Pn, Pn1, Pn2, Q0, Q1, Q2;
	int nP = poly1.size() - 1;
	int nQ = poly2.size();
	if (raccord >= 0 && nP > 0 && nQ > 0)
	{
		Pn = poly1[nP];
		Q0 = poly2[0];
		transform.translate((Pn - Q0).x(), (Pn - Q0).y());
		for (int j = 0; j < nQ; j++)
			poly2[j] = transform.map(poly2[j]);
	}
	if (raccord >= 1 && nP > 1 && nQ > 1)
	{
		Pn1 = poly1[nP - 1];
		Q0 = poly2[0];
		Q1 = poly2[1];
		QLineF line0 = QLineF(Pn1, Pn);
		QLineF line1 = QLineF(Pn, Q1);
		qreal angle = line1.angleTo(line0);
		
		transform.reset();
		transform.translate(-Q0.x(), -Q0.y());
		for (int j = 0; j < nQ; j++)
			poly2[j] = transform.map(poly2[j]);
		
		transform.reset();
		transform.rotate(-angle);
		for (int j = 1; j < nQ; j++)
			poly2[j] = transform.map(poly2[j]);
		
		transform.reset();
		transform.translate(Q0.x(), Q0.y());
		for (int j = 0; j < nQ; j++)
			poly2[j] = transform.map(poly2[j]);
		
		QPoint q1 = findProportionalPoint(Pn1, Pn, r1, r2);
		Q1 = poly2[1];
		transform.reset();
		transform.translate(q1.x() - Q1.x(), q1.y() - Q1.y());
		for (int j = 1; j < nQ; j++)
			poly2[j] = transform.map(poly2[j]);
	}
	if (raccord == 2 && nP > 2 && nQ > 2)
	{
		Pn2 = poly1[nP - 2];
		Q0 = poly2[0];
		Q1 = poly2[1];
		Q2 = poly2[2];
		QPoint tmp = findProportionalPoint(Pn2, Pn1, r1, r2);
		QPoint q2 = findProportionalPoint(tmp, Q1, r1, r2);
		transform.reset();
		transform.translate(q2.x() - Q2.x(), q2.y() - Q2.y());
		for (int j = 2; j < nQ; j++)
			poly2[j] = transform.map(poly2[j]);
	}
	return poly2;
}

// Determination du point X où: P1P2 * r2 = P2X * r1
QPoint findProportionalPoint(QPoint P1, QPoint P2, int r1, int r2)
{
	return (P2 - P1) * r2 / r1 + P2;
}

// Determination du point X où: P1X * r2 = XP2 * r1
QPoint findMediumPoint(QPoint P1, QPoint P2, int r1, int r2)
{
	return P1 + (P2 - P1) * r1 / (r1+r2);
}