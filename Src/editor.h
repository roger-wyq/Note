#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QFileInfo>

class Editor : public QWidget
{
	Q_OBJECT
public:
	Editor(QWidget * parent);
	~Editor();

	void setText(QString text);
	void save();
	void open();

	QString title();

signals:
	void title_changed(QWidget* widget);

public slots:
	void slot_edit_changed();

private:
	QTextEdit* m_markSource;			/* markdown source, input by user */
	QTextBrowser* m_markPreview;		/* markdown preview */

	QFileInfo* m_fileInfo = nullptr;	/* file Info */
	QString m_filePath;					/* file path */

};



#endif // !EDITOR_H
