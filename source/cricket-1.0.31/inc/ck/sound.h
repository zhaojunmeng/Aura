// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */
/** @defgroup CkSound CkSound */
/** @{ */

#pragma once
#include "ck/platform.h"
#include "ck/pathtype.h"
#include "ck/attenuationmode.h"
#include "ck/audiocallback.h"


class CkBank;
class CkMixer;
class CkCustomStream;

/** A sound (either memory-resident or streamed). */

class CkSound 
{
public:
    /** Sets the mixer to which this sound is assigned.
      Setting NULL will assign it to the master mixer. */
    void setMixer(CkMixer*);

    /** Gets the mixer to which this sound is assigned. */
    CkMixer* getMixer();


    /** Returns true if the sound is ready.
      Bank sounds are ready immediately after creation; stream sounds may not be. */
    bool isReady() const;


    /** Returns true if an error occurred while creating the sound. */
    bool isFailed() const;


    /** Play the sound. */
    void play();

    /** Stop the sound. */
    void stop();

    /** Gets whether the sound is playing. */
    bool isPlaying() const; 


    /** Sets whether the sound is paused. */
    void setPaused(bool);

    /** Gets whether the sound is paused. */
    bool isPaused() const;


    /** Set the loop start and end.
      Default is to loop over all sample frames. 
      EndFrame is defined as one frame after the last frame of the loop.
      Setting endFrame = -1 is equivalent to setting it to getLength(). 

     @par Android note: 
      This has no effect for streams in formats other than .cks. */
    void setLoop(int startFrame, int endFrame);

    /** Get the loop start and end. */
    void getLoop(int& startFrame, int& endFrame) const;

    /** Sets the number of times the sound should loop.  
      0 means no looping (play once and then stop).
      1 means it will play twice; 2 means it will play 3 times; etc. 
      -1 means it will loop indefinitely until the sound is stopped or releaseLoop() is called. */
    void setLoopCount(int);

    /** Gets the number of times the sound should loop.  
      0 means no looping (play once and then stop).
      1 means it will play twice; 2 means it will play 3 times; etc. 
      -1 means it will loop indefinitely until the sound is stopped or releaseLoop() is called. */
    int getLoopCount() const;

    /** Gets the number of the current loop.
      For example, returns 0 if this is the first time playing through this sample;
      returns 1 if it is on its second loop through the sample; etc. */
    int getCurrentLoop() const;

    /** Makes the current loop the last.
      This is useful when you don't know in advance how many times you will
      want to loop; set the loop count to -1, and call releaseLoop() when
      you want it to stop looping and play to the end. */
    void releaseLoop();


    /** Set the play position in the sound, in sample frames.
      This can be called before playing, to start from an offset into
      the sound; or during playback, to jump to a new location. */
    void setPlayPosition(int);

    /** Set the play position in the sound, in milliseconds.
      This can be called before playing, to start from an offset into
      the sound; or during playback, to jump to a new location. */
    void setPlayPositionMs(float);

    /** Get the current play position in the sound, in sample frames. */
    int getPlayPosition() const;

    /** Get the current play position in the sound, in milliseconds. */
    float getPlayPositionMs() const;


    /** Sets the volume.
      The volume can range from 0 to 1. The default value is 1. */
    void setVolume(float);

    /** Gets the volume.
      The volume can range from 0 to 1. The default value is 1. */
    float getVolume() const;


    /** Gets the volume value used for mixing. 
      This is the product of the volume set with setVolume() and the mixed
      volume value of the mixer to which the sound is assigned. */
    float getMixedVolume() const;


    /** Sets the pan.
      The pan can range from -1 (left) to +1 (right). The default is 0 (center). */
    void setPan(float);

    /** Gets the pan.
      The pan can range from -1 (left) to +1 (right). The default is 0 (center). */
    float getPan() const;

    /** Sets the pan matrix explicitly.  
      The pan matrix determines how the left and right channels of an input are weighted during mixing.
      Usually it is set by setPan(), but you can use setPanMatrix() if you need more control.
      For a mono input, the left channel of the output is the input scaled by ll, and the right channel of the output is the input scaled by rr.  The off-diagonal lr and rl terms are ignored.
      For a stereo input, the left channel of the output is the left channel of the input scaled by ll plus the right channel of the input scaled by lr.  The right channel of the output is the left channel of the input scaled by rl plus the right channel of the input scaled by rr.
      */
    void setPanMatrix(float ll, float lr, float rl, float rr);

