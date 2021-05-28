#include "Highscore.h"

void Highscore::add(float score)
{
	ScoreEntry entry;
	entry.time = time(NULL);
	entry.score = score;
	entries.push_back(entry);
}

void Highscore::save()
{
}

void Highscore::load()
{
}

void Highscore::draw(RenderWindow& win)
{
}

Highscore::Highscore()
{
}
