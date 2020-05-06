#include "blisytv.h"
#include "ui_blisytv.h"
#include <cmath>
#include <iostream>

int targetf;

blisytv::blisytv(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::blisytv)
{
    ui->setupUi(this);


}


void blisytv::on_pushButton_clicked()
{
    QString console;
    long double frameRate;
    console = ui->consoleBox->currentText();
    if (console == "NDS"){
        frameRate = 59.6555;

    }else{
        frameRate = 59.7275;
    }


    QString gameversion;
    gameversion = ui->versionBox->currentText();
    int seedlag;
    if (gameversion == "FireRed 1.0"){
        seedlag = 121;
       } else if (gameversion == "FireRed 1.1"){
        seedlag = 120;
    } else if(gameversion == "LeafGreen"){
        seedlag = 114;

    }

    long double seedlagms;
    seedlagms = 1 / frameRate * 1000 * seedlag;
    long double introtimerms;
    introtimerms = ui->introtimer->value() + seedlagms;
    int introtimerframes;
    introtimerframes = introtimerms / 1000 * frameRate;
    int outoftvf;
    targetf = ui -> targetframe->value();
    outoftvf = ui -> outoftvframe->value();
    int totaltvf = (targetf - outoftvf)/313 + 33;
    long double remain = (targetf - outoftvf) % 313;
    int outsidetv = (remain + outoftvf) - 33;
    int totaloutput;
    totaloutput = totaltvf + outsidetv + introtimerframes;
    ui->output1->setValue(totaloutput);
    ui->output2->setValue(totaltvf);
    ui->outputms1->setValue(1 / frameRate * 1000 * totaloutput);
    ui->outputms2->setValue(1 / frameRate * 1000 * totaltvf);

}


void blisytv::on_pushButton_2_clicked()
{


    QString console;
    long double frameRate;
    console = ui->consoleBox->currentText();
    if (console == "NDS"){
        frameRate = 59.6555;

    }else{
        frameRate = 59.7275;
    }


    int frameHit;
    frameHit = ui->frameHit->value();
    int adjtv;
    adjtv = targetf - frameHit;
    long double adjtv2;
    adjtv2 = adjtv / 313;
    long double adjout;
    adjout = adjtv % 313;
    if( adjout >= 156){
    adjout = 313 - adjout;
    adjtv2++;
    } else if ( adjout > -156){
    }else {
    adjout = -313 - adjout;
    adjtv2--;
    }
    ui->outputadjust2->setValue(adjtv2);
    ui->outputadjust1->setValue(adjout + adjtv2);
    long double totalmsout;
    totalmsout = adjtv2 / frameRate * 1000;
    long double totaltvout;
    totaltvout = adjout / frameRate * 1000;
    ui->outputmsadjust2->setValue(adjtv2 / frameRate * 1000);
    ui->outputmsadjust1->setValue(totalmsout + totaltvout);


}

void blisytv::on_pushButton_3_clicked()
{
    QString flowtimertotal;
    QString flowtimertv;
    QString introtimer;
    int originalflowtimer;
    int originalflowtimertv;
    int flowtimer;
    int flowtimerteli;
    int introtimer1;
    introtimer1 = ui->introtimer->value();
    introtimer = QString::number(introtimer1);
    flowtimerteli = ui->outputmsadjust2->value();
    flowtimer = ui->outputmsadjust1->value();
   originalflowtimer = ui->outputms1->value();
   originalflowtimertv = ui->outputms2->value();
    flowtimertotal = QString::number(originalflowtimer + flowtimer );
    ui->flow1->setText( flowtimertotal + "/" + introtimer);
    flowtimertv = QString::number(originalflowtimertv + flowtimerteli);
    ui->flowtv->setText(flowtimertv);
}

blisytv::~blisytv()
{





    delete ui;
}



