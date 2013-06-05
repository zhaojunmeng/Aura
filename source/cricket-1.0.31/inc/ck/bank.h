// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */
/** @defgroup CkBank CkBank */
/** @{ */

#pragma once
#include "ck/platform.h"
#include "ck/pathtype.h"


/** A bank of memory-resident sounds. */

class CkBank
{
public:
    /** Returns true when an asynchronously loaded bank has finished loading. */
    bool isLoaded() const;

    /** Returns true if an asynchronously loaded bank had an error during loading. */
    bool isFailed() const;

    /** Returns the name of the bank. */
    const char* getName() const;

    /** Returns the number of sounds in the bank. */
    int getNumSounds() const;

    /** Returns the name of a sound in this bank.
      The name will be 31 characters or less. */
    const char* getSoundName(int index) const;


    ////////////////////////////////////////

    /** Loads a bank. 

      This may return NULL if the bank cannot be loaded.
      When loading a bank asynchronously, you should also check isFailed()
      after loading to make sure no errors occurred.
     */
    static CkBank* newBank(const char* path, CkPathType = kCkPathType_Default);

    /** Loads a bank asynchronously. 

      This may return NULL if the bank cannot be loaded.
      When loading a bank asynchronously, you should also check isFailed()
      after loading to make sure no errors occurred.
      */
    static CkBank* newBankAsync(const char* path, CkPathType = kCkPathType_Default);

    /** Loads a bank from a memory buffer. 

      The buffer should contain entire bank file; you are responsible for
      freeing the memory after the bank is deleted. 

      This may return NULL if the bank cannot be loaded.
      When loading a bank asynchronously, you should also check isFailed()
      after loading to make sure no errors occurred.
      */
    static CkBank* newBankFromMemory(void*, int bytes);


    /** Finds a loaded bank by name; returns NULL if not found. */
    static CkBank* find(const char* bankName);

    /** Destroys the bank. */
    void destroy();

private:
    CkBank();
    ~CkBank();
    CkBank(const CkBank&);
    CkBank& operator=(const CkBank&);

};

/** @} */
