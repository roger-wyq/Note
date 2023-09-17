#include <QHBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QTextCodec>
#include <QTextStream>
#include <string>
#include <iostream>
#include <memory>

#include "editor.h"
#include "maddy/parser.h"

Editor::Editor(QWidget * parent = nullptr) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    layout->addWidget(splitter);

    m_markSource = new QTextEdit(splitter);
    m_markPreview = new QTextBrowser(splitter);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);
    connect(m_markSource, &QTextEdit::textChanged, this, &Editor::slot_edit_changed);
}

Editor::~Editor()
{
}

void Editor::setText(QString text)
{
    m_markSource->setText(text);
}

void Editor::save()
{
    if (m_filePath.isEmpty())
    {
        m_filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("MarkDonw File (*.md);;Text File (*.txt);;All File (*.*)"));
    }
    
    m_fileInfo = new QFileInfo(m_filePath);

    if (!m_filePath.isEmpty()) {
        QFile file(m_filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            out.setCodec(codec);
            out << m_markSource->toPlainText();
            file.close();
        }
    }

    emit title_changed(this);
}

void Editor::open()
{
    m_filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
       tr("MarkDonw File (*.md);;Text File (*.txt);;All File (*.*)"));

    m_fileInfo = new QFileInfo(m_filePath);

    if (!m_filePath.isEmpty()) {
        QFile file(m_filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            in.setCodec(codec);
            m_markSource->setText(in.readAll());
            file.close();
        }
    }

    emit title_changed(this);
}

QString Editor::title()
{
    if (m_fileInfo)
        return m_fileInfo->fileName();
    else
        return "noTitle";
}

void Editor::slot_edit_changed()
{
    std::string markSrcTxt = m_markSource->toPlainText().toStdString();
    std::stringstream markdownInput(markSrcTxt);

    // config is optional
    std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();
    // config->isEmphasizedParserEnabled = false; // default true - this flag is deprecated
    // config->isHTMLWrappedInParagraph = false; // default true - this flag is deprecated
    config->enabledParsers &= ~maddy::types::EMPHASIZED_PARSER; // equivalent to !isEmphasizedParserEnabled
    config->enabledParsers |= maddy::types::HTML_PARSER; // equivalent to !isHTMLWrappedInParagraph

    std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>(config);
    std::string htmlOutput = parser->Parse(markdownInput);
    m_markPreview->setHtml(QString::fromStdString(htmlOutput));
}
