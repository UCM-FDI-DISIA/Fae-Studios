#pragma once
#include <vector>
#include <array>

class anims {

public:
	class animDescription {
		public:
			animDescription(int tPerFrame, int numFrames, int rowNum, int colNum) : tPerFrame(tPerFrame), numFrames(numFrames), rowNum(rowNum), colNum(colNum) {}
			int tPerFrame;
			int numFrames;
			int rowNum;
			int colNum = 0;
	};
	static enum Entities { OTT_ANIM, MELEE_ANIM, RANGE_ANIM, SLIME_ANIM, EARTH_ANIM };
	static std::vector<std::vector<animDescription>> animations;

private:
	static std::vector<animDescription> ott_anims;
	static std::vector<animDescription> melee_anims;
	static std::vector<animDescription> range_anims;
	static std::vector<animDescription> slime_anims;
	static std::vector<animDescription> earth_anims;
};