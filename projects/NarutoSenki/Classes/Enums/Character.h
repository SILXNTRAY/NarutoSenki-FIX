#pragma once
#include "Data/Config.h"
#include "Enums/HeroEnum.h"
#include "Enums/HitType.h"
#include "Enums/KugutsuEnum.h"
#include "Enums/ProjectileEnum.h"
#include "Enums/SkillEnum.h"
#include "Enums/SummonEnum.h"
#include "Enums/TowerEnum.h"
#include "Utils/Cocos2dxHelper.hpp"
#include "Utils/Hash.h"

// Roles
#define kRoleCom "Com"
#define kRolePlayer "Player"
#define kRoleTower "Tower"
#define kRoleBullet "Bullet"
// Special
#define kRoleHero "Hero"
// 分身		Clone
#define kRoleClone "Clone"
#define kRoleFlog "Flog"
// 傀儡		Kugutsu
#define kRoleKugutsu "Kugutsu"
#define kRoleMon "Mon"
// 口寄せ	Summon
#define kRoleSummon "Summon"

#define kGroupKonoha "Konoha"
#define kGroupAkatsuki "Akatsuki"

// Tile maps (Made with Tiled)
#define GetMapPath(mapId) format("Maps/{}.tmx", mapId).c_str()
#define GetMapBgPath(mapId) format("Maps/map_bg{}.png", mapId).c_str()

enum class Role : uint8_t
{
	// Hero of Com
	Com,
	// Hero of Player
	Player,
	// Com & Player
	Hero,
	Flog,
	Tower,
	// Projectile
	Bullet,
	// 分身
	Clone,
	// 傀儡
	Kugutsu,
	Mon,
	// 口寄せ
	Summon,
};

enum class Group : uint8_t
{
	Konoha,
	Akatsuki,
};

// Attack button type
enum ABType : uint8_t
{
	NAttack,
	Item1,	  // Item1: Ramen
	GearItem, // Item skill
	GearBtn,  // Gear skill
	SKILL1,
	SKILL2,
	SKILL3,
	OUGIS1,
	OUGIS2,
};

// declare GearButton
enum class GearType : uint8_t
{
	Gear00,
	Gear01,
	Gear02,
	Gear03,
	Gear04,
	Gear05,
	Gear06,
	Gear07,
	Gear08,
	None
};

namespace AttackType
{
	mk_const(nAttack);
	mk_const(aAttack);
} // namespace AttackType

namespace BuffType
{

} // namespace BuffType

namespace FlogEnum
{
	// Konoha Flogs
	mk_const(KotetsuFlog); // LV 1
	mk_const(IzumoFlog);   // LV 2
	mk_const(KakashiFlog); // LV 3

	// Akatsuki Flogs
	mk_const(FemalePainFlog); // LV 1
	mk_const(PainFlog);		  // LV 2
	mk_const(ObitoFlog);	  // LV 3
} // namespace FlogEnum

namespace GuardianEnum
{
	mk_const(Han);
	mk_const(Roshi);
} // namespace GuardianEnum

#define make_path(name, type, ext) "Unit/" type "/" name ext
// Unit path rules
#define mk_ninja_plist(name) make_path(name "/" name, "Ninja", ".plist")
#define mk_flog_plist(name) make_path(name, "Flog", ".plist")
#define mk_guardian_plist(name) make_path(name "/" name, "Guardian", ".plist")
#define mk_kugutsu_plist(name) make_path(name "/" name, "Kugutsu", ".plist")
#define mk_kuchiyose_plist(name) make_path(name "/" name, "Kuchiyose", ".plist")

// Flogs
constexpr auto kFlog_Kotetsu = mk_flog_plist("KotetsuFlog");
constexpr auto kFlog_Izumo = mk_flog_plist("IzumoFlog");
constexpr auto kFlog_Kakashi = mk_flog_plist("KakashiFlog");
constexpr auto kFlog_FemalePain = mk_flog_plist("FemalePainFlog");
constexpr auto kFlog_Pain = mk_flog_plist("PainFlog");
constexpr auto kFlog_Obito = mk_flog_plist("ObitoFlog");
// Guardians
constexpr auto kGuardian_Han = mk_guardian_plist("Han");
constexpr auto kGuardian_Roshi = mk_guardian_plist("Roshi");

