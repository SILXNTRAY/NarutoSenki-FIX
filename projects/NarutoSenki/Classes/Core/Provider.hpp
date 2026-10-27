#pragma once

// Shinobi
#include "Shinobi/Asuma.hpp"
#include "Shinobi/Chiyo.hpp"
#include "Shinobi/Choji.hpp"
#include "Shinobi/Deidara.hpp"
#include "Shinobi/Gaara.hpp"
#include "Shinobi/Hidan.hpp"
#include "Shinobi/Hinata.hpp"
#include "Shinobi/Hiruzen.hpp"
#include "Shinobi/Ino.hpp"
#include "Shinobi/Itachi.hpp"
#include "Shinobi/Jiraiya.hpp"
#include "Shinobi/Jugo.hpp"
#include "Shinobi/Kakashi.hpp"
#include "Shinobi/Kakuzu.hpp"
#include "Shinobi/Kankuro.hpp"
#include "Shinobi/Karin.hpp"
#include "Shinobi/Kiba.hpp"
#include "Shinobi/Kimimaro.hpp"
#include "Shinobi/Kisame.hpp"
#include "Shinobi/Konan.hpp"
#include "Shinobi/Lee.hpp"
#include "Shinobi/Minato.hpp"
// #include "Shinobi/Nagato.hpp"
#include "Shinobi/Naruto.hpp"
#include "Shinobi/Neji.hpp"
#include "Shinobi/Orochimaru.hpp"
#include "Shinobi/Pain.hpp"
#include "Shinobi/Sai.hpp"
#include "Shinobi/Sakura.hpp"
#include "Shinobi/Sasuke.hpp"
#include "Shinobi/Shikamaru.hpp"
#include "Shinobi/Shino.hpp"
#include "Shinobi/Suigetsu.hpp"
#include "Shinobi/Tenten.hpp"
#include "Shinobi/Tobi.hpp"
#include "Shinobi/Tobirama.hpp"
#include "Shinobi/Tsunade.hpp"

// Bunshin
#include "Shinobi/Bunshin/NarutoClone.hpp"
#include "Shinobi/Bunshin/SageNarutoClone.hpp"
#include "Shinobi/Bunshin/RikudoNarutoClone.hpp"

// Guardian
// Han, Roshi
#include "Guardian/Guardian.hpp"

// Jutsu

// Kuchiyose
#include "Kuchiyose/Akamaru.hpp"
#include "Kuchiyose/Centipede.hpp"
#include "Kuchiyose/DogWall.hpp"
#include "Kuchiyose/Karasu.hpp"
#include "Kuchiyose/Kurama.hpp"
#include "Kuchiyose/Mask.hpp"
#include "Kuchiyose/Parents.hpp"
#include "Kuchiyose/Sanshouuo.hpp"
#include "Kuchiyose/Saso.hpp"
#include "Kuchiyose/Slug.hpp"

#define __begin__ if(0) {}
#define is(var) else if (name == var)
#define is_or(var1, var2) else if (name == var1 || name == var2)
#define is_role(_Role) if (role == _Role)

// TODO: Impl a default AI logic
class DefaultAI : public Hero
{
	void perform() override
	{
	}
};

class Provider
{
public:
	static Hero *create(const string &name, Role role, Group group)
	{
		Hero *ptr;

		__begin__
		is("Akamaru") 						ptr = new Akamaru();
		is("Asuma") 						ptr = new Asuma();
		is("Centipede") 					ptr = new Centipede();
		is("Chiyo") 						ptr = new Chiyo();
		is("Choji") 						ptr = new Choji();
		is("Deidara") 						ptr = new Deidara();
		is("DogWall") 						ptr = new DogWall();
		is("Gaara") 						ptr = new Gaara();
		is("Hidan") 						ptr = new Hidan();
		is("Hinata") 						ptr = new Hinata();
		is("Hiruzen") 						ptr = new Hiruzen();
		is("Ino") 							ptr = new Ino();
		is("Itachi") 						ptr = new Itachi();
		is_or("Jiraiya", "SageJiraiya") 	ptr = new Jiraiya();
		is("Jugo") 							ptr = new Jugo();
		is("Kakashi") 						ptr = new Kakashi();
		is("Kakuzu") 						ptr = new Kakuzu();
		is("Kankuro") 						ptr = new Kankuro();
		is("Karasu") 						ptr = new Karasu();
		is("Karin") 						ptr = new Karin();
		is("Kiba") 							ptr = new Kiba();
		is("Kimimaro") 						ptr = new Kimimaro();
		is("Kisame") 						ptr = new Kisame();
		is("Konan") 						ptr = new Konan();
		is("Kurama") 						ptr = new Kurama();
		is_or("Lee", "RockLee") 			ptr = new Lee();
		is("MaskFuton") 					ptr = new Mask();
		is("MaskKaton") 					ptr = new Mask();
		is("MaskRaiton") 					ptr = new Mask();
		is("Minato") 						ptr = new Minato();
		is("Naruto") 						is_role(Role::Clone) ptr = new NarutoClone();		else ptr = new Naruto();
		is("RikudoNaruto") 					is_role(Role::Clone) ptr = new RikudoNarutoClone();	else ptr = new Naruto();
		is("SageNaruto") 					is_role(Role::Clone) ptr = new SageNarutoClone();	else ptr = new Naruto();
		is("Neji") 							ptr = new Neji();
		is("Orochimaru") 					ptr = new Orochimaru();
		is_or("Pain", "Nagato") 			ptr = new Pain();
		is("AnimalPath") 					ptr = new AnimalPath();
		is("AsuraPath") 					ptr = new AsuraPath();
		is("NarakaPath") 					ptr = new NarakaPath();
		is("PertaPath") 					ptr = new PertaPath();
		is("HumanPath") 					ptr = new HumanPath();
		is("Sai") 							ptr = new Sai();
		is("Sakura") 						ptr = new Sakura();
		is("Sanshouuo") 					ptr = new Sanshouuo();
		is("Saso") 							ptr = new Saso();
		is_or("Sasuke", "ImmortalSasuke") 	ptr = new Sasuke();
		is("Shikamaru") 					ptr = new Shikamaru();
		is("Shino") 						ptr = new Shino();
		is("Slug") 							ptr = new Slug();
		is("Suigetsu") 						ptr = new Suigetsu();
		is("Tenten") 						ptr = new Tenten();
		is("Tobi") 							ptr = new Tobi();
		is("Tobirama") 						ptr = new Tobirama();
		is("Tsunade") 						ptr = new Tsunade();
		is_or("Roshi", "Han")				ptr = new Guardian();
		else								ptr = new DefaultAI();

		if (!ptr)
		{
			CCLOG("Not found character [ %s ]", name.c_str());
			return nullptr;
		}

		if (ptr->init())
		{
			ptr->setID(name, role, group);
			ptr->autorelease();
		}
		else
		{
			CCLOG("Set character %s not found", name.c_str());
			delete ptr;
			ptr = nullptr;
		}
		return ptr;
	}
};

#undef __begin__
#undef is
#undef is_or
#undef is_role
