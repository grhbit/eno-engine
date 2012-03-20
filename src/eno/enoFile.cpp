/*
*  enoFile.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 27..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "enoFile.hpp"

using namespace std;

namespace eno {

    enoFile::enoFile(void) : file(0), mode(0), seekpos(0), filesize(0), autoflush(false), offset(0), end(0)
    {
    }

    enoFile::enoFile(const RString& path, s32 mode) : file(0), mode(0), seekpos(0), filesize(0), autoflush(false), offset(0), end(0)
    {
        open(path, mode);
    }

    enoFile::~enoFile(void)
    {
        if (isOpen())
            close();
    }

    void enoFile::open( const RString& path, s32 mode_ )
    {
        memset(buffer, 0, sizeof(buffer));
        end = &buffer[BUFFER_SIZE];
        offset = end;

        if(filename.IsEmpty() != true)
            close();

        RString openmode_ = "";

        if (mode_ & READ)
            openmode_ += "r+";

        if (mode_ & TRUNC)
            openmode_ = "w";
// 
//         if (mode_ & WRITE)
//             openmode_ += "w+";

        if (mode_ & BINARY)
            openmode_ += "b";

        file = fopen(path.c_str(), openmode_);
        enoFile::RefreshFileSize();

        if(isOpen()) {
            filename = path;
            mode = mode_;
            if(mode_&READ)
                seek(0);
        }
    }

    void enoFile::close( void )
    {
        enoFile::flush();
        filename.clear();
        fclose(file);
    }

    boolean enoFile::isOpen(void) const
    {
        return file != 0;
    }

    boolean enoFile::isEOF(void) const
    {
        return feof(file);
    }

    s64 enoFile::tell(void)
    {
        if ((mode&READ) && isOpen())
            return ftell(file);

        return -1;
    }

    void enoFile::seek(u64 pos)
    {
        if ((mode&READ) && isOpen()) {
            fseek(file, pos, SEEK_SET);
            seekpos = pos;
        }
    }

    u64 enoFile::getFileSize()
    {
        RefreshFileSize();
        return filesize;
    }

    CString enoFile::getLine( const RString delimeter, boolean joinDelimeter )
    {
        if(mode&BINARY)
            return "";

        RString sRet;

        while(true)
        {
            if ((offset == end) == true)
                if(FillBuffer() == 0) // EOF
                    break;

            c8* pos = strstr(offset, delimeter.c_str());
            if(pos == 0) {
                sRet.append(offset, end - offset);
                offset = end;
            }
            else
            {
                pos += delimeter.size();
                sRet.append(offset, joinDelimeter? (pos - offset):(pos - delimeter.size() - offset));
                offset = pos;
                break;
            }
        }

        return sRet;
    }

    void enoFile::writeLine( const RString str )
    {
        if((!isOpen()) && (mode&WRITE))
            return;

        if (mode&BINARY)
            return;

        enoFile::WriteProcess(str+"\n", str.size()+1);

        enoFile::RefreshFileSize();
    }

    c8 enoFile::get()
    {
        if (offset == end)
            if(FillBuffer() == 0)
                return 0;

        c8 ret = *offset;
        offset++;

        return ret;
    }

    void enoFile::put(c8 ch)
    {
        enoFile::WriteProcess(&ch, 1);
    }

    void enoFile::read(CString& str, u64 readcount)
    {
        str = read(readcount);
    }

    RString enoFile::read(u64 readcount)
    {
        RString sRet = "";

        while(true)
        {
            if (offset == end)
                if(FillBuffer() == 0)
                    return sRet;

            if (readcount >= (end - offset))
            {
                sRet.append(offset, end - offset);
                readcount -= (end - offset);
                offset = end;
            }
            else
            {
                sRet.append(offset, readcount);
                offset += readcount;
                break;
            }
        }

        return sRet;
    }

    u8 enoFile::getByte()
    {
        return static_cast<u8>(enoFile::getch());
    }

    void enoFile::getBytes(u8* buff, u64 size)
    {
        memcpy(buff, readBytes(size), size);
    }

    void enoFile::readBytes(RString& str, u64 size)
    {
        str = readBytes(size);
    }

    RString enoFile::readBytes(u64 size)
    {
        return (read(size));
    }

    void enoFile::writeBytes(const c8* buffer_, u64 size)
    {
        enoFile::WriteProcess(buffer_, size);
    }

    c8 enoFile::getch()
    {
        if (!(mode&BINARY))
            return 0;
        
        if (offset == end)
            if (FillBuffer() == 0)
                return 0;

        c8 tch = *offset;
        offset++;
        
        return static_cast<c8>(tch);
    }

    void enoFile::putch(c8 ch)
    {
        if (mode&BINARY)
        {
            enoFile::WriteProcess((const char*)&ch, 1);
        }
    }

    void enoFile::flush(void)
    {
        if(writebuffer.empty())
            return;

        fwrite(writebuffer.c_str(), writebuffer.size()*sizeof(c8), writebuffer.size(), file);
        writebuffer.clear();
        fflush(file);
    }

    void enoFile::flush(boolean autoflushflag)
    {
        autoflush = autoflushflag;
        enoFile::flush();
    }

    u64 enoFile::FillBuffer()
    {
        if ((!isOpen()) && (mode&READ))
            return 0;

        offset = buffer;
        memset(buffer, 0, sizeof(buffer));
        u64 readcount = 0;

        readcount = fread(buffer, sizeof(c8), BUFFER_SIZE, file);
        
        if(readcount != BUFFER_SIZE)
            end = buffer + readcount;

        return readcount;
    }

    void enoFile::WriteProcess(const char* str, u64 size)
    {
        if ((!isOpen()) && (mode&WRITE))
            return;

        writebuffer.append(str, size);
        if ((writebuffer.size()>=WRITE_BUFFER_SIZE) || autoflush)
        {
            enoFile::flush();
            writebuffer.clear();
        }
    }

    void enoFile::RefreshFileSize(void)
    {
        if (!isOpen())
            return;

        u64 begin, end;
        fseek(file, 0, SEEK_SET);
        begin = ftell(file);
        fseek(file, 0, SEEK_END);
        end = ftell(file);

        filesize = end-begin;

        fseek(file, seekpos, SEEK_SET);
    }

}