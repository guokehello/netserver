
#include <boost/bind.hpp>
#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service) : m_socket(io_service)
{

}

Connection::~Connection()
{

}

void Connection::Start()
{
    this->doRead();
}

boost::asio::ip::tcp::socket& Connection::GetSocket()
{
    return m_socket;
}

void Connection::doRead()
{
    auto self = this->shared_from_this();
    m_socket.async_read_some(boost::asio::buffer(m_szBuffer, max_size), [self](const boost::system::error_code& ec, std::size_t length)
    {
        if (ec)
        {
            printf("read failed\n");
        }
        else
        {
            self->doWrite(length);
        }
    });
}

void Connection::doWrite(std::size_t length)
{
    auto self = this->shared_from_this();
    boost::asio::async_write(m_socket, boost::asio::buffer(m_szBuffer, length), [self](const boost::system::error_code& ec, std::size_t length)
    {
        if (ec)
        {
            printf("write failed\n");
        }
        else
        {
            self->doRead();
        }
    });
}