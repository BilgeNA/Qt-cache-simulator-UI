#ifndef WINDOW_H
#define WINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QWidget>
#include <qcombobox.h>
#include "QDir"
#include "simpage.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
private slots:
      void browse_exe();
      void browse_txt();
      void trace();
      void animateFindClick();
      QComboBox *createComboBox(const QString &text = QString());

private:
    Ui::Window *ui;
    SimPage *simPage;

    QLineEdit *createText(const QString &text = QString());
    void createFilesTable();
    QLineEdit *directoryText;
    QLineEdit *directoryText2;
    QPushButton *traceButton;
    QDir currentDir;
    QProcess *proc;
};

#endif // WINDOW_H
