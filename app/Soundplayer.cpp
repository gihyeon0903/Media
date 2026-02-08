#include <iostream>
#include <windows.h>
#include "app/Soundplayer.h"
#include "include/MediaPlayer.h"

void Soundplayer_main() {
    media::MediaPlayer player;

    std::cout << "setDataSource" << std::endl;
    player.setDataSource("res/test2.wav");

    std::cout << "prepare" << std::endl;
    player.prepare();

    std::cout << "start" << std::endl;
    player.start();
    
    Sleep(2000);
    std::cout << "pause" << std::endl;
    player.pause();

    Sleep(2000);
    std::cout << "start" << std::endl;
    player.start();


    Sleep(2000);
    std::cout << "pause" << std::endl;
    player.pause();

    Sleep(2000);    
    std::cout << "start" << std::endl;
    player.start();


    Sleep(5000);

    std::cout << "soundplayer exit" << std::endl;

    return;
}
