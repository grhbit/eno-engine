//
//  Unittest.mm
//  Unittest
//
//  Created by seonggwang.gwon on 12. 6. 4..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#import <SenTestingKit/SenTestingKit.h>


@interface Unittest : SenTestCase
@end

#import "enoType.hpp"
#import "enoFile.hpp"

@implementation Unittest

- (void)testEnoType
{
    STAssertTrue(sizeof(eno::u8) == 1,
                 @"eno::u8 must be 1-byte. but real size is %d-byte.",
                 sizeof(eno::u8));
    STAssertTrue(sizeof(eno::s8) == 1,
                 @"eno::s8 must be 1-byte. but real size is %d-byte.",
                 sizeof(eno::s8));
    STAssertTrue(sizeof(eno::c8) == 1,
                 @"eno::c8 must be 1-byte. but real size is %d-byte.",
                 sizeof(eno::c8));
    
    STAssertTrue(sizeof(eno::u16) == 2,
                 @"eno::u16 must be 2-byte. but real size is %d-byte.",
                 sizeof(eno::u16));
    STAssertTrue(sizeof(eno::s16) == 2,
                 @"eno::s16 must be 2-byte. but real size is %d-byte.",
                 sizeof(eno::s16));
    
    STAssertTrue(sizeof(eno::u32) == 4,
                 @"eno::u32 must be 4-byte. but real size is %d-byte.",
                 sizeof(eno::u32));
    STAssertTrue(sizeof(eno::s32) == 4,
                 @"eno::s32 must be 4-byte. but real size is %d-byte.",
                 sizeof(eno::s32));
    
    STAssertTrue(sizeof(eno::u64) == 8,
                 @"eno::u64 must be 8-byte. but real size is %d-byte.",
                 sizeof(eno::u64));
    STAssertTrue(sizeof(eno::s64) == 8,
                 @"eno::s64 must be 8-byte. but real size is %d-byte.",
                 sizeof(eno::s64));
}

- (void)testEnoFile
{
    eno::enoFile file;
    const eno::RString path = "testEnoFile.tmp.txt";
    eno::RString expect;
    
    // write-test
    {
        STAssertTrue(file.open(path, eno::enoFile::WRITE|eno::enoFile::TRUNC),
                     @"enoFile::open(write|trunc mode) test failed. file: %s",
                     path.c_str());
        
        if (file.is_open() == false) {
            STFail(@"Can't process read-test because failed by write-test.");
            return;
        }

        {
            eno::u64 count;
            eno::u64 sumcount = 0;
            eno::RString s; // string
            
            s = "";
            count = file.writeBytes(s.data(), s.length());
            STAssertTrue(s.length() == count,
                         @"%lu != %llu",
                         s.length(), count);
            expect.append(s);
            sumcount += count;

            s = "eno::enoFile-test";
            count = file.writeBytes(s.data(), s.length());
            STAssertTrue(s.length() == count,
                         @"%lu != %llu",
                         s.length(), count);
            expect.append(s);
            sumcount += count;

            char c[] = "\x0\x1\x2\x3\x4\x5\x6\x7";
            count = file.writeBytes(c, sizeof(c)-1);
            STAssertTrue(sizeof(c)-1 == count,
                         @"%lu != %llu",
                         sizeof(c)-1, count);
            expect.append(c, sizeof(c)-1);
            sumcount += count;

            eno::RString d; // delimiter
            d = "|";
            s = "eno::writeLine-delim";

            count = file.writeLine(s, d);
            STAssertTrue(s.length()+d.length() == count,
                         @"%lu != %llu",
                         s.length()+d.length(), count);
            expect.append(s);
            expect.append(d);
            sumcount += count;

            d = "\n";
            s = "eno::write-newline";
            count = file.writeLine(s, d);
            STAssertTrue(s.length()+d.length() == count,
                         @"%lu != %llu",
                         s.length()+d.length(), count);
            expect.append(s);
            expect.append(d);
            sumcount += count;
            
            STAssertTrue(sumcount == expect.length(),
                         @"%llu != %lu(size) (!= %lu(length))",
                         sumcount, expect.size(), expect.length());
            
            STAssertTrue(file.writeByte(0xFF), @"");
            expect.push_back(0xFF);
            ++sumcount;

            STAssertTrue(file.writeByte(0xFE), @"");
            expect.push_back(0xFE);
            ++sumcount;
            
            STAssertTrue(sumcount == expect.length(),
                         @"%llu == %lu(size) (?== %lu(length))",
                         sumcount, expect.size(), expect.length());
        }
        
        file.close();
        
        STAssertFalse(file.is_open(),
                      @"enoFile::close or enoFile::is_open failed. file: %s",
                      path.c_str());
    }
    
    // read-test
    {
        STAssertTrue(file.open(path, eno::enoFile::READ),
                     @"enoFile::open(read mode) test failed. file: %s",
                     path.c_str());
        
        if (file.is_open() == false) {
            STFail(@"Can't process read-test.");
            return;
        }

        {
            eno::u64 count;
            eno::RString line;
            eno::RString result;
            
            if (file.filesize() != expect.size()) {
                STFail(@"%s file is not that our want. can't process read-test. %llu != %lu",
                       path.c_str(), file.filesize(), expect.size());
                
                return;
            }
            
            line.resize(file.filesize());
            count = file.readBytes(line.Buffer(), file.filesize());
            
            STAssertTrue(count == file.filesize(),
                         @"enoFile::readBytes wrong return value");
            
            if (line.Equals(expect) == false) {
                STFail(@"%s file is not that our want. (or write-test failed) can't process read-test",
                       path.c_str());
                
                return;
            }
            
            if (file.seekpos(0) != 0) {
                STFail(@"seek pos 0 failed.");
                return;
            }
            
            count = file.readLine(line, "-test", false);
            STAssertTrue(line == "eno::enoFile",
                         @"enoFile::readLine test failed.");
            STAssertTrue(count == line.size(),
                         @"%llu != %lu", count, line.length());

            char c[] = "\x0\x1\x2\x3\x4\x5\x6\x7";
            line.clear();
            line.resize(sizeof(c)-1);
            count = file.readBytes(line.Buffer(), sizeof(c)-1);
            STAssertTrue(line.compare(0, line.size(), c, sizeof(c)-1) == 0,
                         @"enoFile::readBytes test failed.");
            
            file.readLine(line, "\xFF", true);
            STAssertTrue(line.Equals("eno::writeLine-delim|eno::write-newline\n\xFF"),
                         @"enoFile::readLine test failed.");
            
            eno::u8 byte;
            file.readByte(&byte);
            STAssertTrue(byte == 0xFE, @"enoFile::readByte test failed.");
        }
    }
}

@end
