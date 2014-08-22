#pragma once

#include <QObject>
#include <QCamera>
#include <QAbstractVideoSurface>
#include <QSharedPointer>
#include <QImage>
#include <VideoEncoderInterface.hpp>


/* This class incapsulate working with QCamera, QAbstractVideoBuffer and encoder;
 * It only start, emit signals with new image from camera, encode this image and save
 * it into QIODevice.
*/
class CameraStream : public QObject
{
	Q_OBJECT
public:
	CameraStream(const QByteArray& cameraName, QObject *parent = 0);
	virtual ~CameraStream();

	//start/stop image processing from camera
	void start();
	void stop();

	//start/stop encoding video;
	//return false at fail(encoding wasn't started yet, output device for video stream wasn't set; ...)
	bool startEncoding();
	bool stopEncoding();
signals:
	void mediaStreamStarted();
	void mediaStreamError(QString errMessage);
	void newImageFromCamera(QSharedPointer<QImage> f);
	void mediaStreamClosed();

public slots:
	//before call startEncoding() you can call it directly from another thread;
	void setOutput(QIODevice* out);


//============================================================================================
protected:
	QCamera* m_camera;
	QAbstractVideoSurface* m_filter;
	VideoEncoderInterface* m_encoder;

protected slots:
	void cameraStateChanged(QCamera::State);
	void cameraStatusChanged(QCamera::Status);
	void cameraError(QCamera::Error);
};
