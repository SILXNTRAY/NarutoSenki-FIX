#include "LoadLayer.h"
#include "GameMode/GameModeImpl.h"

LoadLayer::LoadLayer()
{
	loadNum = 0;
	_hudLayer = nullptr;
	_bgLayer = nullptr;
	_hudLayer = nullptr;
	_isHardCoreMode = true;
	_enableGear = true;
}

bool LoadLayer::init()
{
	if (!Layer::init())
		return false;

	// produce the menu_bar
	Sprite *menu_bar_b = Sprite::create("menu_bar2.png");
	menu_bar_b->setAnchorPoint(Vec2(0, 0));
	FULL_SCREEN_SPRITE(menu_bar_b);
	addChild(menu_bar_b, 2);

	Sprite *menu_bar_t = Sprite::create("menu_bar3.png");
	menu_bar_t->setAnchorPoint(Vec2(0, 0));
	menu_bar_t->setPosition(Vec2(0, winSize.height - menu_bar_t->getContentSize().height));
	FULL_SCREEN_SPRITE(menu_bar_t);
	addChild(menu_bar_t, 2);

	Sprite *loading_title = Sprite::createWithSpriteFrameName("loading_title.png");
	loading_title->setAnchorPoint(Vec2(0, 0));
	loading_title->setPosition(Vec2(2, winSize.height - loading_title->getContentSize().height - 2));
	addChild(loading_title, 3);

	// produce the cloud
	Sprite *cloud_left = Sprite::createWithSpriteFrameName("cloud.png");
	cloud_left->setPosition(Vec2(0, 15));
	cloud_left->setFlipX(true);
	cloud_left->setFlipY(true);
	cloud_left->setAnchorPoint(Vec2(0, 0));
	addChild(cloud_left, 1);

	auto cmv1 = MoveBy::create(1, Vec2(-15, 0));
	auto cseq1 = RepeatForever::create(newSequence(cmv1, cmv1->reverse()));
	cloud_left->runAction(cseq1);

	Sprite *cloud_right = Sprite::createWithSpriteFrameName("cloud.png");
	cloud_right->setPosition(Vec2(winSize.width - cloud_right->getContentSize().width,
								  winSize.height - (cloud_right->getContentSize().height + 15)));
	cloud_right->setAnchorPoint(Vec2(0, 0));
	addChild(cloud_right, 1);

	auto cmv2 = MoveBy::create(1, Vec2(15, 0));
	auto cseq2 = RepeatForever::create(newSequence(cmv2, cmv2->reverse()));
	cloud_right->runAction(cseq2);

	const auto &gd = getGameModeHandler()->getGameData();
	_enableGear = gd.enableGear;
	_isHardCoreMode = gd.isHardCore;

	return true;
}

void LoadLayer::preloadIMG()
{
	auto herosDataVector = getGameModeHandler()->getHerosArray();
	int count = herosDataVector.size();
	if (count == 2) // 1v1
		count = 0;
	else if (count == 4) // Boss mode (3v1)
		count = 3;
	else if (count == 5) // Boss mode (4v1)
		count = 4;
	else if (count == 6) // 3v3
		count = 3;
	else if (count == 8) // 4v4
		count = 4;

	int i = 0;
	for (const auto &data : herosDataVector)
	{
		auto name = data.name;
		if (std::find(loadVector.begin(), loadVector.end(), name) == loadVector.end())
		{
			perloadCharIMG(name.c_str());
			loadVector.push_back(name);
		}

		if (i == 0 || (i < count && _enableGear))
			setLoadingAnimation(name.c_str(), i);
		i++;
	}

	if (_isHardCoreMode)
	{
		addSprites(kGuardian_Han);
		addSprites(kGuardian_Roshi);
		KTools::prepareFileOGG(GuardianEnum::Han);
		KTools::prepareFileOGG(GuardianEnum::Roshi);
	}
	addSprites(kFlog_Kotetsu);
	addSprites(kFlog_FemalePain);

	addSprites(kFlog_Izumo);
	addSprites(kFlog_Kakashi);

	addSprites(kFlog_Pain);
	addSprites(kFlog_Obito);

	KTools::prepareFileOGG("Effect");
	KTools::prepareFileOGG("Ougis");

	setRand();
	int num = rand() % 3 + 1;
	Sprite *tips = Sprite::createWithSpriteFrameName(format("tip{}.png", num).c_str());
	tips->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(tips);

	Sprite *loading = Sprite::createWithSpriteFrameName("loading_font.png");
	loading->setPosition(Vec2(winSize.width - 120, 45));
	auto fade = FadeOut::create(1.0f);
	auto fadeseq = RepeatForever::create(newSequence(fade, fade->reverse()));
	addChild(loading);
	loading->runAction(fadeseq);

	scheduleOnce(schedule_selector(LoadLayer::playBGM), 1.0f);
	scheduleOnce(schedule_selector(LoadLayer::onLoadFinish), 3.0f);
}

