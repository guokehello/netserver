
#ifndef __SERVER_H
#define __SERVER_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Connection.h"

class Server
{
public:
    Server(boost::asio::io_service& io_service, int port);
    ~Server();

    void Start();

private:
    void handleAccept(boost::system::error_code ec, std::shared_ptr<Connection> pConnection);

private:
    boost::asio::ip::tcp::acceptor m_Acceptor;
    boost::asio::io_service& m_IoService;
};

#endif  // __SERVER_H