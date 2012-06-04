/*
*  enoReferenceCounter.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 9. 23..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoType.hpp"

namespace eno {

#ifdef Sealed
#undef Sealed
#endif

interface Sealed
{
protected:
    Sealed(void) { }
};

#define Sealed private virtual Sealed

interface enoReferenceCounter
{
protected:
    enoReferenceCounter(void):refCount_(0) { retain(); }

    virtual ~enoReferenceCounter(void) { release(); }

    enoReferenceCounter(const enoReferenceCounter& rhs) : refCount_(rhs.retain()) { }

    enoReferenceCounter& operator = (const enoReferenceCounter& rhs) { this->refCount_ = rhs.retain(); return *this; }

public:
    virtual s32 retain( void ) const { return ++refCount_; }

    virtual s32 release( void ) const { return --refCount_; }

    inline s32 refCount( void ) const { return refCount_; }

private:
    mutable s32 refCount_;
};

template <typename _Ty>
interface enoAutoPtr : public enoReferenceCounter, Sealed
{
public:
    /* virtual */ s32 release( void ) const 
    {
        if(this->enoReferenceCounter::refCount() == 0) 
        {
            return 0;
        }
        return refCount();
    }
public:
    enoAutoPtr( bool delayCreation )
        :instance(nullptr)
    {
        if (!delayCreation) {
            instance = new _Ty;
        }
    }

    ~enoAutoPtr( void ) { release(); }
private:
    mutable _Ty* instance;
};

template<typename _Ty>
class enoAutoPtr_ : public enoReferenceCounter, Sealed
{
public:
    /* virtual */ s32 release( void ) const
    {
        if (this->enoReferenceCounter::refCount() == 0)
            return 0;

        return refCount();
    }
public:
    enoAutoPtr_( bool delayCreation, _Ty* (*createFunction)(void), void (*destroyFunction)(void) )
        :instance(nullptr), create(createFunction), destroy(destroyFunction)
    {
        if (!delayCreation) {
            instance = create();
        }
    }

    ~enoAutoPtr_( void ) { release(); }

    operator _Ty* () { return instance; }
    operator const _Ty* () const { return instance; }

    _Ty* operator-> () { return instance; }
    const _Ty* operator->() const { return instance; }

private:
    mutable _Ty* instance;
    _Ty* (*create)();
    void (*destroy)();
};

}