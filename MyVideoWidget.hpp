#pragma once

#include <QWidget>
#include <QSharedPointer>
#include <QMutex>

class MyVideoWidget : public QWidget
{
	Q_OBJECT
public:
	explicit MyVideoWidget(QWidget *parent = 0);

public slots:

	void setNewImg(QSharedPointer<QImage> img);
	void paintEvent(QPaintEvent* e);

private:
	QSharedPointer<QImage> m_image;
	QMutex m_mutex;
};

#endif // MYVIDEOWIDGET_HPP
