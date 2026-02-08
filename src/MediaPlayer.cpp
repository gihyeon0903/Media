#include "include/MediaPlayer.h"
#include "external/include/miniaudio.h"
#include <fstream>
#include <iostream>

namespace media {

const char* PlayerStateTable[] = {
    "PLAYER_STATE_IDLE",
    "PLAYER_STATE_INITIALIZED",
    "PLAYER_STATE_PREPARING",
    "PLAYER_STATE_PREPARED",
    "PLAYER_STATE_STARTED",
    "PLAYER_STATE_PAUSED",
    "PLAYER_STATE_STOPPED",
    "PLAYER_STATE_PLAYBACK_COMPLETE",
    "PLAYER_STATE_END",
    "PLAYER_STATE_ERROR",
};


MediaPlayer::MediaPlayer() {
    mState = PLAYER_STATE_IDLE;
    mPath = "";
    mSampleRate = 16000;
    mVolume = 5;
}

MediaPlayer::~MediaPlayer() {
    // TODO: If ma_sound, ma_engine are not uninitialized, we should uninitialize them.
    //       Now, Always uninitialize them.
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
}

player_state_t MediaPlayer::getState() {
    return mState;
}

bool MediaPlayer::setDataSource(const std::string Path) {
    if (mState != PLAYER_STATE_IDLE) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }

    // if (!std::ifstream(Path)) {
    //     std::cout << "File is invalid" << std::endl;
    //     return false;
    // }

    mPath = Path;
    mState = PLAYER_STATE_INITIALIZED;
    return true;
}

bool MediaPlayer::prepare() {
    if (mState != PLAYER_STATE_INITIALIZED && mState != PLAYER_STATE_STOPPED) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }

    engineConfig = ma_engine_config_init();
    engineConfig.sampleRate = mSampleRate;
    ma_result_ = ma_engine_init(&engineConfig, &engine);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine." << std::endl;
        return false;
    }

    ma_result_ = ma_sound_init_from_file(&engine, mPath.c_str(), 0, NULL, NULL, &sound);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to initialize sound." << std::endl;
        return false;
    }

    ma_result_ = ma_sound_set_end_callback(&sound, callback_handler, this);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to set end callback." << std::endl;
        return false;
    }

    ma_sound_set_volume(&sound, mVolume);

    mState = PLAYER_STATE_PREPARED;
    return true;
}

bool MediaPlayer::start() { 
    if (mState != PLAYER_STATE_PREPARED && mState != PLAYER_STATE_PAUSED && mState != PLAYER_STATE_PLAYBACK_COMPLETE) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }
    
    ma_result_ = ma_sound_start(&sound);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to start sound." << std::endl;
        return false;
    }

    mState = PLAYER_STATE_STARTED;
    return true;
}

void MediaPlayer::callback_handler(void* pPlayer, ma_sound* pSound) {
    (void)pSound;
    MediaPlayer* player = (MediaPlayer*)pPlayer;
    if (player) {
        player->playback_completed();
    }
    return;
}

void MediaPlayer::playback_completed() {
    mState = PLAYER_STATE_PLAYBACK_COMPLETE;
    return;
}

bool MediaPlayer::stop() {
    if (mState != PLAYER_STATE_STARTED && mState != PLAYER_STATE_PAUSED \
        && mState != PLAYER_STATE_PLAYBACK_COMPLETE && mState != PLAYER_STATE_STOPPED) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }

    ma_result_ = ma_sound_stop(&sound);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to stop sound." << std::endl;
        return false;
    }

    ma_result_ = ma_sound_seek_to_pcm_frame(&sound, 0);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to seek sound." << std::endl;
        return false;
    }

    mState = PLAYER_STATE_STOPPED;
    return true;
}

bool MediaPlayer::pause() {
    if (mState != PLAYER_STATE_STARTED && mState != PLAYER_STATE_PAUSED) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }

    ma_result_ = ma_sound_stop(&sound);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to pause sound." << std::endl;
        return false;
    }

    mState = PLAYER_STATE_PAUSED;
    return true;
}

bool MediaPlayer::setSampleRate(int sampleRate) {
    if (mState >= PLAYER_STATE_PREPARED) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }

    mSampleRate = sampleRate;
    return true;
}

bool MediaPlayer::setVolume(float volume) {
    mVolume = volume;
    if (mState >= PLAYER_STATE_PREPARED) {
        ma_sound_set_volume(&sound, mVolume);
    }
    return true;
}

bool MediaPlayer::seekTo(int msec) {
    if (mState != PLAYER_STATE_PREPARED && mState != PLAYER_STATE_STARTED \
        && mState != PLAYER_STATE_PAUSED && mState != PLAYER_STATE_PLAYBACK_COMPLETE) {
        std::cout << "PLAYER_STATE is not wrong(mCulState : " << PlayerStateTable[mState] << ")" << std::endl;
        return false;
    }
    
    ma_uint32 sampleRate;
    ma_result_ = ma_sound_get_data_format(&sound, NULL, NULL, &sampleRate, NULL, 0);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to get sample rate." << std::endl;
        return false;
    }

    ma_uint64 frameIndex = (ma_uint64)msec * sampleRate / 1000;
    ma_result_ = ma_sound_seek_to_pcm_frame(&sound, frameIndex);
    if (ma_result_ != MA_SUCCESS) {
        std::cout << "Failed to seek to frame." << std::endl;
        return false;
    }
    return true;
}
} // namespace media