#pragma once

#include <QAbstractVideoSurface>
#include "VideoEncoderInterface.hpp"
#include <QTime>

class CameraImageProcessor : public QAbstractVideoSurface
{
	Q_OBJECT
public:
	CameraImageProcessor( VideoEncoderInterface* enc, QObject* parent = nullptr );
	//encoder and output device will not be deleted at destroying CameraImageProcessor
	virtual ~CameraImageProcessor();

	virtual bool present(const QVideoFrame& next_frame);

	virtual QList<QVideoFrame::PixelFormat>
		supportedPixelFormats(QAbstractVideoBuffer::HandleType h) const;

	//set device which will contain encoded stream
	void setBuffer(QIODevice* buf);

signals:
	void VideoFrameProbed(QSharedPointer<QImage> f);

	void fpsRecalculated(size_t fps);

public slots:
	//return false, if you not set output buffer yet;
	bool start_encoding();

	//stop encoding process; return false, if encoding not started
	bool stopEncoding();

protected:
	VideoEncoderInterface* m_encoder;
	QIODevice* m_outputDevice;
	bool m_encodingStarted;

	//calculating count of frames per second
	size_t  m_fps;
	QTime m_timer;
	size_t m_frames;
};
