#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include <string>
#include "text_output_file.h"
#include <QMessageBox>
#include "fourthwindow.h"

ThirdWindow::ThirdWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);
}

ThirdWindow::~ThirdWindow()
{
    delete ui;
}

void ThirdWindow::on_pushButton_clicked()
{
    try{
        string word = ui->word_line->text().toStdString();
        if (word.empty() or word.find_first_of(" .,*&^%$~!@#?()_+-=<>`'\"\\/;:")!=string::npos){
            QString message = "Те, що ви ввели, не можна вважати словом";
            throw message;
        }

        string name;
        text_file accessory_file ("accessory.a");
        accessory_file>>name;
        string new_name = ui->name_line->text().toStdString();
        if (name == new_name){
            QString message = "Не можна створити два файли з однаковим ім'ям";
            throw message;
        }
        string text;
        text_file ifile(name+".txt");


        text_output_file new_file(new_name+".txt", ifile, word);

        accessory_file.endp();
        accessory_file<<new_name<<"\n";
        accessory_file<<word<<"\n";
    }

    catch (const QString& message){
        QMessageBox::warning(this, "Попередження", message);
        return;
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
    FourthWindow next;
    next.setModal(true);
    next.exec();
}
