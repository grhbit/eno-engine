/*
 *  enoManager.cpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 11. 1. 19..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "enoManager.h"

ENO_NAMESPACE_BEGIN
	ENO_GAME_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			enoManager* enoManager::instance = nullptr;

			enoManager* enoManager::getInstance( void )
			{
				if (enoManager::instance == nullptr) {
					enoManager::instance = new enoManager;
				}
				
				return enoManager::instance;
			}

			void enoManager::release( void )
			{
				if (enoManager::instance != nullptr) {
					delete enoManager::instance;
					enoManager::instance = nullptr;
				}
			}

		ENO_CLASS_TYPE_END
	ENO_GAME_NAMESPACE_END
ENO_NAMESPACE_END