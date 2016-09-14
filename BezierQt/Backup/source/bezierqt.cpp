#include "bezierqt.h"

vector<PolyCourbe> polyCourbe;
bool polyCreating = false;
bool cornerCutting = false;
int raccord = -1;
int polySelect = -1;
extern QColor lastColor;

// Initialisation de la fenêtre
BezierQt::BezierQt(QWidget *parent)
	: QMainWindow(parent), ui(Ui::BezierQtClass())
{
	ui.setupUi(this);
	glWidget = new GLWidget(this);
	ui.mainLayout->addWidget(glWidget);
	ui.menuOptions->setEnabled(false);

	connect(ui.actionNouveau, SIGNAL(triggered()), this, SLOT(nouveau()));
	connect(ui.newPointControlGroup, SIGNAL(triggered()), this, SLOT(ajouter()));
	connect(ui.actionCornerCutting, SIGNAL(triggered()), this, SLOT(modeCalcul()));
	connect(ui.actionChanger_la_couleur, SIGNAL(triggered()), this, SLOT(changeColor()));
	connect(ui.actionParametrage, SIGNAL(triggered()), this, SLOT(parametrage()));
	connect(ui.actionTransformation, SIGNAL(triggered()), this, SLOT(transformation()));
	connect(ui.actionRaccordement, SIGNAL(triggered()), this, SLOT(raccordement()));
	connect(ui.actionChanger_le_pas, SIGNAL(triggered()), this, SLOT(changerPas()));
	connect(ui.actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));
	connect(glWidget, SIGNAL(polySelected()), this, SLOT(enableMenu()));
	connect(glWidget, SIGNAL(mouseMoved()), this, SLOT(updateStatus()));
}

// Effacer la scène et toutes les données
void BezierQt::nouveau()
{
	int nbPoly = polyCourbe.size();
	for (int i = 0; i < nbPoly; i++)
	{
		polyCourbe[i].poly.clear();
		polyCourbe[i].polyCC.clear();
		polyCourbe[i].courbe.clear();
		polyCourbe[i].courbeCC.clear();
		polyCourbe[i].r.clear();
	}
	polyCourbe.clear();
	polyCreating = false;
}

// Ajouter un nouveau groupe de contrôle
void BezierQt::ajouter()
{
	polyCreating = true;
	PolyCourbe newPoly;
	if (raccord != -1)
	{
		newPoly.poly = calculatePointsRaccordement(polyCourbe[polySelect].poly, raccord, 1, 1);
		for (int i = 0; i < raccord; i++)
			newPoly.r.push_back(1);
		raccord = -1;
	}
	newPoly.needUpdate = true;
	polyCourbe.push_back(newPoly);
}

// Boîte de saisie pour le nombre de pas
void BezierQt::changerPas()
{
	QDialog *pasDialog = new QDialog(this);
	pasDialog->setWindowTitle("Choisir un nombre de pas");
	QFormLayout *formInput = new QFormLayout;
	QLineEdit *pas = new QLineEdit;
	pas->setText(QString::number(glWidget->pas()));
	QIntValidator *validNb = new QIntValidator(1, 1000, pas);
	pas->setValidator(validNb);
	formInput->addRow("Nombre de pas", pas);

	QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal);
	buttons->setCenterButtons(true);
	connect(buttons, SIGNAL(accepted()), pasDialog, SLOT(accept()));
	connect(buttons, SIGNAL(rejected()), pasDialog, SLOT(reject()));

	// Ajouter le widget à la fenêtre
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QGroupBox *inputBox = new QGroupBox("");
	inputBox->setLayout(formInput);
	mainLayout->addWidget(inputBox, Qt::AlignCenter);
	mainLayout->addWidget(buttons, Qt::AlignCenter);
	pasDialog->setLayout(mainLayout);
	pasDialog->show();

	if (pasDialog->exec() == QDialog::Accepted)
	{
		if (glWidget->pas() != pas->text().toInt())
		{
			glWidget->pas(pas->text().toInt());
			int nbPoly = polyCourbe.size();
			for (int i = 0; i < nbPoly; i++)
				polyCourbe[i].needUpdate = true;
		}
	}
}

// Changer mode de génération de courbe (entre Casteljau et corner cutting)
void BezierQt::modeCalcul()
{
	cornerCutting = !cornerCutting;
	int nbPoly = polyCourbe.size();
	for (int i = 0; i < nbPoly; i++)
		polyCourbe[i].needUpdate = true;
}

