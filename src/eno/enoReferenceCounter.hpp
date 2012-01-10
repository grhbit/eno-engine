/*
 *  enoReferenceCounter.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 9. 23..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoType.hpp"

ENO_NAMESPACE_BEGIN
	ENO_INTERFACE_TYPE_BEGIN

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
			enoReferenceCounter(void):ref_count(0) { retain(); }

			virtual ~enoReferenceCounter(void) { release(); }

			enoReferenceCounter(const enoReferenceCounter& rhs) : ref_count(rhs.retain()) { }

			enoReferenceCounter& operator = (const enoReferenceCounter& rhs) { this->ref_count = rhs.retain(); return *this; }

		public:
			virtual s32 retain( void ) const { return ++ref_count; }

			virtual s32 release( void ) const { return --ref_count; }

			inline s32 refCount( void ) const { return ref_count; }

		private:
			mutable s32 ref_count;
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
            enoAutoPtr( boolean delayCreation )
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
            enoAutoPtr_( boolean delayCreation, _Ty* (*createFunction)(void), void (*destroyFunction)(void) )
            :instance(nullptr), create(createFunction), destroy(destroyFunction)
            {
                if (!delayCreation) {
                    instance = create();
                }
            }
            
            ~enoAutoPtr_( void ) { release(); }

        private:
            mutable _Ty* instance;
            _Ty* (*create)();
            void (*destroy)();
        };

	ENO_INTERFACE_TYPE_END
ENO_NAMESPACE_END