#include "mainwindow.h"
#include <QWebengineview>
#include <QHBoxLayout>
#include <QTextEdit>
#include <Qstring>
#include <QSplitter>
#include <QFileDialog>
#include <QTextCodec>
#include <string>
#include <iostream>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_editors(new QTabWidget(this))
{       
    m_curEditor = new Editor(this);
    m_editors->addTab(m_curEditor, "noTitle");
    connect(m_curEditor, &Editor::title_changed, this, &MainWindow::slot_editor_title_changed);
    setCentralWidget(m_editors);

    connect(m_editors, &QTabWidget::currentChanged, this, [this](int index) {
        m_curEditor = qobject_cast<Editor*>(m_editors->widget(index));
        });
    initMenuBar();
    
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_new()
{
    Editor* editor = new Editor(this);
    connect(editor, &Editor::title_changed, this, &MainWindow::slot_editor_title_changed);
    m_editors->addTab(editor, editor->title());
    m_curEditor = editor;
    m_editors->setCurrentWidget(editor);
}

void MainWindow::slot_open()
{
    Editor *editor = new Editor(this);
    connect(editor, &Editor::title_changed, this, &MainWindow::slot_editor_title_changed);
    editor->open();
    m_curEditor = editor;
    m_editors->setCurrentWidget(editor);
}

void MainWindow::slot_save()
{
    m_curEditor->save();
}

void MainWindow::slot_editor_title_changed(QWidget* widget)
{
    m_editors->setTabText(m_editors->indexOf(widget), qobject_cast<Editor*>(widget)->title());
}

void MainWindow::initMenuBar()
{
    m_meunBar = new QMenuBar(this);
    setMenuBar(m_meunBar);

    m_fileMenu = new QMenu(tr("File"), this);
    /* add new file item */ 
    QAction* newAction = new QAction(tr("New"), this);
    newAction->setShortcut(QKeySequence::New);
    m_fileMenu->addAction(newAction);
    connect(newAction, &QAction::triggered, this, &MainWindow::slot_new);

    /* add open item */ 
    QAction* openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    m_fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &MainWindow::slot_open);

    /* add save item */
    QAction* saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    m_fileMenu->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &MainWindow::slot_save);

    m_meunBar->addMenu(m_fileMenu);


}

void MainWindow::slot_edit_changed()
{
    
}

