#include "CameraImageProcessor.hpp"

CameraImageProcessor::CameraImageProcessor(VideoEncoderInterface* enc, QObject* parent)
	: QAbstractVideoSurface(parent), m_encoder(enc), m_outputDevice(nullptr), m_encodingStarted(false),
	  m_fps(0), m_frames(0)
{
	connect(this, &CameraImageProcessor::fpsRecalculated, m_encoder, &VideoEncoderInterface::setNewFps);
	m_timer.start();
}

CameraImageProcessor::~CameraImageProcessor()
{
	m_encodingStarted = false;
	if (m_outputDevice && m_outputDevice->isOpen())
		m_outputDevice->close();
}


bool CameraImageProcessor::present(const QVideoFrame &next_frame)
{
	QVideoFrame localCopy = next_frame;
	if (!localCopy.map(QAbstractVideoBuffer::ReadOnly))
	{
		qDebug() << "Failed to map VideoFrame!";
		return false;
	}

	m_frames++;
	auto msecs = m_timer.elapsed();
	if (msecs >= 1000)
	{
		if (m_fps != m_frames)
		{
			m_fps = m_frames / (msecs/1000);
			if (m_encoding)
				emit fpsRecalculated(m_fps);
		}
		m_timer.restart();
		m_frames=0;
	}

	if (m_outputDevice && m_encodingStarted)
	{
		QVector<SharedFrame_t> encodedFrames = m_encoder->encodeFrame( localCopy );
		for ( auto i = encodedFrames.begin(); i != encodedFrames.end(); i++ )
			m_outputDevice->write( (const char*) ((SharedFrame_t)*i)->data(), ((SharedFrame_t)*i)->size() );

	}

	if (localCopy.pixelFormat() == QVideoFrame::Format_YUV420P)
	{
		Frame_t tmp;
		if (!convert_yuv420p_to_rgb24(localCopy, tmp))
		{
			qDebug() << "Can't draw video frame on widget!";
			localCopy.unmap();
			return false;
		}
		QSharedPointer<QImage> f = QSharedPointer<QImage>::create(localCopy.width(), localCopy.height(), QImage::Format_RGB888);
		std::copy(tmp.cbegin(), tmp.cend(), f->bits());
		emit VideoFrameProbed(f);
	}
	else if ( localCopy.pixelFormat() == QVideoFrame::Format_RGB32 || localCopy.pixelFormat() == QVideoFrame::Format_RGB24 )
	{
		QSharedPointer<QImage> f = QSharedPointer<QImage>::
								   create(localCopy.width(), localCopy.height(),
										  QVideoFrame::imageFormatFromPixelFormat(localCopy.pixelFormat()));
		std::copy( localCopy.bits(), localCopy.bits() + localCopy.bytesPerLine()*localCopy.height(),
				   f->bits() );
		emit VideoFrameProbed(f);
	}
	localCopy.unmap();
	return true;
}



QList<QVideoFrame::PixelFormat> CameraImageProcessor::supportedPixelFormats(QAbstractVideoBuffer::HandleType)const
{
	QList<QVideoFrame::PixelFormat> result;
	result  << QVideoFrame::Format_RGB32 << QVideoFrame::Format_YUV420P << QVideoFrame::Format_RGB24;
	return result;
}

void CameraImageProcessor::setBuffer(QIODevice *buf)
{
	m_outputDevice = buf;
	if (m_outputDevice)
	{
		if (!m_outputDevice->isOpen())
			m_outputDevice->open(QIODevice::ReadWrite);
	}
	else
		m_encodingStarted = false;
}


bool CameraImageProcessor::start_encoding()
{
	if (!m_outputDevice)
		return false;

	emit fpsRecalculated(m_fps);
	m_encodingStarted = true;
	return true;
}

bool CameraImageProcessor::stopEncoding()
{
	if (!m_encodingStarted)
		return false;
	m_encodingStarted = false;
	return true;
}
