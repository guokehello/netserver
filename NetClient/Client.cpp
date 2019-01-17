
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include "Client.h"

Client::Client(std::shared_ptr<boost::asio::io_service> spIoService, const std::string& ip, int port)
    : m_spIoService(spIoService)
    , m_spSocket(nullptr)
    , m_strIp(ip)
    , m_nPort(port)
{
    memset(m_szData, 0, max_size);
}

Client::~Client()
{
}

void Client::start()
{
    m_spSocket = std::make_shared<boost::asio::ip::tcp::socket>(*m_spIoService);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(m_strIp), m_nPort);

    printf("start\n");
    m_spSocket->async_connect(endpoint, [this](const boost::system::error_code& ec)
    {
        if (ec)
        {
            printf("connect error\n");
        }
        else
        {
            printf("connect success\n");
            WriteData();
        }
    });

}

void Client::ReadData()
{
    m_spSocket->async_read_some(boost::asio::buffer(m_szData, max_size), [this](const boost::system::error_code& ec, std::size_t length)
    {
        if (ec)
        {
            printf("read error\n");
        }
        else
        {
            printf("read success(%s)\n", this->m_szData);
            ReadData();
        }
    });
}

void Client::WriteData()
{
    char data[max_size] = "helloworld";

    m_spSocket->async_send(boost::asio::buffer(data, strlen(data)), [this](const boost::system::error_code& ec, std::size_t length)
    {
        if (ec)
        {
            printf("write error\n");
        }
        else
        {
            printf("write success\n");
            ReadData();
        }
    });
}

void Client::handleConnect(const boost::system::error_code& ec)
{
    if (ec)
    {
        printf("connect error\n");
    }
    else
    {
        printf("connect success\n");
    }
}



