#include <algorithm>
#include <cmath>
#include <cstdio>
#include <streambuf>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <nowide/args.hpp>
#include <nowide/cstdio.hpp>
#include <nowide/fstream.hpp>
#include <nowide/iostream.hpp>

#include "opencc-t2s.h"

const char *usage = reinterpret_cast<const char *>(u8"用法：\n\t%s font.otd\n");
const char *loadfilefail = reinterpret_cast<const char *>(u8"读取文件 %s 失败\n");

using json = nlohmann::json;

std::string LoadFile(char *u8filename) {
	static char u8buffer[4096];
	nowide::ifstream file(u8filename);
	if (!file) {
		snprintf(u8buffer, sizeof u8buffer, loadfilefail, u8filename);
		nowide::cerr << u8buffer << std::endl;
		throw std::runtime_error("failed to load file");
	}
	std::string result{std::istreambuf_iterator<char>(file),
	                   std::istreambuf_iterator<char>()};
	return result;
}

void Rename(json &base) {
	for (auto &nameTuple : base["name"]) {
		uint16_t nameId = nameTuple["nameID"];
		switch (nameId) {
		case 1:
		case 3:
		case 4:
		case 16:
		case 18:
		case 21:
			nameTuple["nameString"] = std::string(nameTuple["nameString"]) + " (Pseudo-SC)";
			break;
		case 6:
		case 20:
			nameTuple["nameString"] = std::string(nameTuple["nameString"]) + "Pseudo-SC";
			break;
		default:
			break;
		}
	}
}

void Remap(json &base) {
	auto &cmap = base["cmap"];
	for (auto &[trad, simp] : OpenCC_T2S) {
		auto usimp = std::to_string(simp);
		if (cmap.find(usimp) != cmap.end()) {
			auto utrad = std::to_string(trad);
			cmap[utrad] = cmap[usimp];
		}
	}
}

int main(int argc, char *u8argv[]) {
	static char u8buffer[4096];
	nowide::args _{argc, u8argv};

	if (argc != 2) {
		snprintf(u8buffer, sizeof u8buffer, usage, u8argv[0]);
		nowide::cout << u8buffer << std::endl;
		return EXIT_FAILURE;
	}

	json base;
	bool basecff;
	try {
		auto s = LoadFile(u8argv[1]);
		base = json::parse(s);
	} catch (std::runtime_error) {
		return EXIT_FAILURE;
	}

	Rename(base);
	Remap(base);

	std::string out = base.dump();
	FILE *outfile = nowide::fopen(u8argv[1], "wb");
	fwrite(out.c_str(), 1, out.size(), outfile);
	fclose(outfile);
	return 0;
}