// Changer les couleurs des courbes
void BezierQt::changeColor()
{
	if (polySelect != -1)
	{
		QDialog *colDialog = new QDialog(this);
		colDialog->setWindowTitle("Changer les couleurs");
		QPushButton *color[5];
		color[0] = new QPushButton("Polygone de controle");
		color[1] = new QPushButton("Points de Corner Cutting");
		color[2] = new QPushButton("Courbe de Bezier");
		color[3] = new QPushButton("Courbe de Corner Cutting");
		color[4] = new QPushButton("Couleur de fond");

		QVBoxLayout *vbox = new QVBoxLayout;
		groupButtonColor = new QButtonGroup(colDialog);
		for (int i = 0; i < 5; i++)
		{
			vbox->addWidget(color[i]);
			groupButtonColor->addButton(color[i]);
			color[i]->setCheckable(true);
		}
		groupButtonColor->setExclusive(true);
		connect(groupButtonColor, SIGNAL(buttonClicked(int)), this, SLOT(colorDialog(int)));
		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal);
		buttons->setCenterButtons(true);
		connect(buttons, SIGNAL(accepted()), colDialog, SLOT(accept()));
		vbox->addStretch(1);
		QFrame* line = new QFrame();
		line->setFrameShape(QFrame::HLine);
		line->setFrameShadow(QFrame::Sunken);
		vbox->addWidget(line);
		vbox->addWidget(buttons);
		colDialog->setLayout(vbox);
		colDialog->show();
	}
}

// Boîte de choisir de la couleur
void BezierQt::colorDialog(int id)
{
	QColor color = QColorDialog::getColor(Qt::blue, this);
	if (color.isValid() && color != Qt::white && color != Qt::black)
	{
		id = -id - 2;
		switch (id)
		{
		case 0:
			lastColor = color;
			break;
		case 1:
			polyCourbe[polySelect].colorPolyCC = color;
			break;
		case 2:
			polyCourbe[polySelect].colorCourbe = color;
			break;
		case 3:
			polyCourbe[polySelect].colorCourbeCC = color;
			break;
		case 4:
			glWidget->backgroundColor(color);
			break;
		default:
			break;
		}
	}
}

// Boîte de saisie pour l'espace paramétrage
void BezierQt::parametrage()
{
	if (polySelect != -1)
	{
		QDialog *paraDialog = new QDialog(this);
		paraDialog->setWindowTitle("Configurer l'espace parametrage");
		QGridLayout *gridSaisie = new QGridLayout;
		gridSaisie->addWidget(new QLabel("Node #"), 0, 0, Qt::AlignCenter);
		gridSaisie->addWidget(new QLabel("Valeur r"), 0, 1, Qt::AlignCenter);

		int nbPara = polyCourbe[polySelect].r.size();
		QLineEdit **r = new QLineEdit*[nbPara];
		QIntValidator *validNb = new QIntValidator(1, 1000, paraDialog);
		for (int i = 0; i < nbPara; i++)
		{
			r[i] = new QLineEdit(QString::number(polyCourbe[polySelect].r[i]));
			r[i]->setValidator(validNb);
			gridSaisie->addWidget(new QLabel(QString::number(i)), i + 1, 0, Qt::AlignCenter);
			gridSaisie->addWidget(r[i], i + 1, 1, Qt::AlignCenter);
		}

		// Ajouter un scrollbar
		QWidget *zoneSaisie = new QWidget;
		zoneSaisie->setLayout(gridSaisie);
		QScrollArea *scrollGrid = new QScrollArea;
		scrollGrid->setWidget(zoneSaisie);

		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal);
		buttons->setCenterButtons(true);
		connect(buttons, SIGNAL(accepted()), paraDialog, SLOT(accept()));
		connect(buttons, SIGNAL(rejected()), paraDialog, SLOT(reject()));

		// Ajouter le widget à la fenêtre
		QVBoxLayout *mainLayout = new QVBoxLayout;
		mainLayout->addWidget(scrollGrid, Qt::AlignCenter);
		mainLayout->addWidget(buttons, Qt::AlignCenter);
		paraDialog->setLayout(mainLayout);
		paraDialog->show();

		if (paraDialog->exec() == QDialog::Accepted)
		{
			for (int i = 0; i < nbPara; i++)
				polyCourbe[polySelect].r[i] = r[i]->text().toInt();
			polyCourbe[polySelect].needUpdate = true;
		}
	}
}

