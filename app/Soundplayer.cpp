#include <iostream>
#include <windows.h>
#include "app/Soundplayer.h"
#include "include/MediaPlayer.h"

void Soundplayer_main() {
    media::MediaPlayer player;

    std::cout << "Request setDataSource" << std::endl;
    player.setDataSource("res/test2.wav");

    std::cout << "Request prepare" << std::endl;
    player.prepare();

    std::cout << "Request start" << std::endl;
    player.start();
    
    Sleep(1000);
    std::cout << "Request pause" << std::endl;
    player.pause();

    Sleep(1000);
    std::cout << "Request start" << std::endl;
    player.start();


    Sleep(1000);
    std::cout << "Request pause" << std::endl;
    player.pause();

    Sleep(1000);    
    std::cout << "Request start" << std::endl;
    player.start();


    while(player.getState() != media::PLAYER_STATE_PLAYBACK_COMPLETE) {
        std::cout << "wait playback complete...." << std::endl;
        Sleep(1000);
    }

    std::cout << "soundplayer exit" << std::endl;

    return;
}
