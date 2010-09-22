#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
	ENO_INTERFACE_TYPE_BEGIN
		
		interface IReferenceCounter
		{
		protected:
			IReferenceCounter(void) { retain(); }

			virtual ~IReferenceCounter(void) { release(); }

			IReferenceCounter(const IReferenceCounter& rhs) : ref_count(rhs.retain()) { }

			IReferenceCounter& operator = (const IReferenceCounter& rhs) { this->ref_count = rhs.retain(); return *this; }

		public:
			virtual s32 retain( void ) const { return ++ref_count; }

			virtual s32 release( void ) const { return --ref_count; }

			inline s32 getref( void ) const { return ref_count; }

		private:
			mutable s32 ref_count;
		};

		typedef IReferenceCounter ENObject;

		interface IAutoPrt
			: public IReferenceCounter
		{
		public:
			/* virtual */ s32 release( void ) const { if(IReferenceCounter::release() == 0) delete this; return getref(); }
		private:
		};
		
	ENO_INTERFACE_TYPE_END
ENO_NAMESPACE_END