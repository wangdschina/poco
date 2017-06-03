#include "AndyTCPConnection.h"

#include "Poco/Util/Application.h"
#include "Poco/Timestamp.h"
#include "Poco/Exception.h"
#include "Poco/DateTimeFormatter.h"

using Poco::Util::Application;
using Poco::Timestamp;
using Poco::DateTimeFormatter;


AndyTCPConnection::AndyTCPConnection( const StreamSocket& s, const std::string& arg1, int arg2, double arg3 ) : 
	TCPServerConnection(s),
	m_arg1(arg1), 
	m_arg2(arg2), 
	m_arg3(arg3)
{

}

void AndyTCPConnection::run()
{
	Application& app = Application::instance();
	// 日志输出连接的TCP用户的地址（IP和端口）
	app.logger().information("Request from " + this->socket().peerAddress().toString());
	try
	{
		// 向客户端发送数据，这里以发送一个表示时间的字符串为例
		Timestamp now;
		std::string strFmt("%Y:%m:%d %H:%M:%S");
		std::string dt(DateTimeFormatter::format(now, strFmt));
		dt.append("\r\n");
		socket().sendBytes(dt.data(), (int) dt.length());
	}
	catch (Poco::Exception& e)
	{
		app.logger().log(e);
	}
}
