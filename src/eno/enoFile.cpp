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

    enoFile::enoFile(void) : file(0), mode(0),
                            autoflush(false), offset(0), end(0),
                            write_end(&writebuffer[WRITE_BUFFER_SIZE]) { }

    enoFile::enoFile(const RString& path, u32 openmode) : file(0), mode(0),
                autoflush(false), offset(0), end(0),
                write_end(&writebuffer[WRITE_BUFFER_SIZE])
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
        
        if (!(openmode & (READ|WRITE|APPEND))) {
            return false;
        }
        
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
            write_offset = writebuffer;
            
            return true;
        }
        
        return false;
    }
    
    bool enoFile::close()
    {
        if (is_open()) {
            if (mode & WRITE) {
                WriteProcess();
            }
            
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
        
        if (readCount != 0) {
            str = out.substr(0, readCount);
        }

        return readCount;
    }
    
    bool enoFile::writeByte(u8 byte)
    {
        if (write_offset == write_end) {
            if(WriteProcess() == 0) {
                return false;
            }
        }
        
        memcpy(write_offset++, &byte, 1);

        if (autoflush) {
            flush();
        }

        return true;
    }
    
    u64 enoFile::writeBytes(const void *bytes, u64 count)
    {
        u64 writeCount = 0;
        const c8* buf = static_cast<const c8*>(bytes);
        
        while (count != 0) {
            u64 writespace = write_end-write_offset;
            if (writespace == 0) {
                if (WriteProcess() != WRITE_BUFFER_SIZE) {
                    writeCount = 0;
                    break;
                }
            }

            if (writespace > count) {
                writespace = count;
            }
            
            memcpy(write_offset, buf+writeCount, writespace);
            write_offset += writespace;
            
            count -= writespace;
            writeCount += writespace;
        }
        
        if (autoflush) {
            flush();
        }

        return writeCount;
    }
    
    u64 enoFile::writeLine(const RString& str, const c8* delim)
    {
        u64 writecount = 0;
        writecount += writeBytes(str.c_str(), str.length());
        writecount += writeBytes(delim, strlen(delim));
        
        if (autoflush) {
            flush();
        }

        return writecount;
    }
    
    bool enoFile::flush()
    {
        if (mode & WRITE) {
            WriteProcess();
            if(fflush(file) != EOF) {
                return true;
            }
        }
        
        return false;
    }
    
    s64 enoFile::seekpos(s64 offset)
    {
        return fseek(file, offset, SEEK_SET);
    }
    
    s64 enoFile::seekcur(s64 offset)
    {
        return fseek(file, offset, SEEK_CUR);
    }
    
    s64 enoFile::filesize()
    {
        if (file == 0) {
            return -1;
        }
        
        s64 size = 0;
        s64 pos = ftell(file);
        fseek(file, 0L, SEEK_END);
        size = ftell(file);
        fseek(file, pos, SEEK_SET);
        
        return size;
    }
    
    u64 enoFile::FillBuffer()
    {
        if (~mode & READ) {
            return 0;
        }
        
        u64 readCount;
        readCount = fread(buffer, sizeof(c8), BUFFER_SIZE, file);

        offset = buffer;
        end = &buffer[readCount];
        
        return readCount;
    }
    
    u64 enoFile::WriteProcess()
    {
        if (~mode & WRITE) {
            return 0;
        }
        
        u64 writeCount;
        writeCount = fwrite(writebuffer, sizeof(c8), write_offset-writebuffer, file);
        
        write_offset = writebuffer;
        
        return writeCount;
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
