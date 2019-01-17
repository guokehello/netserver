#pragma once
#include <string>
#include <boost/asio.hpp>

class Client
{
public:
    Client(std::shared_ptr<boost::asio::io_service> spIoService, const std::string& ip, int port);
    virtual ~Client();

	void start();

private:
    void handleConnect(const boost::system::error_code& ec);
    void ReadData();
    void WriteData();

private:
	std::shared_ptr<boost::asio::io_service> m_spIoService;
	std::shared_ptr<boost::asio::ip::tcp::socket> m_spSocket;
	std::string m_strIp;
	int m_nPort;
    enum {max_size = 1024};
    char m_szData[max_size];
};