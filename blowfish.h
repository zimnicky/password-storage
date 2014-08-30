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
#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <string>
#include <string.h>
#include <algorithm>

using std::string;

class Blowfish
{
    static const unsigned char N = 16;
    // mantissa Pi
    static const u_int ORIG_P[N + 2];
    static const u_int ORIG_S[4][256];

    // round keys
    u_int P[N + 2];
    // S-blocks
    u_int S[4][256];
    /* encrypts a 64-bit block Feistel network modification
    *  round key is not passed to the function iteration and does exclusive or with the left subblock
    */
    void encryptBlock(u_int *high, u_int *low);

    // decrypts 64-bit block (the same, only the round keys in reverse order)
    void decryptBlock(u_int *high, u_int *low);

    // iteration function for a Feistel network
    u_int iterationFunc(u_int x);
public:
    Blowfish();
    void init(const u_char *key, u_int);
    u_char * encode(const u_char *message, u_int);
    u_char * decode(const u_char *message, u_int);

};

#endif // BLOWFISH_H
