#pragma once
#include "Game.h"

struct ScoreEntry {
	time_t time;
	float score;
};

class Highscore
{
public:
	Highscore();
	void add(float score);
	void save();
	void load();
	void draw(RenderWindow& win);
private:
	std::vector<ScoreEntry> entries;
	Font font;
	Text text;
};

