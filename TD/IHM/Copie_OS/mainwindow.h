#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBoxWindows_clicked();

    void on_checkBoxOSXLion_clicked();

    void on_checkBoxLinux_clicked();

    void on_radioButtonWindows_clicked();

    void on_radioButtonOSXLion_clicked();

    void on_radioButtonLinux_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButtonWindows_clicked();

    void on_pushButtonOSXLion_clicked();

    void on_pushButtonLinux_clicked();

    void on_lineEditCode_textChanged(const QString &arg1);

    void on_actionC_triggered();

    void on_actionJava_triggered();

    void on_actionCpp_triggered();

    void on_actionPHP_triggered();

    void on_actionJavascript_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
