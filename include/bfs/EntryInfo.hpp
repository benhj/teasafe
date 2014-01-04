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

#ifndef BFS_ENTRY_INFO_HPP__
#define BFS_ENTRY_INFO_HPP__

#include "bfs/EntryType.hpp"

#include <string>

namespace bfs
{

    class EntryInfo
    {
      public:
        EntryInfo(std::string const &fileName,
                  uint64_t const &fileSize,
                  EntryType const &entryType,
                  bool const writable,
                  uint64_t const firstFileBlock,
                  uint64_t const folderIndex);

        std::string filename() const;

        uint64_t size() const;

        EntryType type() const;

        bool writable() const;

        uint64_t firstFileBlock() const;

        uint64_t folderIndex() const;

      private:
        std::string m_fileName;
        uint64_t m_fileSize;
        EntryType m_entryType;
        bool m_writable;
        uint64_t m_firstFileBlock;
        uint64_t m_folderIndex;
    };

}

#endif // BFS_ENTRY_INFO_HPP__
