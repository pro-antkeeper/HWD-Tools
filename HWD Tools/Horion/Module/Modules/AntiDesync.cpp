#include "AntiDesync.h"

using namespace std;

AntiDesync::AntiDesync() : IModule(0, Category::PLAYER, "Prevents you from getting desynced on servers")
{
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry(EnumEntry("Normal", 0));
	mode.addEntry(EnumEntry("Nukkit", 1));
}
AntiDesync::~AntiDesync()
{
}

const char* AntiDesync::getRawModuleName()
{
	return "AntiDesync";
}
const char* AntiDesync::getModuleName()
{
	std::string name = "AntiDesync";
	switch (mode.selected)
	{
	case 0:
		name = string("AntiDesync ") + string(GRAY) + string("Normal");
		break;
	case 1:
		name = string("AntiDesync ") + string(GRAY) + string("Nukkit");
		break;
	}
	return name.c_str();
}
void AntiDesync::onSendPacket(C_Packet* packet)
{
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (packet->isInstanceOf<PlayerAuthInputPacket>())
	{

		// * the normal mode is in other hacks lelz
		// * List of Hacks that support AntiDesync:
		// *
		// * Aura // Killaura
		// * AutoCrystal // CrystalPlace
		// * CrystalAura // CrystalBreak
		// * AutoCrystalOld // CrystalAuraGK
		// TODO: Add support for sprint(stops sprinting when eating), tho nukkit mode does the job already
		// TODO: add support for surround to stop surrounding when eating and vice versa

		// * Nukkit Mode
		// * Stops sprinting when eating
		// ? in some nukkit servers you cant eat whilst sprinting, havent found an actual bypass so this is a nice workaround
		if (mode.selected == 1)
		{
			auto player = g_Data.getLocalPlayer();
			if ((player->getSelectedItemId() == 259 && g_Data.isRightClickDown()) || (player->getSelectedItemId() == 300 && g_Data.isRightClickDown()))
			{
				player->setSprinting(false);
			}
		}
	}
}