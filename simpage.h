#ifndef SIMPAGE_H
#define SIMPAGE_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QWidget>

namespace Ui {
class SimPage;
}

class SimPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimPage(QWidget *parent = nullptr);
    ~SimPage();

private slots:

    void read_trace_txt();
    void on_next_clicked();
    void simulate(int var, int diff);

    void on_finish_clicked();
    void on_finish_pressed();

private:
    struct pointodesu {
    int r;
    int g;
    int b;
    int x;
    int y;
    };
    Ui::SimPage *ui;
    QStringList *lines;
    QList<pointodesu> points;
    int var;
    double total;
    int r;
    int g;
    int b;
    QList<QString> results;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // SIMPAGE_H
