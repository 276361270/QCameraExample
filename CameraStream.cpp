#include "CameraStream.hpp"
#include "CameraImageProcessor.hpp"


CameraStream::CameraStream(const QByteArray &cameraName, QObject *parent)
	:QObject(parent)
{
	m_camera = new QCamera(cameraName, this);
	m_encoder = nullptr;
	m_filter = new CameraImageProcessor(m_encoder, this);
	m_camera->setObjectName(QString(cameraName));
	this->setObjectName(QString(cameraName));
	m_camera->setViewfinder( m_filter );

	connect(m_camera, &QCamera::stateChanged, this, &CameraStream::cameraStateChanged);
	connect(m_camera, &QCamera::statusChanged, this, &CameraStream::cameraStatusChanged);
	connect(m_camera, SIGNAL(error(QCamera::Error)), this, SLOT(cameraError(QCamera::Error)));
	connect(m_filter, &CameraImageProcessor::VideoFrameProbed, this, &CameraStream::newImageFromCamera);
}


CameraStream::~CameraStream()
{
	m_filter->stopEncoding();
	m_camera->stop();
	m_filter->stop();
	m_camera->setViewfinder((QAbstractVideoSurface*)nullptr);
}


void CameraStream::setOutput(QIODevice *out)
{
	((CameraImageProcessor*)m_filter)->setBuffer(out);
}

void CameraStream::cameraStateChanged(QCamera::State s)
{
	qDebug() << "camera " << m_camera->objectName() << "\'s state changed to " << s;
	if (s == QCamera::ActiveState)
		emit mediaStreamStarted();
}

void CameraStream::cameraStatusChanged(QCamera::Status s)
{
	qDebug() << "camera " << m_camera->objectName() << "\'s status changed to " << s;
}


void CameraStream::start()
{
	m_camera->start();
}

void CameraStream::stop()
{
	m_camera->stop();
}

bool CameraStream::startEncoding()
{
	return ((CameraImageProcessor*)m_filter)->start_encoding();
}

bool CameraStream::stopEncoding()
{
	return ((CameraImageProcessor*)m_filter)->stopEncoding();
}

void CameraStream::cameraError(QCamera::Error e)
{
	QString err_msg = "%1 error: %2";
	err_msg.arg(objectName()).arg(e);
	qDebug() << err_msg;
	emit mediaStreamError(err_msg);
}
