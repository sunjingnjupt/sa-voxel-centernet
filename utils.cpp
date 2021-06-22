#include "utils.h"
namespace utils
{
    std::vector<utils::data> ReadKittiBinByPath(const std::string & path)
    {
        fprintf(stderr, "[INFO] start read bin file\n");
        std::vector<utils::data> offsets;
        utils::data* dataVec = offsets.data();
        std::fstream file(path.c_str(), std::ios::in | std::ios::binary);
        if (file.good())
        {
            fprintf(stderr, "[INFO] file %s is good\n", path.c_str());
            file.seekg(0, std::ios::beg);
            utils::data tmpData;
            for (int i = 0; file.good() && !file.eof(); ++i)
            {
                file.read(reinterpret_cast<char*>(&tmpData), sizeof(utils::data));
                offsets.emplace_back(tmpData);
            }
            file.close();
        }
        return offsets;
        fprintf(stderr, "[INFO] end read bin file\n");
    }
};