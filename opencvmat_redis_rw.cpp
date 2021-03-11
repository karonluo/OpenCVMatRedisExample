#include <stdlib.h>
#include <stdio.h>
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int args, char** argv)
{
	cv::Mat mat;
	redisContext *context = redisConnect("127.0.0.1", 6379); // 链接 redis server
	redisReply *reply = NULL;
	mat = cv::imread("/home/yt/software/FFmpeg/test.jpg");
	
	// -------------------------------------------------- 写入
	printf("Write to redis ...\r\n");
	reply =(redisReply*) redisCommand(context, "SET mat_data %b", mat.data, mat.total()*mat.channels());
	freeReplyObject(reply);
	
	// -------------------------------------------------- 读取
	printf("Read from redis ...\r\n");	
	reply = (redisReply*)redisCommand(context, "GET mat_data");

	// -------------------------------------------------- 恢复成 OpenCV Mat
	std::vector<char> buffer(reply->str, reply->str+reply->len);
	cv::Mat mat_tmp = cv::Mat(cv::Size(1920,1080), CV_8UC3, buffer.data()); // 重新组装 OpenCV Mat 对象
	freeReplyObject(reply);
	std::vector<char>().swap(buffer);
	buffer.clear();
		
	// -------------------------------------------------- 测试
	cv::imwrite("/tmp/mat_tmp.jpg", mat_tmp);
	mat_tmp.release();	
	redisFree(context);
	printf("Write picture to I/O is OK!\r\n");
	return 0;
}