    /** Gets the pan matrix.
      The pan matrix determines how the left and right channels of an input are weighted during mixing.
      Usually it is set by setPan(), but you can use setPanMatrix() if you need more control.
      For a mono input, the left channel of the output is the input scaled by ll, and the right channel of the output is the input scaled by rr.  The off-diagonal lr and rl terms are ignored.
      For a stereo input, the left channel of the output is the left channel of the input scaled by ll plus the right channel of the input scaled by lr.  The right channel of the output is the left channel of the input scaled by rl plus the right channel of the input scaled by rr.
      */
    void getPanMatrix(float& ll, float& lr, float& rl, float& rr) const;


    /** Sets the pitch shift value, in half-steps.
      This also changes the playback speed of the sound.  
      Positive values mean higher pitch (and faster playback); lower values mean lower pitch 
      (and slower playback).  The default value is 0. 

     @par Android note: 
     This does not work for streams in formats other than .cks. */
    void setPitchShift(float halfSteps);

    /** Gets the pitch shift value, in half-steps.
      Positive values mean higher pitch (and faster playback); lower values mean lower pitch 
      (and slower playback).  The default value is 0. 
     @par Android note: 
     This does not work for streams in formats other than .cks. */
    float getPitchShift() const;


    /** Sets the playback speed.
      Values greater than 1 mean faster playback; values less than 1 mean
      slower playback.  The default value is 1.
     @par Android note: 
     This does not work for streams in formats other than .cks. */
    void setSpeed(float);

    /** Gets the playback speed.
      Values greater than 1 mean faster playback; values less than 1 mean
      slower playback.  The default value is 1. 
     @par Android note: 
     This does not work for streams in formats other than .cks. */
    float getSpeed() const;


    /** Gets the total duration of the sound, in sample frames.
      Stream sounds will return -1 if they are not ready or if the length is unknown. */
    int getLength() const;

    /** Gets the total duration of the sound, in milliseconds.
      Stream sounds will return -1 if they are not ready or if the length is unknown. */
    float getLengthMs() const;

    /** Gets the sample rate of the sound, in Hz.
      Stream sounds will return -1 if they are not ready. */
    int getSampleRate() const;

    /** Gets the number of channels in the sound (1 for mono, 2 for stereo).
      Stream sounds will return -1 if they are not ready. */
    int getChannels() const;


    /** Sets a callback to be called for each slice of audio coming from
      this sound.
      This will be called on a thread that is not the main thread; be sure
      not to spend too much time in the callback.
     @par Android note: 
     This does not work for streams in formats other than .cks. */
    void setAudioCallback(CkAudioCallback, void* data);

    /** Gets a callback to be called for each slice of audio coming from
      this sound. */
    void getAudioCallback(CkAudioCallback&, void*& data);



    /** Sets whether 3D positioning is enabled.
      If enabled, pan will be determined by the sound and listener positions,
      ignoring the value set by setPan().  Volume will be attenuated based
      on the sound and listener positions and the attenuation settings. */
    void set3dEnabled(bool);

    /** Gets whether 3D positioning is enabled. 
      If enabled, pan will be determined by the sound and listener positions,
      ignoring the value set by setPan().  Volume will be attenuated based
      on the sound and listener positions and the attenuation settings. */
    bool is3dEnabled() const;

    /** Sets the position of the sound emitter in 3D space.
      This is used for pan and volume calculations when 3D positioning is enabled. */
    void set3dPosition(float x, float y, float z);

    /** Gets the position of the sound emitter in 3D space.
      This is used for pan and volume calculations when 3D positioning is enabled. */
    void get3dPosition(float& x, float& y, float& z) const;

    /** Sets the velocity of the sound emitter in 3D space.
      This is used for doppler shift calculations when 3D positioning is enabled.
      The units should be the same as those used for the set3dSoundSpeed(). */
    void set3dVelocity(float vx, float vy, float vz);

    /** Gets the velocity of the sound emitter in 3D space.
      This is used for doppler shift calculations when 3D positioning is enabled.
      The units should be the same as those used for the set3dSoundSpeed(). */
    void get3dVelocity(float& vx, float& vy, float& vz) const;

    /** Sets the listener position and rotation in 3D space. 
      This is used for pan and volume calculations when 3D positioning is enabled.
      @param eyeX,eyeY,eyeZ           The listener's position
      @param lookAtX,lookAtY,lookAtZ  The listener's look-at point
      @param upX,upY,upZ              The listener's up vector
      */
    static void set3dListenerPosition(float eyeX, float eyeY, float eyeZ,
                                      float lookAtX, float lookAtY, float lookAtZ,
                                      float upX, float upY, float upZ);

    /** Gets the listener position and rotation in 3D space. 
      This is used for pan and volume calculations when 3D positioning is enabled.
      @param eyeX,eyeY,eyeZ           The listener's position
      @param lookAtX,lookAtY,lookAtZ  The listener's look-at point
      @param upX,upY,upZ              The listener's up vector
      */
    static void get3dListenerPosition(float& eyeX, float& eyeY, float& eyeZ,
                                      float& lookAtX, float& lookAtY, float& lookAtZ,
                                      float& upX, float& upY, float& upZ);

