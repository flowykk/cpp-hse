#include "unixpath.h"

#include <vector>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string_view> all_parts;
    std::vector<std::string_view> current_dirs{current_working_dir, path};

    for (int i = 0; i < current_dirs.size(); ++i) {
        auto dir = current_dirs[i];
        if (!dir.empty() && dir[0] == '/') {
            all_parts.clear();
        }

        size_t fst_slash = 0;
        while (fst_slash != dir.size()) {
            if (dir[fst_slash] != '/') {
                size_t snd_slash = dir.find("/", fst_slash);
                if (snd_slash == std::string_view::npos) {
                    snd_slash = dir.size();
                }

                std::string_view part = dir.substr(fst_slash, snd_slash - fst_slash);
                if (part == ".." && !all_parts.empty()) {
                    all_parts.erase(all_parts.end() - 1);
                }
                if (part != ".." && part != ".") {
                    all_parts.push_back(part);
                }

                fst_slash = snd_slash;
            } else {
                ++fst_slash;
            }
        }
    }

    std::string result;
    for (int i = 0; i < all_parts.size(); ++i) {
        result += "/" + static_cast<std::string>(all_parts[i]);
    }
    if (result.empty()) {
        return "/";
    }

    return result;
}