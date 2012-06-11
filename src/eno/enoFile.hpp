/*
*  enoFile.hpp
*  eno
*
*  Created by seonggwang.gwon on 12. 2. 27..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoType.hpp"
#include <cstdio>

namespace eno {

    class enoFile
    {
    public:
        enum OpenMode : unsigned int {
            READ = 0x01,
            WRITE = 0x02,
            TRUNC = 0x04,
            APPEND = 0x08|TRUNC,
        };

        enoFile();
        enoFile(const RString&, u32 Openmode);
        ~enoFile();
        
        bool open(const RString&, u32 Openmode);
        bool close();
        bool is_open() const { return file != nullptr; }
        
        bool readByte(void*);
        u64 readBytes(void*, u64);
        u64 readLine(RString&, const c8* delim = "\n", bool joinDelim = false);
        
        bool writeByte(u8);
        u64 writeBytes(const void*, u64);
        u64 writeLine(const RString&, const c8* delim = "\n");

        bool flush(void);
        bool flush(bool auto_flush) { autoflush = auto_flush; return flush(); } 
        
        s64 seekpos(s64 offset);
        s64 seekcur(s64 offset);
        
        s64 tell() const;
        
        s64 filesize();
    private:
        u64 FillBuffer();
        u64 WriteProcess();

        enum { READ_BUFFER_SIZE = 1024, WRITE_BUFFER_SIZE = 256 };

        bool autoflush;
        RString filename;

        c8 read_buffer[READ_BUFFER_SIZE];
        c8*read_offset;
        c8*read_end;
        
        c8 write_buffer[WRITE_BUFFER_SIZE];
        c8*write_offset;
  const c8*write_end;
        
        u32 mode;
        FILE* file;
    };
    
	/*
    using OpenMode = enoFile::OpenMode;
	*/
}