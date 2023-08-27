#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebengineview>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slot_edit_changed();

private:
    QTextEdit* m_markSource;       /* markdown source, input by user */
    QTextBrowser* m_markPreview; /* markdown preview */
};
#endif // MAINWINDOW_H
