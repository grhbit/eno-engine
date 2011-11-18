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
		
		interface enoReferenceCounter
		{
		protected:
			enoReferenceCounter(void) { retain(); }

			virtual ~enoReferenceCounter(void) { release(); }

			enoReferenceCounter(const enoReferenceCounter& rhs) : ref_count(rhs.retain()) { }

			enoReferenceCounter& operator = (const enoReferenceCounter& rhs) { this->ref_count = rhs.retain(); return *this; }

		public:
			virtual s32 retain( void ) const { return ref_count++; }

			virtual s32 release( void ) const { return ref_count--; }

			inline s32 refCount( void ) const { return ref_count; }

		private:
			mutable s32 ref_count;
		};

		typedef enoReferenceCounter IReferenceCounter;

		interface enoAutoPtr
			: public enoReferenceCounter
		{
		public:
			/* virtual */ s32 release( void ) const 
            {
                if(this->enoReferenceCounter::release() == 0) 
                    delete this; 
                return refCount(); 
            }
		protected:
			enoAutoPtr( void ) { }
		};

		typedef enoAutoPtr IAutoPtr;
		
	ENO_INTERFACE_TYPE_END
ENO_NAMESPACE_END