#ifndef BFS_MAKE_BFS_HPP__
#define BFS_MAKE_BFS_HPP__

#include "BFSImageStream.hpp"
#include "DetailBFS.hpp"
#include "DetailFileBlock.hpp"
#include "FileBlock.hpp"
#include "FolderEntry.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

namespace bfs
{

    class MakeBFS
    {
      public:

        MakeBFS(std::string const &imageName, uint64_t const blocks)
        {
            buildImage(imageName, blocks);
        }

      private:
        MakeBFS(); // not required

        void buildBlockBytes(uint64_t const fsSize, uint8_t sizeBytes[8])
        {
            detail::convertUInt64ToInt8Array(fsSize, sizeBytes);
        }

        void buildFileCountBytes(uint64_t const fileCount, uint8_t sizeBytes[8])
        {
            detail::convertUInt64ToInt8Array(fileCount, sizeBytes);
        }

        void writeOutFileSpaceBytes(uint64_t const fileBlockCount, BFSImageStream &out)
        {
            for (uint64_t i(0); i < fileBlockCount ; ++i) {
                std::vector<uint8_t> ints;
                ints.assign(detail::FILE_BLOCK_SIZE, 0);
                (void)out.write((char*)&ints.front(), detail::FILE_BLOCK_SIZE);
            }
        }

        void zeroOutBits(std::vector<uint8_t> &bitMapData)
        {
            uint8_t byte;
            for (int i = 0; i < 8; ++i) {
                detail::setBitInByte(byte, i, false);
            }
            bitMapData.push_back(byte);
        }

        /**
         *
         * @param blocks
         */
        void createVolumeBitMap(uint64_t const blocks, BFSImageStream &out)
        {
            //
            // each block will be represented by a bit. If allocated this
            // bit will be set to 1. If not allocated it will be set to 0
            // So we need blocks bits
            // Store the bits in uint8_t. Each of these is a byte so we need
            // blocks divided by 8 to get the number of bytes required.
            // All initialized to zero
            //
            uint64_t bytesRequired = blocks / uint64_t(8);
            std::vector<uint8_t> bitMapData;
            for (uint64_t b = 0; b < bytesRequired; ++b) {
                zeroOutBits(bitMapData);
            }
            (void)out.write((char*)&bitMapData.front(), bytesRequired);
        }

        /**
         * @brief build the file system image
         *
         * The first 8 bytes will represent the number of blocks in the FS
         * The next blocks bits will represent the volume bit map
         * The next 8 bytes will represent the total number of files
         * The next data will be metadata computed as a fraction of the fs
         * size and number of blocks
         * The remaining bytes will be reserved for actual file data 512 byte blocks
         *
         * @param imageName the name of the image
         * @param blocks the number of blocks in the file system
         */
        void buildImage(std::string const &imageName, uint64_t const blocks)
        {

            //
            // store the number of blocks in the first 8 bytes of the superblock
            //
            uint8_t sizeBytes[8];
            buildBlockBytes(blocks, sizeBytes);

            // write out size, and volume bitmap bytes

            BFSImageStream out(imageName, std::ios::out | std::ios::binary);
            out.write((char*)sizeBytes, 8);
            createVolumeBitMap(blocks, out);

            // file count will always be 0 upon initialization
            uint64_t fileCount(0);
            uint8_t countBytes[8];
            buildFileCountBytes(fileCount, countBytes);

            // write out file count
            out.write((char*)countBytes, 8);

            // write out the file space bytes
            writeOutFileSpaceBytes(blocks, out);

            out.flush();
            out.close();


            // create the root folder directory. Calling this constructor will
            // automatically set the initial root block and set the initial
            // number of entries to zero. Note, the initial root block will
            // always be block 0
            FolderEntry rootDir(imageName, blocks, "root");
        }
    };
}

#endif // BFS_MAKE_BFS_HPP__
