Password storage
=======================

This program stores passwords in the file, which can be opened by any device without special software.

This file is html-document with encrypted data and decryption script.

The Blowfish is used for encryption.

## Building

	$ make
	
** Dependencies: ** python 2.6 or later

## Usage

	$ ./storage

Enter secret key & filename. Then use following commands.

**Commands**:

 * add: to add password to storage
 
 * key: to change current secret key
 
 * filename: to set or change current file
 
 * exit: to exit program


## License and copyrights

This software is released under the terms of the [MIT license](https://github.com/pddoz/password-storage/blob/master/LICENSE).