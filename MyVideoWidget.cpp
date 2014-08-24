#include "MyVideoWidget.hpp"
#include <QPainter>

MyVideoWidget::MyVideoWidget(QWidget *parent) :
	QWidget(parent), m_image(nullptr)
{
}


void MyVideoWidget::setNewImg(QSharedPointer<QImage> img)
{
	if (img->format() != QImage::Format_RGB888 && img->format() != QImage::Format_RGB32)
		return;

	m_mutex.lock();
	m_image = img;
	m_mutex.unlock();

	this->update();
}


void MyVideoWidget::paintEvent(QPaintEvent *e)
{
	if (!m_image)
		return;

	QPainter p(this);
	m_mutex.lock();
	p.drawImage(this->rect(), *m_image, m_image->rect());
	m_mutex.unlock();
}
