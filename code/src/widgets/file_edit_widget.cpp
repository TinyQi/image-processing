/**
 * file_edit_widget.cpp
 *
 * Toke Høiland-Jørgensen
 * 2012-04-10
 */

#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include "file_edit_widget.h"

FileEditWidget::FileEditWidget(QWidget *parent)
  :QWidget(parent)
{
  init();
}

FileEditWidget::FileEditWidget(const QString & contents, QWidget *parent)
  :QWidget(parent)
{
  setText(contents);
}

void FileEditWidget::init()
{
  setupUi(this);
  connect(lineEdit, SIGNAL(editingFinished()), SLOT(lineeditFinished()));
  connect(lineEdit, SIGNAL(textChanged(const QString&)),
          SLOT(lineeditChanged(const QString&)));
  connect(lineEdit, SIGNAL(textEdited(const QString&)),
          SLOT(lineeditEdited(const QString&)));
  connect(pushButton, SIGNAL(clicked()), this, SLOT(selectFile()));
}

FileEditWidget::~FileEditWidget()
{
}

QString FileEditWidget::text()
{
  return lineEdit->text();
}

void FileEditWidget::setText(const QString &text)
{
  lineEdit->setText(text);
}

void FileEditWidget::lineeditFinished()
{
  emit editingFinished();
}

void FileEditWidget::lineeditChanged(const QString &text)
{
  emit textChanged(text);
}

void FileEditWidget::lineeditEdited(const QString &text)
{
  emit textEdited(text);
}

void FileEditWidget::selectFile()
{
  QString val = lineEdit->text();
  QString open_directory = QDir::currentPath();

  if(!val.isEmpty()) {
    QFileInfo info(val);
    if(info.exists()) {
      open_directory = info.dir().path();
    }
  }
  QString filename = QFileDialog::getOpenFileName(this, tr("Select file"),
                                                  open_directory,
                                                  tr("Text files (*.txt)"));
  if(!filename.isNull()) {
    lineEdit->setText(filename);
    emit editingFinished();
  }
}