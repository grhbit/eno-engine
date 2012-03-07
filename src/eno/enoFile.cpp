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

#if defined(ENO_UNICODE)
#if !defined(_tcschr)
#define _tcschr wcschr
#endif
#if !defined(_tcsstr)
#define _tcsstr wcsstr
#endif
#if !defined(_tfopen_s)
#define _tfopen_s _wfopen_s
#endif
#else
#if !defined(_tcschr)
#define _tcschr strchr
#endif
#if !defined(_tcsstr)
#define _tcsstr strstr
#endif
#if !defined(_tfopen_s)
#define _tfopen_s fopen_s
#endif
#endif

namespace eno {

    enoFile::enoFile(void) : file(0), mode(0), posg(0), posp(0), filesize(0), autoflush(false), offset(0), end(0)
    {
    }

    enoFile::enoFile(const CString& path, s32 mode) : file(0), mode(0), posg(0), posp(0), filesize(0), autoflush(false), offset(0), end(0)
    {
        open(path, mode);
    }

    enoFile::~enoFile(void)
    {
        if (isOpen())
            close();
    }

    void enoFile::open( const CString& path, s32 mode_ )
    {
        memset(buffer, 0, sizeof(buffer));
        end = &buffer[BUFFER_SIZE];
        offset = end;

        if(filename.IsEmpty() != true)
            close();

        CString openmode_ = _T("");

        if (mode_ & READ)
            openmode_ += _T("r+");

        if (mode_ & TRUNC)
            openmode_ = _T("w");
// 
//         if (mode_ & WRITE)
//             openmode_ += _T("w+");

        if (mode_ & BINARY)
            openmode_ += _T("b");

        _tfopen_s(&file, path.c_str(), openmode_);
        enoFile::RefreshFileSize();

        if(isOpen()) {
            filename = path;
            mode = mode_;
            if(mode_&READ)
                setReadSeek(0);
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

    s64 enoFile::getReadTell(void)
    {
        if ((mode&READ) && isOpen())
            return ftell(file);

        return -1;
    }

    void enoFile::setReadSeek(u64 pos)
    {
        if ((mode&READ) && isOpen()) {
            fseek(file, pos, FILE_BEGIN);
            posg = pos;
        }
    }

    s64 enoFile::getWriteTell(void)
    {
        if ((mode&WRITE) && isOpen())
            return ftell(file);

        return -1;
    }

    void enoFile::setWriteSeek(u64 pos)
    {
        if ((mode&WRITE) && isOpen()) {
            fseek(file, pos, FILE_BEGIN);
            posp = pos;
        }
    }

    u64 enoFile::getFileSize()
    {
        RefreshFileSize();
        return filesize;
    }

    CString enoFile::getLine( const CString delimeter, boolean joinDelimeter )
    {
        if(mode&BINARY)
            return _T("");

        u64 readcount = 0;
        CString sRet;

        while(true)
        {
            if ((offset == end) == true)
                if(FillBuffer() == 0) // EOF
                    break;

            tchar* pos = _tcsstr(offset, delimeter.c_str());
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

    void enoFile::writeLine(const CString str)
    {
        if((!isOpen()) && (mode&WRITE))
            return;

        if (mode&BINARY)
            return;

        enoFile::WriteProcess(str+_T("\n"), str.size()+1);

        enoFile::RefreshFileSize();
    }

    tchar enoFile::get()
    {
        if (offset == end)
            if(FillBuffer() == 0)
                return 0;

        tchar ret = *offset;
        offset++;

        return ret;
    }

    void enoFile::put(tchar ch)
    {
        enoFile::WriteProcess(&ch, 1);
    }

    void enoFile::read(CString& str, u64 readcount)
    {
        str = read(readcount);
    }

    CString enoFile::read(u64 readcount)
    {
        CString sRet = _T("");

        while(true)
        {
            if (offset == end)
                if(FillBuffer() == 0)
                    return sRet;

            u64 cor = end-offset;
            if (readcount >= (end-offset))
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
        memcpy_s(buff, size, readBytes(size), size);
    }

    void enoFile::readBytes(CStdStringA& str, u64 size)
    {
        str = readBytes(size);
    }

    CStdStringA enoFile::readBytes(u64 size)
    {
        return (read(size));
    }

    void enoFile::writeBytes(const tchar* buffer_, u64 size)
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

        tchar tch = *offset;
        offset++;
        
        return static_cast<c8>(tch);
    }

    void enoFile::putch(c8 ch)
    {
        if (mode&BINARY)
        {
            enoFile::WriteProcess((const tchar*)&ch, 1);
        }
    }

    void enoFile::flush(void)
    {
        if(writebuffer.empty())
            return;

        fwrite(writebuffer.c_str(), writebuffer.size()*sizeof(tchar), writebuffer.size(), file);
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

#if defined(ENO_UNICODE)
        u8 tmpBuf[BUFFER_SIZE];
#else
#define tmpBuf buffer
#endif
        readcount = fread_s(tmpBuf, sizeof(tmpBuf), sizeof(u8), BUFFER_SIZE, file);
        
#if defined(ENO_UNICODE)
        for (u64 i = 0; i<readcount; ++i)
            buffer[i] = tmpBuf[i];
#else
#undef tmpBuf
#endif
        
        if(readcount != BUFFER_SIZE)
            end = buffer + readcount;

        return readcount;
    }

    void enoFile::WriteProcess(const tchar* str, u64 size)
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
        fseek(file, 0, FILE_BEGIN);
        begin = ftell(file);
        fseek(file, 0, FILE_END);
        end = ftell(file);

        filesize = end-begin;

        fseek(file, posg, FILE_BEGIN);
    }

}