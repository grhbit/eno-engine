/*
 *  enoDisplay.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 23..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "size2d.hpp"
#include "enoReferenceCounter.hpp"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

			struct displayParameter {
			public:
				displayParameter( void ) : windowed(false), size(0, 0), vsync(false)
				{ }
			
				boolean windowed;
                core::size2d_template<s32> size;
                boolean vsync;
			};

		ENO_STRUCT_TYPE_END

		ENO_INTERFACE_TYPE_BEGIN

			interface enoDisplay
			{
			public:
				virtual ~enoDisplay( void ) { }
				
				enoDisplay( struct_type::displayParameter& param ) { setDisplayParameter(param); }

				void setDisplayParameter( struct_type::displayParameter& param ){ this->param = param; }
				
				void reset( void ) { Destroy(); Create(); }
				void reset( struct_type::displayParameter& param ) { setDisplayParameter(param); reset(); }
			protected:
				virtual void Create( void ) = 0;
				
				virtual void Destroy( void ) = 0;
				
			private:
				struct_type::displayParameter param;
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END