// Boîte de saisie pour le raccordement
void BezierQt::raccordement()
{
	if (polySelect != -1)
	{
		QDialog *raccordDialog = new QDialog(this);
		raccordDialog->setWindowTitle("Choisir un type de raccordement");
		QFormLayout *formInput = new QFormLayout;
		QLineEdit *r = new QLineEdit;
		r->setText("0");
		QIntValidator *validNb = new QIntValidator(0, 2, r);
		r->setValidator(validNb);
		formInput->addRow("Raccordement C (0-2)", r);

		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal);
		buttons->setCenterButtons(true);
		connect(buttons, SIGNAL(accepted()), raccordDialog, SLOT(accept()));
		connect(buttons, SIGNAL(rejected()), raccordDialog, SLOT(reject()));

		// Ajouter le widget à la fenêtre
		QVBoxLayout *mainLayout = new QVBoxLayout;
		QGroupBox *inputBox = new QGroupBox("");
		inputBox->setLayout(formInput);
		mainLayout->addWidget(inputBox, Qt::AlignCenter);
		mainLayout->addWidget(buttons, Qt::AlignCenter);
		raccordDialog->setLayout(mainLayout);
		raccordDialog->show();

		if (raccordDialog->exec() == QDialog::Accepted)
		{
			raccord = r->text().toInt();
			ajouter();
		}
	}
}

// Boîte de saisie pour les transformation
void BezierQt::transformation()
{
	if (polySelect != -1)
	{
		QDialog *transformation = new QDialog(this);
		transformation->setWindowTitle("Transformation");
		QFormLayout *formInput = new QFormLayout;
		QLineEdit *rotation = new QLineEdit;
		QLineEdit *scaleX = new QLineEdit;
		QLineEdit *scaleY = new QLineEdit;
		QLineEdit *transX = new QLineEdit;
		QLineEdit *transY = new QLineEdit;
		QLineEdit *shearX = new QLineEdit;
		QLineEdit *shearY = new QLineEdit;

		rotation->setText("0");
		scaleX->setText("1");
		scaleY->setText("1");
		transX->setText("0");
		transY->setText("0");
		shearX->setText("0");
		shearY->setText("0");

		formInput->addRow("Angle de rotation", rotation);
		formInput->addRow("Cisaillement suivant X", shearX);
		formInput->addRow("Cisaillement suivant Y", shearY);
		formInput->addRow("Scaling suivant X", scaleX);
		formInput->addRow("Scaling suivant Y", scaleY);
		formInput->addRow("Translation suivant X", transX);
		formInput->addRow("Translation suivant Y", transY);

		QIntValidator *validNb = new QIntValidator(0, 1, transformation);

		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal);
		buttons->setCenterButtons(true);
		connect(buttons, SIGNAL(accepted()), transformation, SLOT(accept()));
		connect(buttons, SIGNAL(rejected()), transformation, SLOT(reject()));

		// Ajouter le widget à la fenêtre
		QVBoxLayout *mainLayout = new QVBoxLayout;
		QGroupBox *inputBox = new QGroupBox("Saisie des parametres");
		inputBox->setLayout(formInput);
		mainLayout->addWidget(inputBox, Qt::AlignCenter);
		mainLayout->addWidget(buttons, Qt::AlignCenter);
		transformation->setLayout(mainLayout);
		transformation->show();

		if (transformation->exec() == QDialog::Accepted)
		{
			QTransform transform;
			transform.rotate(rotation->text().toFloat());
			transform.scale(scaleX->text().toFloat(), scaleY->text().toFloat());
			transform.shear(shearY->text().toFloat(), shearX->text().toFloat());
			transform.translate(transX->text().toFloat(), transY->text().toFloat());
			int nbPoints = polyCourbe[polySelect].poly.size();
			for (int j = 0; j < nbPoints; j++)
				polyCourbe[polySelect].poly[j] = transform.map(polyCourbe[polySelect].poly[j]);
			polyCourbe[polySelect].needUpdate = true;
		}
	}
}

// Activer le menu local quand un groupe de points de contrôle est choisie
void BezierQt::enableMenu()
{
	if (polySelect != -1)
		ui.menuOptions->setEnabled(true);
	else
		ui.menuOptions->setEnabled(false);
}

void BezierQt::updateStatus()
{
	ui.statusBar->showMessage((QString("(x,y) coordinates: (%1,%2)").arg(glWidget->mouse().x()).arg(glWidget->mouse().y())));
}

void BezierQt::quitter()
{
	qApp->quit();
}

BezierQt::~BezierQt()
{
	delete[] glWidget;
}