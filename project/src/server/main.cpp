#include "../../include/server/server.h"

int main(int argc, char **argv) {
    int port;
    try {
        port=std::atoi(argv[1]);
    }catch (std::exception &ex){
        std::cerr<<ex.what()<<std::endl;
        return 1;
    }
    Server s(port);
    s.start();
    return 0;
}
