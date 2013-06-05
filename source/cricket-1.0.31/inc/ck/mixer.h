// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */
/** @defgroup CkMixer CkMixer */
/** @{ */

#pragma once
#include "ck/platform.h"
#include <stddef.h>


/** A "mixer" represents a hierarchical grouping of sounds for controlling volumes. */

class CkMixer
{
public:
    /** Set the name of the mixer.
      The name should be 31 characters or less. */
    void setName(const char*);

    /** Get the name of the mixer. */
    const char* getName() const;


    /** Set the local volume.
      (The actual volume used during mixing will also depend on ancestors.) */
    void setVolume(float);

    /** Get the local volume.
      (The actual volume used during mixing will also depend on ancestors.) */
    float getVolume() const;


    /** Gets the  volume used for mixing (affected by ancestors). */
    float getMixedVolume() const;


    /** Set the parent of the mixer.
      Setting to NULL sets the master mixer as the parent. */
    void setParent(CkMixer*);

    /** Get the parent of the mixer. */
    CkMixer* getParent();


    /** Returns the master mixer, which is the root of the mixer hierarchy. */
    static CkMixer* getMaster();

    /** Creates a new mixer. */
    static CkMixer* newMixer(const char* name, CkMixer* parent = NULL);

    /** Finds a mixer by name; returns NULL if not found. */
    static CkMixer* find(const char* name);


    /** Destroys the mixer. */
    void destroy();

private:
    CkMixer();
    ~CkMixer();
    CkMixer(const CkMixer&);
    CkMixer& operator=(const CkMixer&);
};

/** @} */
