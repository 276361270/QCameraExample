/*Convert images between different pixel format
 **/

#pragma once
extern "C"
{
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}
#include <QVideoFrame>
#include <QVector>


bool convert_yuv420p_to_rgb32( const QVideoFrame& src, Frame_t& dst );

bool convert_yuv420p_to_rgb32( const Frame_t& src, size_t src_w, size_t src_h,
							  Frame_t& dst );

bool convert_yuv420p_to_rgb24( const Frame_t& src, size_t src_w,
							  size_t src_h, Frame_t& dst );

bool convert_yuv420p_to_rgb24( const QVideoFrame& src, Frame_t& dst );


bool convert_rgb24_to_yuv420p(const QVideoFrame& src, std::vector<Frame_t>& dstStrides);
