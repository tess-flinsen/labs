#include "fourthwindow.h"
#include "ui_fourthwindow.h"
#include "text_input_file.h"
#include <QMessageBox>

FourthWindow::FourthWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FourthWindow)
{
    ui->setupUi(this);
    try{

        text_input_file accessery_file("accessory.a");

        string old_name, new_name, text, word;
        accessery_file>>old_name>>new_name>>word;

        text_input_file old_file(old_name+".txt"),
            new_file(new_name+".txt");

        while(getline(old_file, text))
            ui->source_text->addItem(QString(text.c_str()));

        ui->key_word->addItem(QString(word.c_str()));

        while(getline(new_file, text))
            ui->new_text->addItem(QString(text.c_str()));
    }

    catch(exception& e){
        QMessageBox::warning(this, "Попередження", "Щось пішло не так(");
        delete ui;
        return;
    }

}

FourthWindow::~FourthWindow()
{
    delete ui;
}

