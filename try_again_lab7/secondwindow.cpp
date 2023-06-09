#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "thirdwindow.h"
#include <string>
#include <QMessageBox>
#include "text_output_file.h"

using namespace std;

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_pushButton_clicked()
{
    try{
        string name = ui->name_line->text().toStdString();

        text_output_file ofile(name+".txt");

        text_output_file accessory_file("accessory.a");
        accessory_file<<name<<"\n";

        string text = ui->PlainTextEdit->toPlainText().toStdString();
        ofile<<text;
    }
    catch (const invalid_argument& e){
        QMessageBox::warning(this, "Invalid data", e.what());
        return;
    }
    catch (const exception& e){
        QMessageBox::critical(this, "Попередження", "Щось пішло не так");
        return;
    }



    hide();
    ThirdWindow next;
    next.setModal(true);
    next.exec();
}