enum class ActionFlag : uint32_t
{
	None = 0UL,
	// Basic
	Dead = 1UL << 0UL,
	Idle = 1UL << 1UL,
	Walk = 1UL << 2UL,
	Hurt = 1UL << 3UL,
	AirHurt = 1UL << 4UL,
	Knockdown = 1UL << 5UL,
	Float = 1UL << 6UL,
	NAttack = 1UL << 7UL,
	Skill01 = 1UL << 8UL,
	Skill02 = 1UL << 9UL,
	Skill03 = 1UL << 10UL,
	Skill04 = 1UL << 11UL,
	Skill05 = 1UL << 12UL,
	// Custom Actions
	Spc01 = 1UL << 13UL,
	Spc02 = 1UL << 14UL,
	Spc03 = 1UL << 15UL,
	Spc04 = 1UL << 16UL,
	Spc05 = 1UL << 17UL,
	Spc06 = 1UL << 18UL,
	Spc07 = 1UL << 19UL,
	Spc08 = 1UL << 20UL,
	Spc09 = 1UL << 21UL,
	Spc10 = 1UL << 22UL,
	Spc11 = 1UL << 23UL,
	Spc12 = 1UL << 24UL,
	Spc13 = 1UL << 25UL,
	Spc14 = 1UL << 26UL,
	Spc15 = 1UL << 27UL,
	Spc16 = 1UL << 28UL,
	Spc17 = 1UL << 29UL,
	Spc18 = 1UL << 30UL,
	Spc19 = 1UL << 31UL,
	// NOTE: More should be changed to uint64_t
	// uint32_t::max = (1 << 32) - 1 (max count is 31)
	// uint64_t::max = (1 << 64) - 1 (max count is 63)
	//
	// Spc20 = 1ULL << 32ULL,
	// Spc21 = 1ULL << 33ULL,
	// Spc22 = 1ULL << 34ULL,
	// Spc23 = 1ULL << 35ULL,
	// Spc24 = 1ULL << 36ULL,
	// Spc25 = 1ULL << 37ULL,
	// Spc26 = 1ULL << 38ULL,
	// Spc27 = 1ULL << 39ULL,
	// Spc28 = 1ULL << 40ULL,
	// Spc29 = 1ULL << 41ULL,
	// Spc30 = 1ULL << 42ULL,
};

ACTION_CONSTANT_NS_BEGIN

using namespace HashUtils;

constexpr uint32_t kActionFlagHash[] = {
	hash32("Dead"),
	hash32("Idle"),
	hash32("Walk"),
	hash32("Hurt"),
	hash32("AirHurt"),
	hash32("Knockdown"),
	hash32("Float"),
	hash32("NAttack"),
	hash32("Skill01"),
	hash32("Skill02"),
	hash32("Skill03"),
	hash32("Skill04"),
	hash32("Skill05"),
	hash32("Spc01"),
	hash32("Spc02"),
	hash32("Spc03"),
	hash32("Spc04"),
	hash32("Spc05"),
	hash32("Spc06"),
	hash32("Spc07"),
	hash32("Spc08"),
	hash32("Spc09"),
	hash32("Spc10"),
	hash32("Spc11"),
	hash32("Spc12"),
	hash32("Spc13"),
	hash32("Spc14"),
	hash32("Spc15"),
	hash32("Spc16"),
	hash32("Spc17"),
	hash32("Spc18"),
	hash32("Spc19"),
};

constexpr size_t kActionFlagHashSize = std::size(kActionFlagHash);

static inline ActionFlag string2ActionFlag(const std::string &name) noexcept
{
	auto hash = HashUtils::hash32(name);
	for (size_t i = 0; i < kActionFlagHashSize; i++)
	{
		if (kActionFlagHash[i] == hash)
			return static_cast<ActionFlag>(1 << i);
	}
	return ActionFlag::None;
}

ACTION_CONSTANT_NS_END

enum class HardHurtState : uint8_t
{
	None,
	Catch,	  // Unit caught on the ground
	CatchAir, // Unit is caught in the air
	Stick,
	Stun,
};
