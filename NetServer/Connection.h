
#ifndef __CONNECTION_H
#define __CONNECTION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(boost::asio::io_service& io_service);
    ~Connection();

    void Start();

    boost::asio::ip::tcp::socket& GetSocket();

private:
    void doRead();
    void doWrite(std::size_t length);

private:
    boost::asio::ip::tcp::socket m_socket;
    enum {max_size = 1024};

    char m_szBuffer[max_size];
};

#endif  // __CONNECTION_H