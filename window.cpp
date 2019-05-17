#include "window.h"
#include "ui_window.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    setWindowTitle(tr("Parallel Program Cache Performance Profiler"));

    QPushButton *browseButton = new QPushButton(tr("&Browse..."), this);
        connect(browseButton, &QAbstractButton::clicked, this, &Window::browse_exe);

    directoryText = createText(QDir::toNativeSeparators("/home/user/Desktop/hello.exe"));
    directoryText2 = createText(QDir::toNativeSeparators("/home/user/Desktop/cachesetting.txt"));
        QFont f1("Times", 12, QFont::Light);
        f1.setWeight(1);
        directoryText->setFont(f1);
        directoryText2->setFont(f1);

    QPushButton *browseButton2 = new QPushButton(tr("&Browse..."), this);
        connect(browseButton2, &QAbstractButton::clicked, this, &Window::browse_txt);

    traceButton = new QPushButton(tr("&TRACE"), this);
        connect(traceButton, &QAbstractButton::clicked, this, &Window::trace);

    proc = new QProcess();

    QLabel *exeLabel = new QLabel(tr("Enter executable file:"));
        QFont f2( "Ariel", 13, QFont::Thin);
        f2.setItalic(true);
        exeLabel->setFont(f2);

    QLabel *txtLabel = new QLabel(tr("Enter setting file for cache:"));
        txtLabel->setFont(f2);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(exeLabel, 1,0);
    mainLayout->addWidget(directoryText, 2, 0, 1, 3);
    mainLayout->addWidget(browseButton, 2, 3, 1, 1);
    mainLayout->addWidget(txtLabel, 4, 0);
    mainLayout->addWidget(directoryText2, 5, 0, 1, 3);
    mainLayout->addWidget(browseButton2, 5, 3, 1, 1);
    mainLayout->addWidget(traceButton, 6 , 1, 2, 1);
}

Window::~Window()
{
    delete ui;
}

void Window::browse_exe()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Parallel Program Cache Performance Profiler"),
                                                              "/home/bilgen/Desktop", tr("Executable (*.out)")));
        directoryText->setText(directory);
}

void Window::browse_txt()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Parallel Program Cache Performance Profiler"),
                                                              "/home/bilgen/Desktop", tr("Settings (*.txt)")));
        directoryText2->setText(directory);
}

void Window::trace()
{
    hide();
    proc->setWorkingDirectory("/home/bilgen/Desktop");
    proc->start("../../../pin -t obj-intel64/myTool.so -- " + directoryText->text());
    proc->waitForFinished();
    /*proc->setWorkingDirectory("/home/bilgen/Pictures");
    proc->start(" eog -f yose.jpg");*/
    proc->setWorkingDirectory("/home/bilgen/Desktop");
    proc->start("java -jar tez.jar");
    proc->waitForFinished();
    simPage = new SimPage(this);
    simPage->show();
}

QLineEdit *Window::createText(const QString &text)
{
    QLineEdit *comboBox = new QLineEdit;
    comboBox->setReadOnly(true);
    comboBox->insert(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

void Window::animateFindClick()
{
    traceButton->animateClick();
}
QComboBox *Window::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