void LoadLayer::perloadCharIMG(const string &name)
{
	Texture2D::PVRImagesHavePremultipliedAlpha(true);

	auto path = format("Unit/Ninja/{}/{}_Skill.plist", name, name);
	if (FileUtils::sharedFileUtils()->isFileExist(path.c_str()))
		addSprites(path);
	// else
	// CCLOG("Not found file %s", path);

	KTools::prepareFileOGG(name);

	path = format("Unit/Ninja/{}/{}.plist", name, name);
	addSprites(path);
	// Add extra sprites
	if (name == HeroEnum::Jiraiya)
	{
		addSprites(mk_ninja_plist("SageJiraiya"));
		KTools::prepareFileOGG(HeroEnum::SageJiraiya);
	}
	else if (name == HeroEnum::Kankuro)
	{
		addSprites(mk_kugutsu_plist("Karasu"));
		addSprites(mk_kugutsu_plist("Sanshouuo"));
		addSprites(mk_kugutsu_plist("Saso"));
	}
	else if (name == HeroEnum::Chiyo)
	{
		addSprites(mk_kugutsu_plist("Parents"));
	}
	else if (name == HeroEnum::Kakuzu)
	{
		addSprites(mk_kugutsu_plist("MaskRaiton"));
		addSprites(mk_kugutsu_plist("MaskFuton"));
		addSprites(mk_kugutsu_plist("MaskKaton"));
	}
	else if (name == HeroEnum::Naruto)
	{
		addSprites(mk_ninja_plist("RikudoNaruto"));
		addSprites(mk_ninja_plist("SageNaruto"));
		addSprites(mk_kuchiyose_plist("Kurama"));
		KTools::prepareFileOGG(HeroEnum::SageNaruto);
		KTools::prepareFileOGG(HeroEnum::RikudoNaruto);
	}
	else if (name == HeroEnum::Lee)
	{
		addSprites(mk_ninja_plist("RockLee"));
	}
	else if (name == HeroEnum::Tsunade)
	{
		addSprites(mk_kuchiyose_plist("Slug"));
	}
	else if (name == HeroEnum::Kakashi)
	{
		addSprites(mk_kuchiyose_plist("DogWall"));
	}
	else if (name == HeroEnum::Deidara)
	{
		addSprites(mk_kuchiyose_plist("Centipede"));
	}
	else if (name == HeroEnum::Pain)
	{
		addSprites(mk_ninja_plist("AnimalPath"));
		addSprites(mk_ninja_plist("AsuraPath"));
		addSprites(mk_ninja_plist("NarakaPath"));
		// addSprites(mk_ninja_plist("HumanPath"));
		// addSprites(mk_ninja_plist("PertaPath"));
		addSprites(mk_ninja_plist("Nagato"));
		KTools::prepareFileOGG(HeroEnum::Nagato);
	}
	else if (name == HeroEnum::Sasuke)
	{
		addSprites(mk_ninja_plist("ImmortalSasuke"));
		KTools::prepareFileOGG(HeroEnum::ImmortalSasuke);
	}
	else if (name == HeroEnum::Kiba)
	{
		addSprites(mk_kuchiyose_plist("Akamaru"));
	}
}

