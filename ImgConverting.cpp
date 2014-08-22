#include "ImgConverting.hpp"
#include <QDebug>

bool convert_yuv420p_to_rgb32( const QVideoFrame& src, Frame_t& dst )
{

	dst.clear();

	SwsContext* ctx = sws_getContext( src.width(), src.height(), PIX_FMT_YUV420P,
		src.width(), src.height(), PIX_FMT_RGB32, SWS_FAST_BILINEAR, 0,0,0 );

	if (!ctx)
	{
		qDebug() << "sws context initialisation fail";
		return false;
	}

	AVPicture tmp_pic;

	//copy frame from QVideoFrame into tmp_pic
	int bytes_copied = avpicture_fill(&tmp_pic, const_cast<uint8_t*>(src.bits()),
		PIX_FMT_YUV420P, src.width(), src.height());

	if (bytes_copied < 0)
	{
		qDebug() << "H264Encoder: error calling avpicture_fill(...)!";
		sws_freeContext(ctx);
		return false;
	}
	AVPicture tmp_out_pic;
	if (avpicture_alloc(&tmp_out_pic, PIX_FMT_RGB32, src.width(), src.height()) != 0)
	{
		qDebug() << "avpicture_alloc() fail!";
		sws_freeContext(ctx);
		return false;
	}

	//convert img into m_out_format and save in m_in_pic
	int scaled_img_height = sws_scale(ctx, tmp_pic.data, tmp_pic.linesize, 0, src.height(),
		tmp_out_pic.data, tmp_out_pic.linesize);

	if ( scaled_img_height < 0 || scaled_img_height != src.height() )
	{
		qDebug() << "Scaling failed!";
		sws_freeContext(ctx);
		return false;
	}

	std::copy( tmp_out_pic.data[0], tmp_out_pic.data[0] + tmp_out_pic.linesize[0]*src.height(),
		std::back_inserter(dst) );
	sws_freeContext(ctx);
	avpicture_free(&tmp_out_pic);
	return true;
}


bool convert_yuv420p_to_rgb32( const Frame_t& src, size_t src_w,
							  size_t src_h, Frame_t& dst )
{
	dst.clear();

	SwsContext* ctx = sws_getContext( src_w, src_h, PIX_FMT_YUV420P,
		src_w, src_h, PIX_FMT_RGB32, SWS_FAST_BILINEAR, 0,0,0 );

	if (!ctx)
	{
		qDebug() << "sws context initialisation fail";
		return false;
	}

	AVPicture tmp_pic;

	//copy frame from QVideoFrame into tmp_pic
	int bytes_copied = avpicture_fill(&tmp_pic, const_cast<uint8_t*>(src.data()),
		PIX_FMT_YUV420P, src_w, src_h);

	if (bytes_copied < 0)
	{
		qDebug() << "H264Encoder: error calling avpicture_fill(...)!";
		sws_freeContext(ctx);
		return false;
	}
	AVPicture tmp_out_pic;
	if (avpicture_alloc(&tmp_out_pic, PIX_FMT_RGB32, src_w, src_h) != 0)
	{
		qDebug() << "avpicture_alloc() fail!";
		sws_freeContext(ctx);
		return false;
	}

	//convert img into m_out_format and save in m_in_pic
	int scaled_img_height = sws_scale(ctx, tmp_pic.data, tmp_pic.linesize, 0, src_h,
		tmp_out_pic.data, tmp_out_pic.linesize);

	if ( scaled_img_height < 0 || scaled_img_height != src_h )
	{
		qDebug() << "Scaling failed!";
		sws_freeContext(ctx);
		return false;
	}

	std::copy( tmp_out_pic.data[0], tmp_out_pic.data[0] + tmp_out_pic.linesize[0]*src_h,
		std::back_inserter(dst) );
	sws_freeContext(ctx);
	avpicture_free(&tmp_out_pic);
	return true;
}


bool convert_yuv420p_to_rgb24( const Frame_t& src, size_t src_w,
							  size_t src_h, Frame_t& dst )
{
	dst.clear();

	SwsContext* ctx = sws_getContext( src_w, src_h, PIX_FMT_YUV420P,
		src_w, src_h, PIX_FMT_RGB24, SWS_FAST_BILINEAR, 0,0,0 );

	if (!ctx)
	{
		qDebug() << "sws context initialisation fail";
		return false;
	}

	AVPicture tmp_pic;

	//copy frame from QVideoFrame into tmp_pic
	int bytes_copied = avpicture_fill(&tmp_pic, const_cast<uint8_t*>(src.data()),
		PIX_FMT_YUV420P, src_w, src_h);

	if (bytes_copied < 0)
	{
		qDebug() << "H264Encoder: error calling avpicture_fill(...)!";
		sws_freeContext(ctx);
		return false;
	}
	AVPicture tmp_out_pic;
	if (avpicture_alloc(&tmp_out_pic, PIX_FMT_RGB24, src_w, src_h) != 0)
	{
		qDebug() << "avpicture_alloc() fail!";
		sws_freeContext(ctx);
		return false;
	}

	//convert img into m_out_format and save in m_in_pic
	int scaled_img_height = sws_scale(ctx, tmp_pic.data, tmp_pic.linesize, 0, src_h,
		tmp_out_pic.data, tmp_out_pic.linesize);

	if ( scaled_img_height < 0 || scaled_img_height != src_h )
	{
		qDebug() << "Scaling failed!";
		sws_freeContext(ctx);
		return false;
	}

	std::copy( tmp_out_pic.data[0], tmp_out_pic.data[0] + tmp_out_pic.linesize[0]*src_h,
		std::back_inserter(dst) );
	sws_freeContext(ctx);
	avpicture_free(&tmp_out_pic);
	return true;
}


