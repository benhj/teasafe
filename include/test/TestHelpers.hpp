/*
Copyright (c) <2013-2014>, <BenHJ>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.
*/

#ifndef BFS_TEST_HELPERS_HPP__
#define BFS_TEST_HELPERS_HPP__

#include "bfs/CoreBFSIO.hpp"
#include "bfs/MakeBFS.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>

#include <string>
#include <vector>

int const HELLO_IT = 1000;
int const BIG_SIZE = HELLO_IT * 13;
int const A_STRING_SIZE = 998;

int testFailures = 0;
int passedPoints = 0;
std::vector<std::string> failingTestPoints;

bfs::CoreBFSIO createTestIO(boost::filesystem::path const &testPath)
{
    bfs::CoreBFSIO io;
    io.path = testPath.string();
    io.blocks = 2048;
    io.password = "abcd1234";
    io.rootBlock = 0;
    return io;
}

inline boost::filesystem::path buildImage(boost::filesystem::path const &path, long const blockCount)
{
    std::string testImage(boost::filesystem::unique_path().string());
    boost::filesystem::path testPath = path / testImage;
    bfs::CoreBFSIO io = createTestIO(testPath);
    bfs::MakeBFS bfs(io);
    return testPath;
}

std::string createLargeStringToWrite(std::string const &val="Hello, World!")
{
    std::string theString("");
    for (int i = 0; i < HELLO_IT; ++i) {
        theString.append(val);
    }
    return theString;
}

std::string createAString()
{
    std::string theString("");
    for (int i = 0; i < A_STRING_SIZE; ++i) {
        theString.append("a");
    }
    return theString;
}

#define ASSERT_EQUAL(A, B, C)                                          \
    if(A == B) {                                                       \
        std::cout<<boost::format("%1% %|100t|%2%\n") % C % "passed";   \
        ++passedPoints;                                                \
    } else {                                                           \
        std::cout<<boost::format("%1% %|100t|%2%\n") % C % "failed";   \
        ++testFailures;                                                \
        failingTestPoints.push_back(C);                                \
    }

#endif
