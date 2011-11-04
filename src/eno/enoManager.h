/*
 *  enoManager.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 11. 1. 19..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "eno.h"

ENO_NAMESPACE_BEGIN
	ENO_GAME_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			class enoManager {
			private:
				static enoManager* instance;

			private:
				enoManager( void ) { }
				
				~enoManager( void ) { }
				
			public:
				
			//public static
			public:
				static enoManager* getInstance( void );

				static void release( void );
			};

		ENO_CLASS_TYPE_END
	ENO_GAME_NAMESPACE_END
ENO_NAMESPACE_END