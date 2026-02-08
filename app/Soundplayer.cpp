#include <iostream>
#include <windows.h>
#include "app/Soundplayer.h"
#include "include/MediaPlayer.h"

void Soundplayer_main() {
    media::MediaPlayer player;

    std::cout << "Request setDataSource" << std::endl;
    player.setDataSource("res/test.wav");

    std::cout << "Request setVolume(0.4)" << std::endl;
    player.setVolume((float)0.4);

    std::cout << "Request setSampleRate(44100)" << std::endl;
    player.setSampleRate(44100);

    std::cout << "Request prepare" << std::endl;
    player.prepare();

    std::cout << "Request start" << std::endl;
    player.start();
    
    Sleep(5000);
    std::cout << "Request setVolume(0.7)" << std::endl;
    player.setVolume((float)0.7);
    std::cout << "Request pause" << std::endl;
    player.pause();

    Sleep(5000);
    std::cout << "Request start" << std::endl;
    player.start();
    Sleep(5000);

    std::cout << "Request seekTo(20000)" << std::endl;
    player.seekTo(20000);

    while(player.getState() != media::PLAYER_STATE_PLAYBACK_COMPLETE) {
        std::cout << "wait playback complete...." << std::endl;
        Sleep(1000);
    }

    std::cout << "soundplayer exit" << std::endl;

    return;
}
