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
#include <iostream>
#include <locale>
#include <cstdio>
#include <signal.h>
#include <termios.h>
#include "storage.h"

using namespace std;

const char *help_message = "commands:\n help: shows this message\n add: to add password to storage\n \
key: to change current secret key\n filename: to set or change current file\n exit: to exit program";

// params:
bool help = false;                  // --help
string filename;

Storage storage;

void readParam(char *param)
{
    if (param == "--help")
        help = true;
    else
        filename = param;
    return;
}

string readPassword(string message)
{
    struct termios oldsettings, newsettings;
    sigset_t newsigset, oldsigset;
    sigemptyset(&newsigset);
    sigaddset(&newsigset, SIGINT);
    sigaddset(&newsigset, SIGTSTP);
    sigprocmask(SIG_BLOCK, &newsigset, &oldsigset);
    tcgetattr(fileno(stdin), &oldsettings);
    newsettings = oldsettings;
    newsettings.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), TCSAFLUSH, &newsettings);
    cout << message;
    string pass;
    getline(cin, pass, '\n');
    tcsetattr(fileno(stdin), TCSANOW, &oldsettings);
    sigprocmask(SIG_SETMASK, &oldsigset, NULL);
    return pass;
}

void addPassDialog()
{
    string site, login, pass, pass1;
    cout << "Site: ";
    getline(cin, site, '\n');
    cout << "Username: ";
    getline(cin, login, '\n');
    bool good = false;
    while (!good)
    {
        pass = readPassword("Password: ");
        pass1 = readPassword("\nConfirm password: ");
        good = pass == pass1;
    }
    if (!storage.addPassword(site, login, pass))
    {
        storage.overwriteFile();
        if (!storage.addPassword(site, login, pass))
            cout << "\nOperation failed." << endl;
    }
    else
        cout << "\nPassword added." << endl;
}

void changeFilenameDialog()
{
    cout << "Filename: ";
    getline(cin, filename, '\n');
    storage.setFilename(filename);
    cout << "Filename changed";
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"C");
    if (argc <= 1) help = true;
    int curr_param = 2;
    while (curr_param < argc)
    {
        readParam(argv[curr_param]);
        curr_param++;
    }

    storage.setKey(readPassword("Enter secret key: "));
    if (filename.empty())
    {
        cout << endl;
        changeFilenameDialog();
    }
    else
        storage.setFilename(filename);
    string command;
    bool repeat = true;
    while (repeat)
    {
        cout << endl << ">> ";
        getline(cin, command, '\n');
        if (command == "help")
            cout << help_message;
        else if (command == "add")
            addPassDialog();
        else if (command == "key")
        {
            storage.setKey(readPassword("Enter secret key: "));
            cout << "Current secret key changed";
        }
        else if (command == "exit")
            repeat = false;
        else if (command == "filename")
            changeFilenameDialog();
        else
        {
            cout << "Unknown command." << endl;
            cout << help_message;
        }
    }

    return 0;
}

