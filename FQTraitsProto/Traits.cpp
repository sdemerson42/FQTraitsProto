#include "Traits.h"
#include "HeroBase.h"

void TraitKlepto::initialize(Hero *h) 
{
	h->modAttrib(HeroAttrib::Rogue, rand() % 3 + 3);
}