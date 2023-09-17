#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebengineview>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QMenuBar>
#include <QTabWidget>

#include "editor.h"


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
    void slot_editor_title_changed(QWidget* widget);

private:
    void initMenuBar();

private:
    QMenuBar* m_meunBar;
    QMenu* m_fileMenu;

    QTabWidget *m_editors;       /* table widget that contain some editor */
    Editor* m_curEditor;           /* current editor */
};
#endif // MAINWINDOW_H
