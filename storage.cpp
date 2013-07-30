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
#include "storage.h"
#include "page_template.h"

Storage::Storage()
{
}

string Storage::encode(const string &str)
{
    const u_char *t = (u_char*)str.c_str();
    u_char * tmp = b.encode(t, str.size());
    u_int size = str.size();
    if (size%8 != 0)
        size += 8-(str.size()%8);
    return hex(tmp, size);
}

string Storage::decode(const string &hex)
{
    string str = bytes(hex);
    const u_char *t = (u_char*)str.c_str();
    return (char*)b.decode(t, (u_int)str.size());
}

string Storage::hex(const u_char* bytes, u_int len)
{
    string res;
    char *buff = new char[len*2+1];
    memset(buff, 0, len*2+1);
    int curr = 0;
    for (int i = 0; i < len; i++)
        curr += sprintf(buff+curr, "%02x",bytes[i]);
    res.assign(buff);
    delete buff;
    return res;
}

string Storage::bytes(const string &hex)
{
    string res;
    for (int i = 0; i < hex.size(); i+=2)
    {
        u_char byte;
        if (hex[i] >= '0' && hex[i] <= '9')
            byte = hex[i] - '0';
        else
            byte = hex[i] - 'a' + 10;
        byte <<= 4;
        if (hex[i+1] >= '0' && hex[i+1] <= '9')
            byte += hex[i+1] - '0';
        else
            byte += hex[i+1] - 'a' + 10;
        res += byte;
    }
    return res;
}

void Storage::setKey(const string &key)
{
   b.init((u_char*)key.c_str(), key.size());
}

void Storage::setFilename(const string &filename)
{
    this->filename = filename;
    ifstream i(filename.c_str());
    if (i.is_open())
        i.close();
    else
        overwriteFile();
}

void Storage::overwriteFile()
{
    ofstream out(filename.c_str(), ios_base::out | ios_base::binary);
    out << page_template;
    out.close();
}

bool Storage::addPassword(const string &site, const string &login, const string &pass)
{
    ofstream out(filename.c_str(), ios_base::app);
    if (!out.is_open())
        return false;
    out << "<script>passwords.push({site: '" << site << "', login: '"
       << login << "', password: '"<< encode(pass) << "'});</script>"<<endl;
    out.close();
    return true;
}


