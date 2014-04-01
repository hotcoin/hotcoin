Hotcoin integration/staging tree
================================

http://www.hot-coin.org

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2013-2014 Hotcoin Developers

What is Hotcoin?
----------------

Hotcoin is a lite version of Bitcoin using scrypt as a proof-of-work algorithm.
 - 2 minute block targets
 - subsidy halves in 290k blocks (~4 years)
 - ~29 million total coins

The rest is the same as Bitcoin.
 - 40 coins per block
 - Low difficulty, CPU and GPU both can mining.
 - The whole network within two minutes only accept one block.
 - Prevent mining machine, and smart mining pool.

For more information, as well as an immediately useable, binary version of
the Hotcoin client sofware, see http://www.hot-coin.org.

License
-------

Hotcoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Hotcoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](http://sourceforge.net/mailarchive/forum.php?forum_name=bitcoin-development).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitcoin/bitcoin/tags) are created
regularly to indicate new official, stable release versions of Hotcoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./hotcoin-qt_test

