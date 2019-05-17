#include "simpage.h"
#include "ui_simpage.h"

#include <QCommonStyle>
#include <QFile>
#include <QTextStream>

SimPage::SimPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimPage)
{
    ui->setupUi(this);
    setWindowTitle(tr("Parallel Program Cache Performance Profiler"));
    lines = new  QStringList();
    var = 0;
    total = 0;
    ui->progressBar->setValue(0);
    QCommonStyle style;
    ui->next->setIcon(style.standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
    read_trace_txt();
    ui->textBrowser->setTextColor(Qt::red);
    ui->textBrowser->setText("Simulation started.");
    ui->textBrowser->setTextColor(Qt::black);
}

SimPage::~SimPage()
{
    delete ui;
}

void SimPage::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pointpen(QColor(random()*1000%255,122,34,255));
    pointpen.setWidth(7);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pointpen);

    if(points.length() != 0){
        for (var = 0; var < points.length(); ++var) {
            pointpen.setColor(QColor(random()*1000%255,random()*1000%255,random()*1000%255,255));
            painter.setPen(pointpen);
            painter.drawPoint(points.at(var).x(), points.at(var).y());
        }
    }
}

void SimPage::read_trace_txt()
{
    QFile file("/home/bilgen/Desktop/Output.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QString line;
        QTextStream in(&file);
        while (!in.atEnd())
        {
            line = in.readLine();
            lines->append(line);
            total++;
        }
        lines->pop_back();
        total--;
    }
}

void SimPage::simulate(int varr, int diff)
{
    int address = 0, x = 0, y = 0;

    while(varr < diff)
    {
        if(lines->at(varr).split(" ").at(0) == "Main"){
            long m_address = lines->at(varr).split(" ").at(1).toLong();
            ui->textBrowser->append("Main -> "+QString::number(m_address));
            m_address = (m_address % 1989);
            x = (m_address%117) * 8 + 77;
            y = ((int)m_address / 117) * 8 + 188;
            points.append(QVector2D(x, y));
        }

        else if (lines->at(varr).split(" ").at(0) == "L2"){
            address = lines->at(varr).split(" ").at(1).toInt();
            ui->textBrowser->append("L2 -> "+QString::number(address));
            x = (address % 117) * 8 + 77;
            y = (address / 117) * 8 + 366;
            points.append(QVector2D(x, y));
        }
        else{
            if( lines->at(varr).split(" ").at(3) == "0"){
                 address = lines->at(varr).split(" ").at(1).toInt();
                 ui->textBrowser->append("Core_1-L1 -> "+QString::number(address));
                 x = (address % 27) * 8 + 77;
                 y = (address / 27) * 8 + 538;
                 points.append(QVector2D(x, y));
            }
            else if( lines->at(varr).split(" ").at(3) == "1"){
                 address = lines->at(varr).split(" ").at(1).toInt();
                 ui->textBrowser->append("Core_2-L1 -> "+QString::number(address));
                 x = (address % 28) * 8 + 307;
                 y = (address / 28) * 8 + 537;
                 points.append(QVector2D(x, y));
            }
            else if( lines->at(varr).split(" ").at(3) == "2"){
                 address = lines->at(varr).split(" ").at(1).toInt();
                 ui->textBrowser->append("Core_3-L1 -> "+QString::number(address));
                 x = (address % 28) * 8 + 547;
                 y = (address / 28) * 8 + 537;
                 points.append(QVector2D(x, y));
            }
            else{
                 address = lines->at(varr).split(" ").at(1).toInt();
                 ui->textBrowser->append("Core_4-L1 -> "+QString::number(address));
                 x = (address % 28) * 8 + 787;
                 y = (address / 28) * 8 + 537;
                 points.append(QVector2D(x, y));
            }
        }
        varr++;
        update();
    }
    ui->progressBar->setValue(diff/total*100);
}

void SimPage::on_next_clicked()
{
    bool flag = true;

    int lineE = ui->lineEdit->text().toInt();

    if(var >= lines->length()){
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("INSTRUCTIONS FINISHED.");
        ui->textBrowser->setTextColor(Qt::black);
        flag = false;
    }

    else if (lineE+var > lines->length()) {
        int diff = qAbs(lines->length() - (lineE+var));
        lineE = lineE - diff;
    }
    if(flag){
        simulate(var, lineE+var);
        var += lineE;
    }
}

void SimPage::on_finish_clicked()
{
    simulate(var, lines->length());
    if(var >= lines->length()){
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("INSTRUCTIONS FINISHED.");
        ui->textBrowser->setTextColor(Qt::black);
    }
}

void SimPage::on_finish_pressed()
{
    ui->textBrowser->setTextColor(Qt::blue);
    ui->textBrowser->append("It may take a while...");
    ui->textBrowser->setTextColor(Qt::black);
}