    /** Sets the listener velocity in 3D space.
      This is used for doppler shift calculations when 3D positioning is enabled. 
      The units should be the same as those used for the set3dSoundSpeed(). */
    static void set3dListenerVelocity(float vx, float vy, float vz);

    /** Gets the listener velocity in 3D space.
      This is used for doppler shift calculations when 3D positioning is enabled.
      The units should be the same as those used for the set3dSoundSpeed(). */
    static void get3dListenerVelocity(float& vx, float& vy, float& vz);

    /** Sets parameters used for 3D volume attenuation. 
      @param mode      The attenuation mode (default is kCkAttenuationMode_InvDistanceSquared)
      @param nearDist  The near distance; sounds closer than this distance will not be attenuated (default is 1.0)
      @param farDist   The far distance; sounds further than this will be at the far volume (default is 100.0)
      @param farVol    The far volume; sounds further than farDist will be at this volume (default is 0.0)
      */
    static void set3dAttenuation(CkAttenuationMode mode, float nearDist, float farDist, float farVol);

    /** Gets parameters used for 3D volume attenuation. 
      @param mode      The attenuation mode
      @param nearDist  The near distance; sounds closer than this distance will not be attenuated.
      @param farDist   The far distance; sounds further than this will be at the far volume.
      @param farVol    The far volume; sounds further than farDist will be at this volume.
      */
    static void get3dAttenuation(CkAttenuationMode& mode, float& nearDist, float& farDist, float& farVol);

    /** Sets the speed of sound.
      This is used for doppler shift calculations when 3D positioning is enabled.  If no doppler
      shift is desired, this can be set to 0 (which is the default value).
      You may want to use the predefined constants for the speed of sound (such as 
      k_soundSpeed_MetersPerSecond); use the constant that corresponds to
      the unit system you are using for your velocity and position values.
      You can also exaggerate the doppler effect by using a smaller value. */
    static void set3dSoundSpeed(float);

    /** Gets the speed of sound.
      This is used for doppler shift calculations when 3D positioning is enabled.  */
    static float get3dSoundSpeed();

    /** The speed of sound in dry air at 20 degrees C, in centimeters per second.
      This value is provided as a convenience for CkSound::set3dSoundSpeed(). */
    static const float k_soundSpeed_CentimetersPerSecond;

    /** The speed of sound in dry air at 20 degrees C, in meters per second.
      This value is provided as a convenience for CkSound::set3dSoundSpeed(). */
    static const float k_soundSpeed_MetersPerSecond;

    /** The speed of sound in dry air at 20 degrees C, in inches per second.
      This value is provided as a convenience for CkSound::set3dSoundSpeed(). */
    static const float k_soundSpeed_InchesPerSecond;

    /** The speed of sound in dry air at 20 degrees C, in feet per second.
      This value is provided as a convenience for CkSound::set3dSoundSpeed(). */
    static const float k_soundSpeed_FeetPerSecond;

    ////////////////////////////////////////
    // bank sounds

    /** Creates a sound from a bank by index. */
    static CkSound* newBankSound(CkBank*, int index);

    /** Creates a sound from a bank by name. 
      If bank is NULL, all loaded banks are searched for the first matching sound. */
    static CkSound* newBankSound(CkBank*, const char* name);


    ////////////////////////////////////////
    // streams

    /** Creates a stream from a file path. */
    static CkSound* newStreamSound(const char* path, CkPathType = kCkPathType_Default);

    /** Creates a custom stream.
      This could be used, for example, for streaming audio from a proprietary file format. */
    static CkSound* newCustomStreamSound(CkCustomStream*);

#if CK_PLATFORM_IOS
    /** Creates a stream from a URL for an asset in the iTunes library. 
      The URL should be determined using an MPMediaQuery object; see the
      "iPod Library Access Programming Guide" document in the iOS Developer Library.
      Note that this will only work for music files without DRM; for such files the URL will be returned as nil.
      @par Only available on iOS version 4.3 or later.
     */
    static CkSound* newAssetStreamSound(const char* url);
#endif

#if CK_PLATFORM_ANDROID
    /** Creates an HTTP network stream. 
      @par Only available on Android, and only for formats other than .cks. 
     */
    static CkSound* newNetworkStreamSound(const char* url);
#endif


    /** Destroys the sound. */
    void destroy();

private:
    CkSound();
    ~CkSound();
    CkSound(const CkSound&);
    CkSound& operator=(const CkSound&);
};


/** @} */