bool convert_yuv420p_to_rgb24( const QVideoFrame& src, Frame_t& dst )
{

	dst.clear();

	SwsContext* ctx = sws_getContext( src.width(), src.height(), PIX_FMT_YUV420P,
		src.width(), src.height(), PIX_FMT_RGB24, SWS_FAST_BILINEAR, 0,0,0 );

	if (!ctx)
	{
		qDebug() << "sws context initialisation fail";
		return false;
	}

	AVPicture tmp_pic;

	//copy frame from QVideoFrame into tmp_pic
	int bytes_copied = avpicture_fill(&tmp_pic, const_cast<uint8_t*>(src.bits()),
		PIX_FMT_YUV420P, src.width(), src.height());

	if (bytes_copied < 0)
	{
		qDebug() << "H264Encoder: error calling avpicture_fill(...)!";
		sws_freeContext(ctx);
		return false;
	}
	AVPicture tmp_out_pic;
	if (avpicture_alloc(&tmp_out_pic, PIX_FMT_RGB24, src.width(), src.height()) != 0)
	{
		qDebug() << "avpicture_alloc() fail!";
		sws_freeContext(ctx);
		return false;
	}

	//convert img into m_out_format and save in m_in_pic
	int scaled_img_height = sws_scale(ctx, tmp_pic.data, tmp_pic.linesize, 0, src.height(),
		tmp_out_pic.data, tmp_out_pic.linesize);

	if ( scaled_img_height < 0 || scaled_img_height != src.height() )
	{
		qDebug() << "Scaling failed!";
		sws_freeContext(ctx);
		return false;
	}

	std::copy( tmp_out_pic.data[0], tmp_out_pic.data[0] + tmp_out_pic.linesize[0]*src.height(),
		std::back_inserter(dst) );
	sws_freeContext(ctx);
	avpicture_free(&tmp_out_pic);
	return true;
}





bool convert_rgb24_to_yuv420p( const QVideoFrame& src, std::vector<Frame_t>& dstStrides )
{
	dstStrides.clear();

	SwsContext* ctx = sws_getContext( src.width(), src.height(), PIX_FMT_RGB24,
		src.width(), src.height(), PIX_FMT_YUV420P, SWS_FAST_BILINEAR, 0,0,0 );
	if (!ctx)
	{
		qDebug() << "sws context initialisation fail";
		return false;
	}

	AVPicture tmp_pic;

	//copy frame from QVideoFrame into tmp_pic
	int bytes_copied = avpicture_fill(&tmp_pic, const_cast<uint8_t*>(src.bits()),
		PIX_FMT_RGB24, src.width(), src.height());
	if (bytes_copied < 0)
	{
		qDebug() << "H264Encoder: error calling avpicture_fill(...)!";
		sws_freeContext(ctx);
		return false;
	}

	AVPicture tmp_out_pic;
	if (avpicture_alloc(&tmp_out_pic, PIX_FMT_YUV420P, src.width(), src.height()) != 0)
	{
		qDebug() << "avpicture_alloc() fail!";
		sws_freeContext(ctx);
		return false;
	}

	//convert img into m_out_format and save in m_in_pic
	int scaled_img_height = sws_scale(ctx, tmp_pic.data, tmp_pic.linesize, 0, src.height(),
		tmp_out_pic.data, tmp_out_pic.linesize);
	if ( scaled_img_height < 0 || scaled_img_height != src.height() )
	{
		qDebug() << "Scaling failed!";
		sws_freeContext(ctx);
		return false;
	}

	dstStrides.clear();
	dstStrides.resize(3);

	std::copy( tmp_out_pic.data[0], tmp_out_pic.data[0] + tmp_out_pic.linesize[0]*src.height(),
				std::back_inserter(dstStrides[0]) );

	for (size_t i = 1; i < 3; i++)
		std::copy( tmp_out_pic.data[i], tmp_out_pic.data[i] + tmp_out_pic.linesize[i] * src.height() / 2,
			std::back_inserter(dstStrides[i]));

	sws_freeContext(ctx);
	avpicture_free(&tmp_out_pic);
	return true;
}

