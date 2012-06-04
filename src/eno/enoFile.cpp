/*
*  enoFile.cpp
*  eno
*
*  Created by seonggwang.gwon on 12. 2. 27..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "enoFile.hpp"

const eno::c8* mystrnstr(const eno::c8* str, 
                              const eno::c8* substr, 
                              eno::s64 length);

namespace eno {

    enoFile::enoFile(void) : file(0), mode(0), pos(0), size(0),
                                autoflush(false), offset(0), end(0){ }

    enoFile::enoFile(const RString& path, u32 openmode) : file(0), mode(0),
                pos(0), size(0), autoflush(false), offset(0), end(0)
    {
        open(path, openmode);
    }

    enoFile::~enoFile(void)
    {
        close();
    }
    
    bool enoFile::open(const RString & path, u32 openmode)
    {
        close();
        
        char openmode_string[5] = "";
        bool readwrite = (openmode & (READ|WRITE)) == (READ|WRITE);
        
        if (openmode & TRUNC) {
            if ((openmode & APPEND) == APPEND) {
                strcat(openmode_string, "a");
            } else {
                strcat(openmode_string, "w");
            }
        } else {
            strcat(openmode_string, "r");
        }
        
        if (readwrite) {
            strcat(openmode_string, "+");
        }
        
        strcat(openmode_string, "b");
        
        file = fopen(path, openmode_string);
        
        if (is_open()) {
            filename = path;
            mode = openmode;
            
            offset = end = buffer;
            write_offset = write_end = writebuffer;
            
            return true;
        }
        
        return false;
    }
    
    bool enoFile::close()
    {
        if (is_open()) {
            if (fclose(file) == EOF) {
                file = nullptr;
                return false;
            }
        }
        
        file = nullptr;
        return true;
    }
    
    bool enoFile::readByte(void *ch)
    {
        if (offset == end) {
            if(FillBuffer() == 0) {
                return false;
            }
        }
        
        memcpy(ch, offset++, 1);
        
        return true;
    }
    
    u64 enoFile::readBytes(void *dest, u64 count)
    {
        u64 readCount = count;
        c8 *dest_offset = static_cast<c8*>(dest);
        u64 availBufSize;
        
        while (count != 0) {
            availBufSize = end-offset;
            
            if (availBufSize == 0) {
                if (FillBuffer() == 0) {
                    break;
                }
                continue;
            }
            
            if (availBufSize <= count) {
                memcpy(dest_offset, offset, availBufSize);
                count -= availBufSize;
                dest_offset += availBufSize;
                offset += availBufSize;
            } else {
                memcpy(dest_offset, offset, count);
                offset += count;
                count = 0;
            }
        }
        
        return readCount - count;
    }
    
    u64 enoFile::readLine(RString& str, const c8 *delimiter, bool joinDelimiter)
    {
        RString out;
        s64 readCount = 0;
        u64 availBufSize;
        s64 derimsearchoffset = 0;
        const s64 delimLength = strlen(delimiter);
        
        while (true) {
            availBufSize = end-offset;
            
            if (availBufSize == 0) {
                if (FillBuffer() == 0) {
                    break;
                }
                continue;
            }
            
            out.append(offset, availBufSize);

            const c8 *delimoff = mystrnstr(out.c_str()+derimsearchoffset,
                          delimiter,
                          out.size()-derimsearchoffset);
            
            if (delimoff != nullptr) {
                s64 noff = (delimoff-out.c_str());
                noff+=delimLength-readCount;
                offset += noff;
                readCount = (delimoff-out.c_str())+(joinDelimiter?delimLength:0);
                break;
            }
            
            readCount += availBufSize;
            derimsearchoffset = readCount-delimLength;
            offset = end;
        }
        
        str = out.substr(0, readCount);
        return readCount;
    }
    
    bool enoFile::writeByte(c8 byte)
    {
        if ((write_end-writebuffer)>WRITE_BUFFER_SIZE) {
            if(WriteProcess() == 0) {
                return false;
            }
        }
        
        *write_end = byte;
        ++write_end;
        
        return true;
    }
    
    u64 enoFile::writeBytes(c8* bytes, u64 count)
    {
        while (count != 0) {
            if (count > WRITE_BUFFER_SIZE) {
                
            } else {
                
            }
        }
        
        return 0;
    }
    
    u64 enoFile::writeLine(RString& str, const c8* delim)
    {
        //
        u64 writecount;
        writecount = fwrite(str.c_str(), 1, str.size(), file);
        fwrite(delim, 1, strlen(delim), file);
        return writecount + 1;
    }
    
    bool enoFile::flush()
    {
        //
        return fflush(file) != EOF;
    }
    
    s64 enoFile::seekpos(s64 offset)
    {
        if (fseek(file, offset, SEEK_SET) == -1) {
            return -1;
        }
        
        pos = offset;
        return pos;
    }
    
    s64 enoFile::seekcur(s64 offset)
    {
        return seekpos(pos+offset);
    }
    
    u64 enoFile::FillBuffer()
    {
        u64 readCount;
        readCount = fread(buffer, sizeof(c8), BUFFER_SIZE, file);

        offset = buffer;
        end = &buffer[readCount];
        
        return readCount;
    }
    
    u64 enoFile::WriteProcess()
    {
        u64 writeCount;
        writeCount = fwrite(writebuffer, sizeof(c8), write_end-writebuffer, file);
        
        write_end = writebuffer;
        
        return writeCount;
    }
    
    u64 enoFile::RefreshFileSize()
    {
        if(fseek(file, 0, SEEK_END) == -1) {
            return 0;
        }
        
        size = ftell(file);        
        seekpos(pos);
        return size;
    }

}

const eno::c8* mystrnstr(const eno::c8* str, 
                              const eno::c8* substr, 
                              eno::s64 length) {
	if (*str == 0)
        return nullptr;
    
    eno::s32 subLength = strlen(substr);
    
    for (eno::s32 k, j, i = 0; i < length && (str[i] != 0); i++)
    {
        for (k = i, j = 0;
             (k < length) &&
             (j < subLength) &&
             (str[k] == substr[j]); k++, j++);
        
        if (j == subLength) {
            return str+i;
        }
    }
    
	return nullptr;
}
