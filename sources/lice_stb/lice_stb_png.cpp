// Copyright 2021 Jean Pierre Cimalando
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
//

#define STBI_ONLY_PNG
#include "lice_stb_generic.hpp"

LICE_IBitmap *LICE_LoadPNG(const char *filename, LICE_IBitmap *bmp)
{
    return LICE_LoadSTB(filename, bmp);
}

class LICE_stb_PNGLoader
{
    _LICE_ImageLoader_rec rec;

public:
    LICE_stb_PNGLoader()
    {
        rec.loadfunc = loadfunc;
        rec.get_extlist = get_extlist;
        rec._next = LICE_ImageLoader_list;
        LICE_ImageLoader_list = &rec;
    }

    static LICE_IBitmap *loadfunc(const char *filename, bool checkFileName, LICE_IBitmap *bmpbase)
    {
        if (checkFileName) {
            const char *p = filename;
            while (*p)
                p++;
            while (p > filename && *p != '\\' && *p != '/' && *p != '.')
                p--;
            if (stricmp(p, ".png"))
                return nullptr;
        }
        return LICE_LoadSTB(filename, bmpbase);
    }

    static const char *get_extlist()
    {
        return "PNG files (*.PNG)\0*.PNG\0";
    }
};

void lice_stb_install_png_loader()
{
    static LICE_stb_PNGLoader loader;
}
