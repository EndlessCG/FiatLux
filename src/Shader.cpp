#include <string>
#include <Shader.h>

std::unordered_map<std::string, Material> MATERIALS = {
        {"EMERALD",
                Material(0.0215, 0.1745, 0.0215,
                         0.07568, 0.61424, 0.07568,
                         0.633, 0.727811, 0.633,
                         76.8)},
        {"JADE",
                Material(0.135, 0.2225, 0.1575,
                         0.54, 0.89, 0.63,
                         0.316228, 0.316228, 0.316228,
                         12.8)},
        {"OBSIDIAN",
                Material(0.05375, 0.05, 0.06625,
                         0.18275, 0.17, 0.22525,
                         0.332741, 0.328634, 0.346435,
                         38.4)},
        {"GOLD",
                Material(0.24725, 0.1995, 0.0745,
                         0.75164, 0.60648, 0.22648,
                         0.628281, 0.555802, 0.366065,
                         51.2)}
};