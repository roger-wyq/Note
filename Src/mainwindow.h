#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebengineview>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QMenuBar>

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
    void slot_new();
    void slot_open();
    void slot_save();

private:
    void initMenuBar();

private:
    QMenuBar* m_meunBar;
    QMenu* m_fileMenu;

    QTextEdit* m_markSource;       /* markdown source, input by user */
    QTextBrowser* m_markPreview;   /* markdown preview */
};
#endif // MAINWINDOW_H
