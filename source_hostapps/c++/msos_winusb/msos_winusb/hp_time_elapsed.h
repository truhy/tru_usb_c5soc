/*
    MIT License

    Copyright (c) 2024 Truong Hy

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    Version: 20240601
*/

#ifndef HP_TIME_ELAPSED_H
#define HP_TIME_ELAPSED_H

// Generic base class
class hp_time_elapsed_base{
public:
    virtual void set_begin_point() = 0;
    virtual void set_end_point() = 0;
    virtual double elapsed_x() = 0;
    virtual double elapsed_us() = 0;
    virtual double elapsed_ms() = 0;
    virtual double elapsed_s() = 0;
};

// ============
// Windows code
// ============

#if defined(WIN32) || defined(WIN64)

#include <windows.h>

// Stop watch class, typically accurate to microseconds
class hp_time_elapsed : public hp_time_elapsed_base{
protected:
    LARGE_INTEGER m_time_begin;
    LARGE_INTEGER m_time_end;
    LARGE_INTEGER m_time_freq;
    LARGE_INTEGER m_time_elapsed;
    double m_time_elapsed_us;
    double m_time_elapsed_ms;
    double m_time_elapsed_sec;

public:
    hp_time_elapsed() :
        m_time_elapsed_us(0),
        m_time_elapsed_ms(0),
        m_time_elapsed_sec(0){
        m_time_begin.QuadPart = 0;
        m_time_end.QuadPart = 0;
        m_time_freq.QuadPart = 0;
        m_time_elapsed.QuadPart = 0;
    }

    void set_begin_point(){
		QueryPerformanceFrequency(&m_time_freq);
        QueryPerformanceCounter(&m_time_begin);
    }

    void set_end_point(){
        QueryPerformanceCounter(&m_time_end);

        m_time_elapsed.QuadPart = m_time_end.QuadPart - m_time_begin.QuadPart;
        m_time_elapsed_us = m_time_elapsed.QuadPart / ((double)m_time_freq.QuadPart / 1000000);  // Convert to microsecs
        m_time_elapsed_ms = m_time_elapsed.QuadPart / ((double)m_time_freq.QuadPart / 1000);  // Convert to millisecs
        m_time_elapsed_sec = m_time_elapsed.QuadPart / (double)m_time_freq.QuadPart;  // Convert to seconds
    }

    double elapsed_x(){
        return (double)m_time_elapsed.QuadPart;
    }

    double elapsed_us(){
        return m_time_elapsed_us;
    }

    double elapsed_ms(){
        return m_time_elapsed_ms;
    }

    double elapsed_s(){
        return m_time_elapsed_sec;
    }
};

// Alternative stop watch class, typically accurate to microseconds
class hp_time_elapsed2 : public hp_time_elapsed_base{
protected:
    FILETIME m_time_begin;
    FILETIME m_time_end;
    ULARGE_INTEGER m_time_begin2;
    ULARGE_INTEGER m_time_end2;
    ULARGE_INTEGER m_time_elapsed;
    double m_time_elapsed_us;
    double m_time_elapsed_ms;
    double m_time_elapsed_sec;

public:
    hp_time_elapsed2() :
        m_time_elapsed_us(0),
        m_time_elapsed_ms(0),
        m_time_elapsed_sec(0){
        m_time_begin.dwLowDateTime = 0;
        m_time_begin.dwHighDateTime = 0;
        m_time_end.dwLowDateTime = 0;
        m_time_end.dwHighDateTime = 0;
        m_time_begin2.QuadPart = 0;
        m_time_end2.QuadPart = 0;
        m_time_elapsed.QuadPart = 0;
    }

    void set_begin_point(){
        GetSystemTimeAsFileTime(&m_time_begin);

        m_time_begin2.LowPart = m_time_begin.dwLowDateTime;
        m_time_begin2.HighPart = m_time_begin.dwHighDateTime;
    }

    void set_end_point(){
        GetSystemTimeAsFileTime(&m_time_end);

        m_time_end2.LowPart = m_time_end.dwLowDateTime;
        m_time_end2.HighPart = m_time_end.dwHighDateTime;

        m_time_elapsed.QuadPart = m_time_end2.QuadPart - m_time_begin2.QuadPart;
        m_time_elapsed_us = m_time_elapsed.QuadPart / (double)10;  //Convert 100-nanosecs to microsecs.
        m_time_elapsed_ms = m_time_elapsed.QuadPart / (double)10000;  //Convert 100-nanosecs to millisecs.
        m_time_elapsed_sec = m_time_elapsed.QuadPart / (double)10000000;  //Convert 100-nanosecs to seconds.
    }

    double elapsed_x(){
        return (double)m_time_elapsed.QuadPart;
    }

    double elapsed_us(){
        return m_time_elapsed_us;
    }

    double elapsed_ms(){
        return m_time_elapsed_ms;
    }

    double elapsed_s(){
        return m_time_elapsed_sec;
    }
};

// ==========
// Linux code
// ==========

#else

#include <sys/time.h>

// Stop watch class, typically accurate to microseconds
class hp_time_elapsed : public hp_time_elapsed_base{
protected:
    struct timeval m_time_begin;
    struct timeval m_time_end;
    struct timeval m_time_elapsed;
    double m_time_elapsed_us;
    double m_time_elapsed_ms;
    double m_time_elapsed_sec;

public:
    void set_begin_point(){
        gettimeofday(&m_time_begin, NULL);
    }

    void set_end_point(){
        gettimeofday(&m_time_end, NULL);

        m_time_elapsed.tv_sec = m_time_end.tv_sec - m_time_begin.tv_sec;
        m_time_elapsed.tv_usec = m_time_end.tv_usec - m_time_begin.tv_usec;
        m_time_elapsed_us = (double)m_time_elapsed.tv_sec * 1000000 + (double)m_time_elapsed.tv_usec;
        m_time_elapsed_ms = (double)m_time_elapsed.tv_sec * 1000 + ((double)m_time_elapsed.tv_usec / 1000);
        m_time_elapsed_sec = (double)m_time_elapsed.tv_sec + ((double)m_time_elapsed.tv_usec / 1000000);
    }

    double elapsed_x(){
        return m_time_elapsed_us;
    }

    double elapsed_us(){
        return m_time_elapsed_us;
    }

    double elapsed_ms(){
        return m_time_elapsed_ms;
    }

    double elapsed_s(){
        return m_time_elapsed_sec;
    }
};

#endif

#endif
