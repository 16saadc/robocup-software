#include "Offense.hpp"

using namespace std;

Gameplay::Plays::Offense::Offense(GameplayModule *gameplay):
	Play(gameplay, 4),
	_fullback1(gameplay, Behaviors::Fullback::Left),
	_fullback2(gameplay, Behaviors::Fullback::Left),
	_kicker1(gameplay),
	_kicker2(gameplay)
{
	_fullback1.otherFullbacks.insert(&_fullback2);
	_fullback2.otherFullbacks.insert(&_fullback1);
}

bool Gameplay::Plays::Offense::applicable()
{
	bool refApplicable =_gameplay->state()->gameState.playing();
	bool gameplayApplicable = _gameplay->state()->stateID.posession == Packet::LogFrame::OFFENSE ||
						      _gameplay->state()->stateID.posession == Packet::LogFrame::FREEBALL;

	return refApplicable && gameplayApplicable;
}

bool Gameplay::Plays::Offense::assign(set<Robot *> &available)
{
	if(!_kicker1.assign(available)){return false;};
	if(!_kicker2.assign(available)){return false;};
	if(!_fullback1.assign(available)){return false;};
	if(!_fullback2.assign(available)){return false;};

	_robots.insert(_kicker1.robot());
	_robots.insert(_kicker2.robot());
	_robots.insert(_fullback1.robot());
	_robots.insert(_fullback2.robot());

	return _robots.size() >= _minRobots;
}

bool Gameplay::Plays::Offense::run()
{
	_kicker1.run();
	_kicker2.run();
	_fullback1.run();
	_fullback2.run();
	
	return true;
}