void LoadLayer::unloadCharIMG(CharacterBase *c)
{
	if (c == nullptr || c->isClone() || c->isSummon())
	{
		return;
	}

	auto name = c->getName();
	auto path = format("Unit/Ninja/{}/{}.plist", name, name);
	removeSprites(path);

	if (c->isPlayerOrCom())
	{
		KTools::prepareFileOGG(name, true);
	}

	if (name == HeroEnum::Jiraiya)
	{
		removeSprites(mk_ninja_plist("SageJiraiya"));
		KTools::prepareFileOGG(HeroEnum::SageJiraiya, true);
	}
	else if (name == HeroEnum::Kankuro)
	{
		removeSprites(mk_kugutsu_plist("Karasu"));
		removeSprites(mk_kugutsu_plist("Sanshouuo"));
		removeSprites(mk_kugutsu_plist("Saso"));
	}
	else if (name == HeroEnum::Kakuzu)
	{
		removeSprites(mk_kugutsu_plist("MaskFuton"));
		removeSprites(mk_kugutsu_plist("MaskRaiton"));
		removeSprites(mk_kugutsu_plist("MaskKaton"));
	}
	else if (name == HeroEnum::Naruto)
	{
		removeSprites(mk_ninja_plist("SageNaruto"));
		removeSprites(mk_ninja_plist("RikudoNaruto"));
		KTools::prepareFileOGG(HeroEnum::SageNaruto, true);
		KTools::prepareFileOGG(HeroEnum::RikudoNaruto, true);
	}
	else if (name == HeroEnum::RockLee)
	{
		removeSprites(mk_ninja_plist("Lee"));
	}
	else if (name == HeroEnum::Lee)
	{
		removeSprites(mk_ninja_plist("RockLee"));
	}
	else if (name == HeroEnum::Sasuke)
	{
		KTools::prepareFileOGG(HeroEnum::ImmortalSasuke, true);
		removeSprites(mk_ninja_plist("ImmortalSasuke"));
	}
	else if (name == HeroEnum::Pain)
	{
		KTools::prepareFileOGG(HeroEnum::Nagato, true);
		removeSprites(mk_ninja_plist("AnimalPath"));
		removeSprites(mk_ninja_plist("AsuraPath"));
		removeSprites(mk_ninja_plist("NarakaPath"));
		// addSprites(mk_ninja_plist("HumanPath"));
		// addSprites(mk_ninja_plist("PertaPath"));
		removeSprites(mk_ninja_plist("Nagato"));
	}
	else if (name == HeroEnum::Nagato)
	{
		removeSprites(mk_ninja_plist("AnimalPath"));
		removeSprites(mk_ninja_plist("AsuraPath"));
		removeSprites(mk_ninja_plist("NarakaPath"));
	}
}

void LoadLayer::unloadAllCharsIMG(const vector<Hero *> &players)
{
	vector<string> unloadVector(players.size());
	for (auto player : players)
	{
		auto name = player->getName();
		if (std::find(unloadVector.begin(), unloadVector.end(), name) == unloadVector.end())
		{
			unloadCharIMG(player);
			unloadVector.push_back(name);
		}
	}
}

void LoadLayer::setLoadingAnimation(const char *player, int index)
{
	auto loadingAvator = Sprite::createWithSpriteFrameName(format("{}_Walk_01", player).c_str());
	loadingAvator->setFlipX(true);
	loadingAvator->setPosition(Vec2(winSize.width - 100 + index * 16, 30));
	loadingAvator->setAnchorPoint(Vec2(0, 0));

	// FIXME: Use the other way get animation frame count
	ssize_t frameCount = is_same(player, HeroEnum::Konan) ? 1 : 7;
	Vector<SpriteFrame *> animeFrames(frameCount);
	for (int i = 1; i < frameCount; i++)
	{
		auto frame = getSpriteFrame("{}_Walk_{:02d}", player, i);
		animeFrames.pushBack(frame);
	}

	auto tempAnimation = Animation::createWithSpriteFrames(animeFrames, 1.0f / 10.0f);
	auto tempAction = Animate::create(tempAnimation);
	auto animAction = RepeatForever::create(tempAction);

	addChild(loadingAvator);
	loadingAvator->runAction(animAction);
}

void LoadLayer::playBGM(float dt)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(LOADING_MUSIC, false);
}

void LoadLayer::preloadAudio()
{
	auto bg_src = _enableGear ? "blue_bg.png" : "red_bg.png";
	Sprite *bgSprite = Sprite::create(bg_src);

	FULL_SCREEN_SPRITE(bgSprite);
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setPosition(Vec2(0, 0));
	addChild(bgSprite, -5);

	preloadIMG();
}

void LoadLayer::onLoadFinish(float dt)
{
	Scene *gameScene = Scene::create();

	_hudLayer = HudLayer::create();

	_gameLayer = GameLayer::create();
	_gameLayer->setHudLayer(_hudLayer);
	_gameLayer->setTotalKills(0);
	_gameLayer->setTotalTime(0);
	_gameLayer->initHeros();

	_bgLayer = BGLayer::create();
	_bgLayer->initBg(_gameLayer->mapId);

	_hudLayer->initHeroInterface();
	_gameLayer->invokeAllCallbacks();

	gameScene->addChild(_bgLayer, kBgOrder);
	gameScene->addChild(_gameLayer, kGameLayerOrder);
	gameScene->addChild(_hudLayer, kHudLayerOrder);

	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, gameScene));
}
