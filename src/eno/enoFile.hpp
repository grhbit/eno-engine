/*
*  enoFile.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 27..
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
        enum OpenMode {
            READ = 0x01,
            WRITE = 0x02,
            BINARY = 0x04,
            TRUNC = 0x08
        };

        enoFile(void);
        enoFile(const CStdStringA&, s32 Openmode);
        ~enoFile(void);

        void open(const CStdStringA&, s32 Openmode);
        void close(void);

        boolean isOpen(void) const;
        boolean isEOF(void) const;

        s64 getReadTell(void);
        void setReadSeek(u64);

        s64 getWriteTell(void);
        void setWriteSeek(u64);

        u64 getFileSize(void);

        //--- ONLY TEXT MODE
        CString getLine(const CString delimeter = _T("\n"), boolean joinDelimeter = false);

        void write(CString, u64 count = 0);
        void writeLine(const CString str);
        //---

        //--- TEXT & BINARY MODE
        c8 get();
        void read(CString&, u64);
        CString read(u64 readcount);

        void put(c8);
        void writeBytes(const c8*, u64 size);
        //---

        //--- ONLY BINARY MODE
        c8 getch();
        u8 getByte();
        void getBytes(u8*, u64);
        void readBytes(CStdStringA&, u64);
        CStdStringA readBytes(u64 size);

        void putch(c8);
        //---

        void flush(void);
        void flush(boolean autoflush);

    private:
        u64 FillBuffer();
        void WriteProcess(const c8*, u64 size);
        void RefreshFileSize(void);

        enum { BUFFER_SIZE = 1024, WRITE_BUFFER_SIZE = 256 };

        boolean autoflush;
        CString filename;
        c8 buffer[BUFFER_SIZE];
        c8*offset;
        c8*end;
        CString writebuffer;
        s32 mode;
        u64 posg;  // for read, in
        u64 posp;  // for write, out
        u64 filesize;
        FILE* file;
    };

}