//
//  enoIOTest.cpp
//  eno
//
//  Created by GWON SEONG GWANG on 12. 4. 13..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#include "enoUnitTest.h"
#include "enoFile.hpp"

namespace  {
    TEST(FileIOTest)
    {
        eno::RString filename = "FileIOTest.tmp";
        eno::CString testLine = "eno::enoFile FileIOTest";
        
        eno::enoFile file;
        file.open(filename, eno::enoFile::WRITE);
        CHECK(file.isOpen());
        
        if(file.isOpen())
        {
            file.writeLine(testLine);
            file.close();
            
            CHECK(!file.isOpen());
        }
        
        if (!file.isOpen()) {
            file.open(filename, eno::enoFile::READ);
            CHECK(file.isOpen());
            
            CHECK_EQUAL(testLine, file.getLine());
            
            file.close();
            CHECK(!file.isOpen());
        }
    }
}