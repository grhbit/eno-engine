//
//  enoIOTest.cpp
//  eno
//
//  Created by seonggwang.gwon on 12. 4. 13..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#include "enoUnitTest.h"
#include "enoFile.hpp"

namespace  {
    TEST(FileIOTest)
    {
        eno::RString filename = "FileIOTest.tmp";
        eno::RString testLine = "eno::enoFile FileIOTest";
        
        eno::enoFile file;
        file.open(filename, eno::enoFile::WRITE|eno::enoFile::TRUNC);
        CHECK(file.is_open());
        
        if(file.is_open())
        {
            file.writeLine(testLine);
            file.writeLine(testLine);
            file.writeLine(testLine, "|");
            file.writeLine(testLine, "|");
            file.close();
            
            CHECK(!file.is_open());
        }
        
        if (!file.is_open()) {
            file.open(filename, eno::enoFile::READ);
            CHECK(file.is_open());
            
            if (file.is_open() == false) {
                return;
            }
            
            eno::RString line;
            file.readLine(line);
            CHECK_EQUAL(testLine, line);
            file.readLine(line, "ile", true);            
            CHECK(line.Equals("eno::enoFile"));
            file.readLine(line, "\n", false);
            CHECK_EQUAL(line, " FileIOTest");
            file.readLine(line, "|", false);
            CHECK_EQUAL(testLine, line);
            file.readLine(line, "|", true);
            CHECK_EQUAL(testLine+"|", line);

            file.close();
            CHECK(!file.is_open());
        }
    }
}