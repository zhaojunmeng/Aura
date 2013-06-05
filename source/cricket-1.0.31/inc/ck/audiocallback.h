// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */
/** @defgroup CkAudioCallback CkAudioCallback */
/** @{ */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/** Callback for audio processing.
  The audio data is signed 8.24 fixed-point values.
  The buf pointer may be NULL, which means there is no audio for this slice. */
typedef void (*CkAudioCallback)(int* buf, int frames, int channels, int sampleRate, void* data);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */

