#include "MainWindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Main widget
    QWidget *centralWidget = new QWidget(this);

    // Informasi Personal Group
    QGroupBox *personalInfoGroup = new QGroupBox("Informasi Personal");
    QGridLayout *personalLayout = new QGridLayout;

    nameEdit = new QLineEdit;
    genderBox = new QComboBox;
    weightEdit = new QLineEdit;
    heightEdit = new QLineEdit;
    AgeEdit = new QLineEdit;

    genderBox->addItems({"Pria", "Wanita"});

    personalLayout->addWidget(new QLabel("Nama:"), 0, 0);
    personalLayout->addWidget(nameEdit, 0, 1);
    personalLayout->addWidget(new QLabel("Jenis Kelamin:"), 1, 0);
    personalLayout->addWidget(genderBox, 1, 1);
    personalLayout->addWidget(new QLabel("Usia :"), 2, 0);
    personalLayout->addWidget(AgeEdit, 2, 1);
    personalLayout->addWidget(new QLabel("Berat Badan (kg):"), 3, 0);
    personalLayout->addWidget(weightEdit, 3, 1);
    personalLayout->addWidget(new QLabel("Tinggi Badan (cm):"), 4, 0);
    personalLayout->addWidget(heightEdit, 4, 1);

    personalInfoGroup->setLayout(personalLayout);

    // Tambah Makanan Group
    QGroupBox *foodGroup = new QGroupBox("Tambah Makanan");
    QGridLayout *foodLayout = new QGridLayout;

    foodEdit = new QLineEdit;
    proteinEdit = new QLineEdit;
    calorieEdit = new QLineEdit;
    foodWeightEdit = new QLineEdit;
    QPushButton *addFoodButton = new QPushButton("Masukan Makanan");

    foodLayout->addWidget(new QLabel("Nama Makanan:"), 0, 0);
    foodLayout->addWidget(foodEdit, 0, 1);
    foodLayout->addWidget(new QLabel("Protein/100g (gram):"), 1, 0);
    foodLayout->addWidget(proteinEdit, 1, 1);
    foodLayout->addWidget(new QLabel("Kalori/100g:"), 2, 0);
    foodLayout->addWidget(calorieEdit, 2, 1);
    foodLayout->addWidget(new QLabel("Berat Makanan (gram):"), 3, 0);
    foodLayout->addWidget(foodWeightEdit, 3, 1);
    foodLayout->addWidget(addFoodButton, 4, 0, 1, 2);

    foodGroup->setLayout(foodLayout);

    // Tabel untuk daftar makanan
    QLabel *foodTableLabel = new QLabel("<b>Daftar Makanan</b>");
    foodTable = new QTableWidget(0, 4);
    foodTable->setHorizontalHeaderLabels({"Nama", "Protein (g)", "Kalori", "Berat (g)"});
    foodTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Tabel untuk hasil perhitungan
    QLabel *resultTableLabel = new QLabel("<b>Hasil Perhitungan</b>");
    resultTable = new QTableWidget(1, 9);
    resultTable->setHorizontalHeaderLabels({
                                            "Nama", "Kelamin", "BB (kg)", "TB (cm)", "Kalori Total",
                                            "Protein Total", "BMI", "BMR", "Saran Kalori"});
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Hitung Button
    QPushButton *calculateButton = new QPushButton("Hitung");

    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(personalInfoGroup);
    mainLayout->addWidget(foodTableLabel);
    mainLayout->addWidget(foodTable);
    mainLayout->addWidget(foodGroup);
    mainLayout->addWidget(resultTableLabel);
    mainLayout->addWidget(resultTable);
    mainLayout->addWidget(calculateButton);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect buttons to functions
    connect(addFoodButton, &QPushButton::clicked, this, &MainWindow::addFood);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
}

void MainWindow::addFood() {
    QString foodName = foodEdit->text();
    double protein = proteinEdit->text().toDouble();
    double calories = calorieEdit->text().toDouble();
    double weight = foodWeightEdit->text().toDouble();

    if (foodName.isEmpty() || protein <= 0 || calories <= 0 || weight <= 0) {
        QMessageBox::warning(this, "Error", "Isi semua data makanan dengan benar!");
        return;
    }

    int rowCount = foodTable->rowCount();
    foodTable->insertRow(rowCount);

    foodTable->setItem(rowCount, 0, new QTableWidgetItem(foodName));
    foodTable->setItem(rowCount, 1, new QTableWidgetItem(QString::number(protein)));
    foodTable->setItem(rowCount, 2, new QTableWidgetItem(QString::number(calories)));
    foodTable->setItem(rowCount, 3, new QTableWidgetItem(QString::number(weight)));

    foodEdit->clear();
    proteinEdit->clear();
    calorieEdit->clear();
    foodWeightEdit->clear();
}

void MainWindow::calculate() {
    double totalCalories = 0;
    double totalProtein = 0;

    // Iterate through each food item
    for (int i = 0; i < foodTable->rowCount(); ++i) {
        double calories = foodTable->item(i, 2)->text().toDouble();
        double weight = foodTable->item(i, 3)->text().toDouble();
        double protein = foodTable->item(i, 1)->text().toDouble();

        // Calculate calories and protein for the given weight (using proportion)
        totalCalories += (calories / 100) * weight;
        totalProtein += (protein / 100) * weight;
    }

    double weight = weightEdit->text().toDouble(); // Weight in kg
    double height = heightEdit->text().toDouble(); // Height in cm
    int age = AgeEdit->text().toInt(); // Age from a new input field
    QString gender = genderBox->currentText();

    // Calculate BMI (Body Mass Index)
    double bmi = weight / ((height / 100) * (height / 100));

    // Calculate BMR using the provided formulas
    double bmr = 0.0;
    if (gender == "Pria") {
        bmr = 66.5 + (13.7 * weight) + (5 * height) - (6.8 * age);
    } else {
        bmr = 655 + (9.6 * weight) + (1.8 * height) - (4.7 * age);
    }

    // Set results in the resultTable
    resultTable->setItem(0, 0, new QTableWidgetItem(nameEdit->text()));
    resultTable->setItem(0, 1, new QTableWidgetItem(gender));
    resultTable->setItem(0, 2, new QTableWidgetItem(QString::number(weight)));
    resultTable->setItem(0, 3, new QTableWidgetItem(QString::number(height)));
    resultTable->setItem(0, 4, new QTableWidgetItem(QString::number(totalCalories)));
    resultTable->setItem(0, 5, new QTableWidgetItem(QString::number(totalProtein)));
    resultTable->setItem(0, 6, new QTableWidgetItem(QString::number(bmi)));
    resultTable->setItem(0, 7, new QTableWidgetItem(QString::number(bmr)));
    resultTable->setItem(0, 8, new QTableWidgetItem(QString::number(bmr * 1.2))); // Assuming Sedentary activity level
}
