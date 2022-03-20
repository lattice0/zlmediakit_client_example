#include "ZLMediaKit/src/Player/PlayerBase.h"
#include "ZLMediaKit/src/Player/MediaPlayer.h"
#include "ZLMediaKit/src/Extension/Frame.h"

#include <memory>
using namespace std;
using namespace toolkit;
using namespace mediakit;

int main() {
    auto player = std::make_shared<MediaPlayer>();
    weak_ptr<MediaPlayer> weakPlayer = player;
    player->setOnPlayResult([weakPlayer](const SockException &ex) {
        InfoL << "OnPlayResult:" << ex.what();
        auto strongPlayer = weakPlayer.lock();
        if (ex || !strongPlayer) {
            return;
        }

        auto viedoTrack = strongPlayer->getTrack(TrackVideo);
        if (!viedoTrack) {
            WarnL << "none video Track!";
            return;
        }
        
        viedoTrack->addDelegate(std::make_shared<FrameWriterInterfaceHelper>([](const Frame::Ptr &frame) {
            //please decode video here
            std::cout << "frame!" << std::endl;
            return true;
        }));
        
    });

    player->setOnShutdown([](const SockException &ex) {
        ErrorL << "OnShutdown:" << ex.what();
    });

    //rtp transport over tcp
    (*player)[Client::kRtpType] = Rtsp::RTP_TCP;
    std::cout << "gonna play" << std::endl;
    player->play("rtsp://admin:888888@192.168.1.22:10554/tcp/av0_0");
    while (true) {}
}