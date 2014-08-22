#pragma once

#include <QObject>
#include <QVector>
#include <QVideoFrame>


typedef QVector<quint8> Frame_t;
typedef QSharedPointer<Frame_t> SharedFrame_t;



class VideoEncoderInterface : public QObject
{
	Q_OBJECT
public:
	VideoEncoderInterface(QObject* parent = nullptr)
		:QObject(parent)
	{}

	virtual ~VideoEncoderInterface()
	{}


signals:
	void encoderError(QString errorMessage);

public slots:
	//send to this slot image from camera; if encoder have result after encoding it will be returned
	virtual QVector<SharedFrame_t> encodeFrame(QVide f)=0;

	virtual void setNewFps(size_t fps) = 0;
};
