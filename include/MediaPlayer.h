#include <string>
#include "external/include/miniaudio.h"

namespace media {

typedef enum player_state_t {
    PLAYER_STATE_IDLE,
    PLAYER_STATE_INITIALIZED,
    PLAYER_STATE_PREPARING,
    PLAYER_STATE_PREPARED,
    PLAYER_STATE_STARTED,
    PLAYER_STATE_PAUSED,
    PLAYER_STATE_STOPPED,
    PLAYER_STATE_PLAYBACK_COMPLETE,
    PLAYER_STATE_END,
    PLAYER_STATE_ERROR,
} player_state_t;

class MediaPlayer {
public: 
    MediaPlayer();
    ~MediaPlayer();

    player_state_t getState();
    bool setDataSource(const std::string Path);
    bool prepare();
    bool start();
    bool stop();
    bool pause();
    bool setSampleRate(int sampleRate);
    bool setVolume(float volume);
    bool seekTo(int msec);

    // miniaudio callback func should register C style function, So, We need to use static function.
    // And callback_handler can not acces member variable directly, So, We need to pass player and call playback_completed.
    static void callback_handler(void* pPlayer, ma_sound* pSound);
    void playback_completed();
    bool isPlaying();

private:
    std::string mPath;
    player_state_t mState;
    // mSampleRate can not be changed during playing. But, mVolume can be changed.
    int mSampleRate;
    float mVolume;

    ma_sound sound;
    ma_result ma_result_;
    ma_engine_config engineConfig;
    ma_engine engine;
};

}