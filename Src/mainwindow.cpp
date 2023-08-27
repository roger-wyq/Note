#include "mainwindow.h"
#include "./cpp-markdown-100/markdown.h"
#include <QWebengineview>
#include <QHBoxLayout>
#include <QTextEdit>
#include <Qstring>
#include <QSplitter>
#include <QFileDialog>
#include <QTextCodec>
#include <string>
#include <iostream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* layout = new QHBoxLayout(this);
    centralWidget->setLayout(layout);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);
    layout->addWidget(splitter);

    m_markSource = new QTextEdit(splitter);
    m_markPreview = new QTextBrowser(splitter);


    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);    

    connect(m_markSource, &QTextEdit::textChanged, this, &MainWindow::slot_edit_changed);
    initMenuBar();
    
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_new()
{

}

void MainWindow::slot_open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), 
        tr("MarkDonw File (*.md);;Text File (*.txt);;All File (*.*)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            in.setCodec(codec);
            m_markSource->setText(in.readAll());
            file.close();
        }
    }
}

void MainWindow::slot_save()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), 
        tr("MarkDonw File (*.md);;Text File (*.txt);;All File (*.*)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            out.setCodec(codec);
            out << m_markSource->toPlainText();
            file.close();
        }
    }
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
    std::string markSrcTxt = m_markSource->toPlainText().toStdString();
    markdown::Document markDoc;
    markDoc.read(markSrcTxt);
    std::ostringstream os;
    markDoc.write(os);
    m_markPreview->setHtml(QString::fromStdString(os.str()));
}

