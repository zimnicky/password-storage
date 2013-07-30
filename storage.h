/*
*   Copyright (c) 2013 Pawel Zimnicki(zimnicky@gmail.com)
*
*   This file is part of the password storage.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*   THE SOFTWARE.
*/
#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "blowfish.h"

using namespace std;

class Storage
{
    static const unsigned char page_template[];
    Blowfish b;
    string filename;
    string encode(const string &str);
    string decode(const string &hex);
    string hex(const u_char* bytes, u_int len);
    string bytes(const string &hex);
public:
    Storage();
    void setKey(const string &key);
    void setFilename(const string &filename);
    virtual void overwriteFile();
    virtual bool addPassword(const string &site, const string &login, const string &pass);
    //virtual bool changePassword(const string &site, const string &login, const string &newpass);
    //virtual string getPassword(const string &site, const string &login);
};

#endif // STORAGE_H
