#include "mainwindow.h"
#include "./cpp-markdown-100/markdown.h"
#include <QWebengineview>
#include <QHBoxLayout>
#include <QTextEdit>
#include <Qstring>
#include <QSplitter>
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
    
}

MainWindow::~MainWindow()
{

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

