#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void addFood();
    void calculate();

private:
    QLineEdit *nameEdit;
    QComboBox *genderBox;
    QLineEdit *weightEdit;
    QLineEdit *heightEdit;
    QLineEdit *AgeEdit;

    QLineEdit *foodEdit;
    QLineEdit *proteinEdit;
    QLineEdit *calorieEdit;
    QLineEdit *foodWeightEdit;

    QTableWidget *foodTable;       // Tabel untuk memasukkan makanan
    QTableWidget *resultTable;     // Tabel untuk hasil perhitungan
};

#endif // MAINWINDOW_H
