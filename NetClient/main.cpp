
#include <boost/asio.hpp>
#include "Client.h"

using namespace std;

int main()
{
    std::shared_ptr<boost::asio::io_service>  spIoService = std::make_shared<boost::asio::io_service>();

    for (int i = 0; i < 10; ++i)
    {
        Client* pClient = new Client(spIoService, "127.0.0.1", 11111);
        pClient->start();
    }


    spIoService->run();

    getchar();
}