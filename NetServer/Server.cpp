

#include <boost/bind/bind.hpp>
#include <boost/bind.hpp>
#include "Server.h"

Server::Server(boost::asio::io_service& io_service, int port)
: m_Acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
, m_IoService(io_service)
{
}

Server::~Server()
{

}

void Server::Start()
{
    std::shared_ptr<Connection> pConnection(new Connection(m_IoService));
    m_Acceptor.async_accept(pConnection->GetSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error, pConnection));
}

void Server::handleAccept(boost::system::error_code ec, std::shared_ptr<Connection> pConnection)
{
    if (!ec)
    {
        printf("new connect(%s) come in\n", pConnection->GetSocket().remote_endpoint().address().to_string().c_str());
        pConnection->Start();
    }
    Start();
}