#include "circleread.h"
#include <iostream>
#include <stdio.h>
#include "src/dl_dxf.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

CIRCLEREAD::CIRCLEREAD()
{
}

void CIRCLEREAD::readcircle(const char *filename)
{
    DL_Dxf *getData=new DL_Dxf();
    if(!getData->in(filename,this))
    {
       // QMessageBox::Informationl(NULL,"error","error");
        delete getData;
        exit(1);
    }

    delete getData;
}

void CIRCLEREAD::addCircle(const DL_CircleData &data)
{
    circlelist.append(data);
    QString filename="count.txt";
    QFile file(filename);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream writecircle(&file);
    writecircle<<"x:"<< data.cx <<"y:" << data.cy  <<"z:"<<data.cz
              <<"radius:"<< data.radius<<"length:"<<circlelist.length() << "\n";
}

void CIRCLEREAD::addText(const DL_TextData &data)
{
    QString filename="text.txt";
    QFile file(filename);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream writetext(&file);
    //QString qstring=QString::fromStdString(data.text);
    QString qstring=data.text.c_str();
    writetext<<"text:"<< qstring<<"\n";
}

void CIRCLEREAD::addDimDiametric(const DL_DimensionData& data, const DL_DimDiametricData& edata)
{
    QString filename="dimdiamertic.txt";
    QFile file(filename);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream writedimdiamertic(&file);

    //代码复制
    QString qstring=data.text.c_str();

    qstring.replace("^ ", "^");
    QRegExp rx("\\\\S([^\\\\]*)\\\\([^;]*);");
    qstring.replace(rx, "\\S\\1^\\2;");
    QString uTol, lTol;
    QRegExp rxAlignment("^\\\\A(\\d+);");
    qstring.replace(rxAlignment, "");
    QRegExp rxTolerance("\\\\S([^^]*)\\^([^;]*);$");
    if (rxTolerance.indexIn(qstring)!=-1) {
        uTol = rxTolerance.cap(1);
        lTol = rxTolerance.cap(2);
    }
    qstring.replace(rxTolerance, "");

    // auto measurement is default (empty string):
    if (qstring=="<>") {
        qstring = "";
    }
    //代码复制

    writedimdiamertic<<"text:"<< qstring<<"\n";
}

void CIRCLEREAD::addPolyline(const DL_PolylineData & data)
{
      polylinelist.append(data);
      QString filename="polyline.txt";
      QFile file(filename);
      file.open(QIODevice::WriteOnly|QIODevice::Append);
      QTextStream writepolyline(&file);
      writepolyline<<"number:"<<data.number<<"flags:"<<data.flags
                  <<"m:"<<data.m<<"n:"<<data.n<<"\n";
}

void CIRCLEREAD::addVertex(const DL_VertexData &data)
{
    vertexlist.append(data);
}

