#include <windows.h>
#include <format>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"

// for debugging the heap corruption at 64 or more cars, no luck so far
//#include "memoryhook.h"

const size_t nNewPlayerStructCustomVarsBegin = 0xF50; // sizeof AIPlayer

int nNumAI = 7;
int nNumAIToSpawn = 7;
int nNumAIProfiles = 7;
int nNumPlayers = 8;
int nNumPlayersForPlayerInfo = 8;
int* nAISortingThing = nullptr;
int* nInitPlayersArray = nullptr;
struct tPlayerSettings {
	uint8_t _0[0x2C];
	uint32_t nPlayerType;
	uint8_t _30[0x14];
};
static_assert(sizeof(tPlayerSettings) == 0x44);
tPlayerSettings* nPlayerSettingsArray = nullptr; // game + 0x5F4
int* nCameraArray43 = nullptr;
int* nCameraArray44 = nullptr;
int* nCameraArray45 = nullptr;
int* nScoreboardArray108 = nullptr;
int* nScoreboardArray110 = nullptr;
int* nSomeRenderArray = nullptr; // scene + 0x1C4
float* nSomeDerbyScoringArray1 = nullptr;
float* nSomeDerbyScoringArray2 = nullptr;
struct tPlayerBonuses {
	uint32_t values[7];
};
struct tScoreboardPlayer {
	uint8_t _0[0x8];
};
tScoreboardPlayer* nPlayerScoreboardArray = nullptr;
int* nSomeCarCollisionArray209AC = nullptr;
int* nSomeCarCollisionArray209E4 = nullptr;
int nSomeCarCollisionArrayMaxCount = 0;
int* nAIPortraitsArray = nullptr; // hud + 0x150

void SetDefaultAISorting() {
	for (int i = 0; i < nNumPlayers; i++) {
		nAISortingThing[i] = i + 1;
	}
}

uintptr_t AISortingThingASM1_jmp = 0x45E2A9;
void __attribute__((naked)) AISortingThingASM1() {
	__asm__ (
		"pushad\n\t"
		"call %2\n\t"
		"popad\n\t"
		"jmp %0\n\t"
			:
			: "m" (AISortingThingASM1_jmp), "m" (nAISortingThing), "i" (SetDefaultAISorting)
	);
}

uintptr_t AISortingThingASM2_jmp = 0x45E382;
void __attribute__((naked)) AISortingThingASM2() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov ecx, [ebp+ebx*4]\n\t"
		"lea eax, [ebp+edx*4]\n\t"
		"mov edx, [eax]\n\t"
		"mov [ebp+ebx*4], edx\n\t"
		"mov [eax], ecx\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (AISortingThingASM2_jmp), "m" (nAISortingThing)
	);
}

uintptr_t AISortingThingASM3_jmp = 0x45E3A0;
void __attribute__((naked)) AISortingThingASM3() {
	__asm__ (
		"mov eax, [esi+0x9BC]\n\t"
		"mov ecx, %1\n\t"
		"sub ecx, eax\n\t"
		"mov edx, ebp\n\t"
		"mov edi, edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (AISortingThingASM3_jmp), "m" (nAISortingThing)
	);
}

uintptr_t InitPlayersASM1_jmp = 0x470C8E;
void __attribute__((naked)) InitPlayersASM1() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"lea edx, [ecx+eax*4]\n\t"
		"mov edx, [ebp+edx]\n\t"
		"mov [ebp+eax*4], edx\n\t"
		"pop ebp\n\t"
		"inc eax\n\t"
		"cmp eax, ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitPlayersASM1_jmp), "m" (nInitPlayersArray)
	);
}

uintptr_t InitPlayersASM2_jmp = 0x470C9D;
void __attribute__((naked)) InitPlayersASM2() {
	__asm__ (
		"mov eax, %1\n\t"
		"push ebp\n\t"
		"push eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitPlayersASM2_jmp), "m" (nInitPlayersArray)
	);
}

uintptr_t InitPlayersASM3_jmp = 0x470CB8;
void __attribute__((naked)) InitPlayersASM3() {
	__asm__ (
		"mov ecx, [esp+0x10]\n\t"
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov edi, [ebp+ecx*4]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitPlayersASM3_jmp), "m" (nInitPlayersArray)
	);
}

uintptr_t InitPlayersASM4_jmp = 0x470C80;
void __attribute__((naked)) InitPlayersASM4() {
	__asm__ (
		"mov ecx, ebx\n\t"
		"mov edx, %1\n\t"
		"sub ecx, edx\n\t"
		"lea esp, [esp+0]\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitPlayersASM4_jmp), "m" (nInitPlayersArray)
	);
}

uintptr_t InitPlayerSettingsASM_jmp = 0x45D9C2;
void __attribute__((naked)) InitPlayerSettingsASM() {
	__asm__ (
		"imul eax, 0x44\n\t"
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"lea esi, [eax+ebp+0x612-0x5F4]\n\t"
		"pop ebp\n\t"
		"push edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitPlayerSettingsASM_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM_jmp = 0x45DA53;
void __attribute__((naked)) ReadPlayerSettingsASM() {
	__asm__ (
		"mov eax, %1\n\t"
		"add eax, 0x34\n\t"
		"push edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM2_jmp = 0x49F187;
void __attribute__((naked)) ReadPlayerSettingsASM2() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx]\n\t"
		"pop ecx\n\t"
		"mov ecx, 0x11\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM2_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM3_jmp = 0x4A24F3;
void __attribute__((naked)) ReadPlayerSettingsASM3() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx]\n\t"
		"pop ecx\n\t"
		"mov ecx, 0x11\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM3_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM4_jmp = 0x497181;
void __attribute__((naked)) ReadPlayerSettingsASM4() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx]\n\t"
		"pop ecx\n\t"
		"mov ecx, 0x11\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM4_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM5_jmp = 0x497473;
void __attribute__((naked)) ReadPlayerSettingsASM5() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx]\n\t"
		"pop ecx\n\t"
		"mov eax, [esp+0x3C]\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM5_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM6_jmp = 0x498DE1;
void __attribute__((naked)) ReadPlayerSettingsASM6() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx]\n\t"
		"pop ecx\n\t"
		"mov ecx, 0x11\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM6_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM7_jmp = 0x498F03;
void __attribute__((naked)) ReadPlayerSettingsASM7() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx]\n\t"
		"pop ecx\n\t"
		"mov eax, [esp+0x58]\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM7_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM8_jmp = 0x45CD7B;
void __attribute__((naked)) ReadPlayerSettingsASM8() {
	__asm__ (
		"mov ecx, %1\n\t"
		"add ecx, 0x20\n\t"
		"mov ecx, [ecx]\n\t"
		"mov eax, [ebp+0x13BC]\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM8_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM9_jmp = 0x45A4A1;
void __attribute__((naked)) ReadPlayerSettingsASM9() {
	__asm__ (
		"mov edi, %1\n\t"
		"add edi, 0x20\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM9_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM10_jmp = 0x479B03;
void __attribute__((naked)) ReadPlayerSettingsASM10() {
	__asm__ (
		"push edx\n\t"
		"mov edx, %1\n\t"
		"cmp dword ptr [ecx+edx+0x2C], 5\n\t"
		"pop edx\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM10_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM11_jmp = 0x4610B4;
void __attribute__((naked)) ReadPlayerSettingsASM11() {
	__asm__ (
		"mov edi, %1\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM11_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM12_jmp = 0x479935;
void __attribute__((naked)) ReadPlayerSettingsASM12() {
	__asm__ (
		"push eax\n\t"
		"mov eax, %1\n\t"
		"cmp dword ptr [edx+eax+0x2C], 5\n\t"
		"pop eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM12_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM13_jmp = 0x46182F;
void __attribute__((naked)) ReadPlayerSettingsASM13() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [eax+ecx-0x44]\n\t"
		"pop ecx\n\t"
		"push esi\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM13_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM14_jmp = 0x45DFFF;
void __attribute__((naked)) ReadPlayerSettingsASM14() {
	__asm__ (
		"mov eax, [esp+0x120]\n\t"
		"imul eax, 0x44\n\t"
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"add ebp, 0x28\n\t"
		"mov eax, [eax+ebp]\n\t"
		"pop ebp\n\t"
		"dec eax\n\t"
		"mov dword ptr [esp+0xC], 0\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM14_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM15_jmp = 0x47AC2C;
void __attribute__((naked)) ReadPlayerSettingsASM15() {
	__asm__ (
		"push eax\n\t"
		"mov eax, %1\n\t"
		"cmp dword ptr [edx+eax+0x2C], 2\n\t"
		"pop eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM15_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM16_jmp = 0x484F73;
void __attribute__((naked)) ReadPlayerSettingsASM16() {
	__asm__ (
		"push edx\n\t"
		"mov edx, %1\n\t"
		"cmp dword ptr [eax+edx+0x2C], 5\n\t"
		"pop edx\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM16_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsASM17_jmp = 0x492DD7;
void __attribute__((naked)) ReadPlayerSettingsASM17() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"lea esi, [edx+ecx-0x44]\n\t"
		"pop ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsASM17_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsMPASM1_jmp = 0x4DEA7D;
void __attribute__((naked)) ReadPlayerSettingsMPASM1() {
	__asm__ (
		"push eax\n\t"
		"mov eax, %1\n\t"
		"lea edi, [edi+eax]\n\t"
		"pop eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsMPASM1_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsMPASM2_jmp = 0x4DF33C;
void __attribute__((naked)) ReadPlayerSettingsMPASM2() {
	__asm__ (
		"push eax\n\t"
		"mov eax, %1\n\t"
		"mov ecx, [edi+eax+0x40]\n\t"
		"pop eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsMPASM2_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsMPASM3_jmp = 0x4DFA34;
void __attribute__((naked)) ReadPlayerSettingsMPASM3() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"mov edi, [edx+ecx+0x40]\n\t"
		"pop ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsMPASM3_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t ReadPlayerSettingsMPASM4_jmp = 0x4DFF8D;
void __attribute__((naked)) ReadPlayerSettingsMPASM4() {
	__asm__ (
		"push ecx\n\t"
		"mov ecx, %1\n\t"
		"mov eax, [edi+ecx+0x40]\n\t"
		"pop ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (ReadPlayerSettingsMPASM4_jmp), "m" (nPlayerSettingsArray)
	);
}

void ClearPlayerSettings() {
	memset(nPlayerSettingsArray, 0, sizeof(tPlayerSettings) * nNumPlayers);
}

uintptr_t ClearPlayerSettingsASM_jmp = 0x45E411;
void __attribute__((naked)) ClearPlayerSettingsASM() {
	__asm__ (
		"pushad\n\t"
		"call %1\n\t"
		"popad\n\t"
		"jmp %0\n\t"
			:
			: "m" (ClearPlayerSettingsASM_jmp), "i" (ClearPlayerSettings)
	);
}

uintptr_t InitLocalPlayerSettingsASM1_jmp = 0x45D8FB;
void __attribute__((naked)) InitLocalPlayerSettingsASM1() {
	__asm__ (
		"mov edx, %1\n\t"
		"xor eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitLocalPlayerSettingsASM1_jmp), "m" (nPlayerSettingsArray)
	);
}

uintptr_t InitLocalPlayerSettingsASM2_jmp = 0x45D88A;
void __attribute__((naked)) InitLocalPlayerSettingsASM2() {
	__asm__ (
		"mov edx, %1\n\t"
		"push edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitLocalPlayerSettingsASM2_jmp), "m" (nPlayerSettingsArray)
	);
}

int __fastcall GetNumPlayersOfType(int type, void* a2) {
	int count = 0;
	for (int i = 0; i < nNumPlayers; i++) {
		if (nPlayerSettingsArray[i].nPlayerType == type) count++;
	}
	return count;
}

uintptr_t PlayerUpdaterASM1_jmp = 0x472688;
void __attribute__((naked)) PlayerUpdaterASM1() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %3\n\t" // v45
		"mov [ebp+ecx*4], eax\n\t"
		"pop ebp\n\t"
		"mov eax, [eax+0x33C]\n\t"
		"test eax, eax\n\t"
		"jz short loc_472680\n\t"
		"cmp byte ptr [eax+0x2924], 0\n\t"
		"jz short loc_472680\n\t"

		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov [ebp+ecx*4], eax\n\t"
		"pop ebp\n\t"
		"jmp short loc_472688\n\t"

		"loc_472680:\n\t"
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov dword ptr [ebp+ecx*4], 0\n\t"
		"pop ebp\n\t"
		"loc_472688:\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM1_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM2_jmp = 0x47270D;
void __attribute__((naked)) PlayerUpdaterASM2() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %3\n\t" // v45
		"mov edx, [ebp+eax*4]\n\t"
		"pop ebp\n\t"
		"inc eax\n\t"
		"cmp eax, edi\n\t"
		"mov [edx+0x69C], ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM2_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM3_jmp = 0x472726;
void __attribute__((naked)) PlayerUpdaterASM3() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM3_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM4_jmp = 0x47275B;
void __attribute__((naked)) PlayerUpdaterASM4() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM4_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM5_jmp = 0x472796;
void __attribute__((naked)) PlayerUpdaterASM5() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM5_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM6_jmp = 0x4727CB;
void __attribute__((naked)) PlayerUpdaterASM6() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM6_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM7_jmp = 0x472806;
void __attribute__((naked)) PlayerUpdaterASM7() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM7_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM8_jmp = 0x472826;
void __attribute__((naked)) PlayerUpdaterASM8() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov edi, [ebp+ebx*4]\n\t"
		"pop ebp\n\t"
		"test edi, edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM8_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM9_jmp = 0x472876;
void __attribute__((naked)) PlayerUpdaterASM9() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t" // v43
		"mov ecx, [ebp+eax*4]\n\t"
		"pop ebp\n\t"
		"test ecx, ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM9_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM10_jmp = 0x47287D;
void __attribute__((naked)) PlayerUpdaterASM10() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov [ebp+edi*4], ecx\n\t"
		"pop ebp\n\t"
		"inc edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM10_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM11_jmp = 0x4728EC;
void __attribute__((naked)) PlayerUpdaterASM11() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov eax, [ebp+esi*4]\n\t"
		"mov cl, [eax+0x6AE4]\n\t"
		"pop ebp\n\t"
		"test cl, cl\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM11_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM12_jmp = 0x47290C;
void __attribute__((naked)) PlayerUpdaterASM12() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov eax, [ebp+esi*4]\n\t"
		"mov cl, [eax+0x6AE4]\n\t"
		"pop ebp\n\t"
		"test cl, cl\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM12_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM13_jmp = 0x47292C;
void __attribute__((naked)) PlayerUpdaterASM13() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov eax, [ebp+esi*4]\n\t"
		"mov cl, [eax+0x6AE4]\n\t"
		"pop ebp\n\t"
		"test cl, cl\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM13_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM14_jmp = 0x47294C;
void __attribute__((naked)) PlayerUpdaterASM14() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov ebx, [ebp+esi*4]\n\t"
		"mov al, [ebx+0x6AE4]\n\t"
		"pop ebp\n\t"
		"test al, al\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM14_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM15_call = 0x42B5D0;
uintptr_t PlayerUpdaterASM15_jmp = 0x472969;
void __attribute__((naked)) PlayerUpdaterASM15() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"call %4\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM15_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45), "m" (PlayerUpdaterASM15_call)
	);
}

uintptr_t PlayerUpdaterASM16_jmp = 0x472734;
void __attribute__((naked)) PlayerUpdaterASM16() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %3\n\t" // v45
		"mov ecx, [ebp+esi*4]\n\t"
		"mov eax, [ecx]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM16_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM17_jmp = 0x472769;
void __attribute__((naked)) PlayerUpdaterASM17() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %3\n\t" // v45
		"mov ecx, [ebp+esi*4]\n\t"
		"mov eax, [ecx]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM17_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM18_jmp = 0x4727A4;
void __attribute__((naked)) PlayerUpdaterASM18() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %3\n\t" // v45
		"mov ecx, [ebp+esi*4]\n\t"
		"mov eax, [ecx]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM18_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM19_jmp = 0x4727D9;
void __attribute__((naked)) PlayerUpdaterASM19() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %3\n\t" // v45
		"mov ecx, [ebp+esi*4]\n\t"
		"mov eax, [ecx]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM19_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM20_jmp = 0x4728C6;
void __attribute__((naked)) PlayerUpdaterASM20() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov esi, [ebp+ebx*4]\n\t"
		"pop ebp\n\t"
		"mov ecx, ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM20_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45)
	);
}

uintptr_t PlayerUpdaterASM21_call = 0x42B440;
uintptr_t PlayerUpdaterASM21_jmp = 0x472899;
void __attribute__((naked)) PlayerUpdaterASM21() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov ebx, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"call %4\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM21_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45), "m" (PlayerUpdaterASM21_call)
	);
}

uintptr_t PlayerUpdaterASM22_call = 0x42B4C0;
uintptr_t PlayerUpdaterASM22_jmp = 0x4728AD;
void __attribute__((naked)) PlayerUpdaterASM22() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t" // v44
		"mov eax, [ebp+esi*4]\n\t"
		"pop ebp\n\t"
		"call %4\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerUpdaterASM22_jmp), "m" (nCameraArray43), "m" (nCameraArray44), "m" (nCameraArray45), "m" (PlayerUpdaterASM22_call)
	);
}

uintptr_t PlayerScoreboardASM1_jmp = 0x4B7D71;
void __attribute__((naked)) PlayerScoreboardASM1() {
	__asm__ (
		"mov [esp+0xC], edx\n\t"
		"push eax\n\t"
		"mov eax, %1\n\t"
		"mov [eax+ebp*8], ecx\n\t"
		"pop eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerScoreboardASM1_jmp), "m" (nPlayerScoreboardArray)
	);
}

uintptr_t PlayerScoreboardASM2_jmp = 0x4B7DBB;
void __attribute__((naked)) PlayerScoreboardASM2() {
	__asm__ (
		"mov dword ptr [esp+0x20], 0\n\t"
		"push eax\n\t"
		"mov eax, %1\n\t"
		"fstp dword ptr [eax+ebp*8+4]\n\t"
		"pop eax\n\t"
		"mov dword ptr [esp+0x24], 0\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerScoreboardASM2_jmp), "m" (nPlayerScoreboardArray)
	);
}

uintptr_t PlayerScoreboardASM3_jmp = 0x4BD6AE;
void __attribute__((naked)) PlayerScoreboardASM3() {
	__asm__ (
		"mov ebp, %1\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerScoreboardASM3_jmp), "m" (nPlayerScoreboardArray)
	);
}

uintptr_t PlayerScoreboardASM4_jmp = 0x4BDBEB;
void __attribute__((naked)) PlayerScoreboardASM4() {
	__asm__ (
		"mov esi, [ebp+0x9BC]\n\t"
		"mov edi, %1\n\t"
		"mov edi, [edi+ebx*8]\n\t"
		"mov edx, esi\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerScoreboardASM4_jmp), "m" (nPlayerScoreboardArray)
	);
}

uintptr_t PlayerScoreboardASM5_jmp = 0x4BDC17;
void __attribute__((naked)) PlayerScoreboardASM5() {
	__asm__ (
		"mov ecx, %1\n\t"
		"mov edx, [esp+0x14]\n\t"
		"fld dword ptr [ecx+edx*8+4]\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerScoreboardASM5_jmp), "m" (nPlayerScoreboardArray)
	);
}

uintptr_t ScoreboardArrayASM1_jmp = 0x4BD68E;
void __attribute__((naked)) ScoreboardArrayASM1() {
	__asm__ (
		"mov edi, %1\n\t"
		"rep stosd\n\t"
		"mov ecx, ebx\n\t"
		"and ecx, 3\n\t"
		"rep stosb\n\t"
		"mov ecx, edx\n\t"
		"shr ecx, 2\n\t"
		"xor eax, eax\n\t"
		"mov edi, %2\n\t"
		"rep stosd\n\t"
		"mov ecx, edx\n\t"
		"jmp %0\n\t"
			:
			: "m" (ScoreboardArrayASM1_jmp), "m" (nScoreboardArray108), "m" (nScoreboardArray110)
	);
}

uintptr_t ScoreboardArrayASM2_jmp = 0x4BD7E5;
void __attribute__((naked)) ScoreboardArrayASM2() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t"
		"sub ebp, 4\n\t" // todo not sure if this is needed
		"mov esi, [ebp+eax*4]\n\t"
		"xor edx, edx\n\t"
		"test ecx, ecx\n\t"
		"setz dl\n\t"
		"mov ebp, %1\n\t"
		"sub ebp, 4\n\t" // todo not sure if this is needed
		"mov dword ptr [ebp+eax*4], 1\n\t"
		"mov ebp, %2\n\t"
		"sub ebp, 4\n\t" // todo not sure if this is needed
		"lea eax, [ebp+eax*4]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (ScoreboardArrayASM2_jmp), "m" (nScoreboardArray108), "m" (nScoreboardArray110)
	);
}

uintptr_t ScoreboardArrayASM3_jmp = 0x4BDB41;
void __attribute__((naked)) ScoreboardArrayASM3() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov eax, [ebp+ebx*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (ScoreboardArrayASM3_jmp), "m" (nScoreboardArray108), "m" (nScoreboardArray110)
	);
}

uintptr_t ScoreboardArrayASM4_jmp = 0x4BDB59;
void __attribute__((naked)) ScoreboardArrayASM4() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %2\n\t"
		"mov eax, [ebp+ebx*4]\n\t"
		"pop ebp\n\t"
		"test eax, eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (ScoreboardArrayASM4_jmp), "m" (nScoreboardArray108), "m" (nScoreboardArray110)
	);
}

uintptr_t DerbyScoringArrayASM1_jmp = 0x47B93F;
void __attribute__((naked)) DerbyScoringArrayASM1() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov [ebp+ebx*4], eax\n\t"
		"mov ebp, %2\n\t"
		"mov [ebp+ebx*4], eax\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM1_jmp), "m" (nSomeDerbyScoringArray1), "m" (nSomeDerbyScoringArray2)
	);
}

uintptr_t DerbyScoringArrayASM2_jmp = 0x47B8F4;
void __attribute__((naked)) DerbyScoringArrayASM2() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov dword ptr [ebp+ebx*4], 0x3F000000\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM2_jmp), "m" (nSomeDerbyScoringArray1)
	);
}

uintptr_t DerbyScoringArrayASM3_jmp = 0x47B8F4;
void __attribute__((naked)) DerbyScoringArrayASM3() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"fstp dword ptr [ebp+ebx*4]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM3_jmp), "m" (nSomeDerbyScoringArray1)
	);
}

uintptr_t DerbyScoringArrayASM4_jmp = 0x47B930;
void __attribute__((naked)) DerbyScoringArrayASM4() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov dword ptr [ebp+ebx*4], 0x3F000000\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM4_jmp), "m" (nSomeDerbyScoringArray2)
	);
}

uintptr_t DerbyScoringArrayASM5_jmp = 0x47B93F;
void __attribute__((naked)) DerbyScoringArrayASM5() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"fstp dword ptr [ebp+ebx*4]\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM5_jmp), "m" (nSomeDerbyScoringArray2)
	);
}

uintptr_t DerbyScoringArrayASM6_jmp = 0x47BAF7;
void __attribute__((naked)) DerbyScoringArrayASM6() {
	__asm__ (
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"fcomp dword ptr [ebp+edi*4]\n\t"
		"pop ebp\n\t"
		"fnstsw ax\n\t"
		"test ah, 0x41\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM6_jmp), "m" (nSomeDerbyScoringArray1)
	);
}

uintptr_t DerbyScoringArrayASM7_jmp = 0x47BC57;
void __attribute__((naked)) DerbyScoringArrayASM7() {
	__asm__ (
		"push edi\n\t"
		"mov edi, %1\n\t"
		"fcomp dword ptr [edi+ebp*4]\n\t"
		"pop edi\n\t"
		"fnstsw ax\n\t"
		"test ah, 0x41\n\t"
		"jmp %0\n\t"
			:
			: "m" (DerbyScoringArrayASM7_jmp), "m" (nSomeDerbyScoringArray2)
	);
}

void __fastcall ResetCrashBonuses(uintptr_t pPlayer) {
	auto bonuses = (tPlayerBonuses*)(pPlayer + nNewPlayerStructCustomVarsBegin);
	for (int i = 0; i < nNumPlayers; i++) {
		bonuses[i].values[0] = 0; // 55C
		bonuses[i].values[1] = 0; // 560
		bonuses[i].values[2] = -10000; // 564
		bonuses[i].values[3] = -60000; // 568
		bonuses[i].values[4] = -60000; // 56C
		bonuses[i].values[5] = -60000; // 570
		bonuses[i].values[6] = -999999; // 574
	}
}

void __attribute__((naked)) ResetCrashBonusesASM() {
	__asm__ (
		"pushad\n\t"
		"mov ecx, eax\n\t"
		"call %0\n\t"
		"popad\n\t"
		"ret\n\t"
			:
			: "i" (ResetCrashBonuses)
	);
}

uintptr_t WriteCrashBonusesASM_jmp = 0x46E481;
void __attribute__((naked)) WriteCrashBonusesASM() {
	__asm__ (
		"mov esi, edi\n\t"
		"imul esi, 0x1C\n\t"
		"add esi, %1\n\t"
		"jmp %0\n\t"
			:
			: "m" (WriteCrashBonusesASM_jmp), "m" (nNewPlayerStructCustomVarsBegin)
	);
}

uintptr_t RenderArrayASM1_jmp = 0x4C9C20;
void __attribute__((naked)) RenderArrayASM1() {
	__asm__ (
		"lea eax, [ecx+ebx*8]\n\t"
		"push ebp\n\t"
		"mov ebp, %1\n\t"
		"mov [ebp+eax*4], edx\n\t"
		"pop ebp\n\t"
		"inc ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (RenderArrayASM1_jmp), "m" (nSomeRenderArray)
	);
}

// sets car and carskin in the playerinfo array
uintptr_t InitAIPlayerInfoASM_jmp = 0x45DDF4;
void __attribute__((naked)) InitAIPlayerInfoASM() {
	__asm__ (
		"mov edx, [eax+0x340]\n\t"
		"imul esi, 0x44\n\t"
		"mov ebp, %1\n\t"
		"lea ecx, [esi+ebp]\n\t"
		"sub ecx, 0x5F4\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitAIPlayerInfoASM_jmp), "m" (nPlayerSettingsArray)
	);
}

class Player {
public:
	virtual void _vf0() = 0;
	virtual void _vf1() = 0;
	virtual void _vf2() = 0;
	virtual void _vf3() = 0;
	virtual void _vf4() = 0;
	virtual void _vf5() = 0;
	virtual void _vf6() = 0;
	virtual void _vf7() = 0;
	virtual void _vf8() = 0;
	virtual void _vf9() = 0;
	virtual void _vf10() = 0;
	virtual void _vf11() = 0;
	virtual void _vf12() = 0;
	virtual void _vf13() = 0;
	virtual void _vf14() = 0;
	virtual void _vf15() = 0;
	virtual void _vf16() = 0;
	virtual void _vf17() = 0;
	virtual void _vf18() = 0;
	virtual void _vf19() = 0;
	virtual void TriggerEvent(int* properties) = 0;
};

void __fastcall GhostForMoreOpponents(Player* pPlayer) {
	if (nNumPlayers > 8) {
		int eventProperties[] = {6036, 0, 0, 0, 1000};
		pPlayer->TriggerEvent(eventProperties);
	}
}

uintptr_t GhostForMoreOpponentsASM_jmp = 0x42764C;
void __attribute__((naked)) GhostForMoreOpponentsASM() {
	__asm__ (
		"pushad\n\t"
		"mov ecx, [edi+0x463C]\n\t"
		"call %1\n\t"
		"popad\n\t"
		"mov ebp, [edi+0x1BEC]\n\t"
		"cmp ebp, [edi+0x1BF0]\n\t"
		"mov dword ptr [edi+0x6AA0], 0\n\t"
		"jmp %0\n\t"
			:
			: "m" (GhostForMoreOpponentsASM_jmp), "i" (GhostForMoreOpponents)
	);
}

uintptr_t PlayerHostCollisionsASM1_jmp = 0x4704D4;
void __attribute__((naked)) PlayerHostCollisionsASM1() {
	__asm__ (
		"mov eax, %1\n\t" // 209AC
		"mov [ebx+0x209D4], eax\n\t"
		"mov [ebx+0x209D0], eax\n\t"
		"mov [ebx+0x209DC], eax\n\t"
		"mov [ebx+0x209D8], eax\n\t"
		"mov eax, %2\n\t" // 209E4
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionsASM1_jmp), "m" (nSomeCarCollisionArray209AC), "m" (nSomeCarCollisionArray209E4)
	);
}

uintptr_t PlayerHostCollisionsASM2_jmp = 0x470786;
void __attribute__((naked)) PlayerHostCollisionsASM2() {
	__asm__ (
		"mov eax, %2\n\t" // 209E4
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionsASM2_jmp), "m" (nSomeCarCollisionArray209AC), "m" (nSomeCarCollisionArray209E4)
	);
}

uintptr_t PlayerHostCollisionsASM3_jmp = 0x4707D3;
void __attribute__((naked)) PlayerHostCollisionsASM3() {
	__asm__ (
		"mov eax, %1\n\t" // 209AC
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionsASM3_jmp), "m" (nSomeCarCollisionArray209AC), "m" (nSomeCarCollisionArray209E4)
	);
}

uintptr_t PlayerHostCollisionsASM4_jmp = 0x471A15;
void __attribute__((naked)) PlayerHostCollisionsASM4() {
	__asm__ (
		"mov eax, %1\n\t" // 209AC
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionsASM4_jmp), "m" (nSomeCarCollisionArray209AC), "m" (nSomeCarCollisionArray209E4)
	);
}

uintptr_t PlayerHostCollisionsASM5_jmp = 0x471A70;
void __attribute__((naked)) PlayerHostCollisionsASM5() {
	__asm__ (
		"mov eax, %2\n\t" // 209E4
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionsASM5_jmp), "m" (nSomeCarCollisionArray209AC), "m" (nSomeCarCollisionArray209E4)
	);
}

uintptr_t PlayerHostCollisionBoundsASM1_jmp = 0x470780;
void __attribute__((naked)) PlayerHostCollisionBoundsASM1() {
	__asm__ (
		"jz short loc_470780\n\t"
		"mov esi, edx\n\t"
		"add esi, %1\n\t"

		"loc_470773:\n\t"
		"add eax, 4\n\t"
		"cmp eax, esi\n\t"
		"jnz short loc_47077C\n\t"
		"mov eax, edx\n\t"

		"loc_47077C:\n\t"
		"cmp eax, ecx\n\t"
		"jnz short loc_470773\n\t"

		"loc_470780:\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM1_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM2_jmp = 0x4707C0;
void __attribute__((naked)) PlayerHostCollisionBoundsASM2() {
	__asm__ (
		"mov esi, edx\n\t"
		"add esi, %1\n\t"
		"lea ecx, [ecx+0]\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM2_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM3_jmp = 0x471A0F;
void __attribute__((naked)) PlayerHostCollisionBoundsASM3() {
	__asm__ (
		"jz short loc_471A0F\n\t"
		"mov esi, edx\n\t"
		"add esi, %1\n\t"

		"loc_471A02:\n\t"
		"add eax, 4\n\t"
		"cmp eax, esi\n\t"
		"jnz short loc_471A0B\n\t"
		"mov eax, edx\n\t"

		"loc_471A0B:\n\t"
		"cmp eax, ecx\n\t"
		"jnz short loc_471A02\n\t"

		"loc_471A0F:\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM3_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM4_jmp = 0x471A50;
void __attribute__((naked)) PlayerHostCollisionBoundsASM4() {
	__asm__ (
		"mov esi, edx\n\t"
		"add esi, %1\n\t"
		"lea esp, [esp+0]\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM4_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM5_jmp = 0x472B33;
void __attribute__((naked)) PlayerHostCollisionBoundsASM5() {
	__asm__ (
		"mov ebp, eax\n\t"
		"add ebp, %1\n\t"
		"cmp ecx, ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM5_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM6_jmp = 0x472AB8;
void __attribute__((naked)) PlayerHostCollisionBoundsASM6() {
	__asm__ (
		"mov ebp, eax\n\t"
		"add ebp, %1\n\t"
		"cmp ecx, ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM6_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM7_jmp = 0x472BB0;
void __attribute__((naked)) PlayerHostCollisionBoundsASM7() {
	__asm__ (
		"mov ebp, ecx\n\t"
		"add ebp, %1\n\t"
		"cmp edx, ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM7_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM8_jmp = 0x472C6A;
void __attribute__((naked)) PlayerHostCollisionBoundsASM8() {
	__asm__ (
		"mov esi, ecx\n\t"
		"add esi, %1\n\t"
		"cmp edx, esi\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM8_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM9_jmp = 0x472BF1;
void __attribute__((naked)) PlayerHostCollisionBoundsASM9() {
	__asm__ (
		"add ecx, %1\n\t"
		"mov [eax+0x209DC], ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM9_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM10_jmp = 0x472C17;
void __attribute__((naked)) PlayerHostCollisionBoundsASM10() {
	__asm__ (
		"add ecx, %1\n\t"
		"mov [eax+0x209D4], ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM10_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM11_jmp = 0x472CBE;
void __attribute__((naked)) PlayerHostCollisionBoundsASM11() {
	__asm__ (
		"mov ebx, ecx\n\t"
		"add ebx, %1\n\t"
		"cmp edx, ebx\n\t"
		"pop ebx\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM11_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t PlayerHostCollisionBoundsASM12_jmp = 0x472CF7;
void __attribute__((naked)) PlayerHostCollisionBoundsASM12() {
	__asm__ (
		"mov esi, ecx\n\t"
		"add esi, %1\n\t"
		"cmp edx, esi\n\t"
		"pop esi\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionBoundsASM12_jmp), "m" (nSomeCarCollisionArrayMaxCount)
	);
}

uintptr_t AIPortraitsASM1_jmp = 0x4BF85C;
void __attribute__((naked)) AIPortraitsASM1() {
	__asm__ (
		"push edi\n\t"
		"mov edi, %1\n\t"
		"mov ecx, [edi+ecx*4-4]\n\t"
		"pop edi\n\t"
		"jmp %0\n\t"
			:
			: "m" (AIPortraitsASM1_jmp), "m" (nAIPortraitsArray)
	);
}

struct tTexturePtrAssoc {
	const char* bedName = nullptr;
	void* outPtr = nullptr;
};
// 4B6500
auto LoadTextureWithBed = (void(__stdcall*)(void*, const char*, const char*, tTexturePtrAssoc*, int, int))0x4B6500;
void __stdcall LoadAIPortraitTextures(void* a1, const char* a2, const char* a3, tTexturePtrAssoc* a4, int a5, int a6) {
	// load the original ones since the ai_damage_bar textures are still used from it
	LoadTextureWithBed(a1, a2, a3, a4, a5, a6);

	memset(nAIPortraitsArray, 0, (nNumAIProfiles + 1) * sizeof(int));

	auto ptrAssoc = new tTexturePtrAssoc[nNumAIProfiles + 2]; // last one has to be null for it to fill properly
	for (int i = 0; i < nNumAIProfiles; i++) {
		auto str = new char[64];
		snprintf(str,64,"ai_face_%d", i);
		ptrAssoc[i].bedName = str;
		ptrAssoc[i].outPtr = &nAIPortraitsArray[i];
	}
	ptrAssoc[nNumAIProfiles].bedName = "ai_face_player";
	ptrAssoc[nNumAIProfiles].outPtr = &nAIPortraitsArray[nNumAIProfiles];

	LoadTextureWithBed(a1, a2, a3, ptrAssoc, 1, 2);

	for (int i = 0; i < nNumAIProfiles + 1; i++) {
		delete[] ptrAssoc[i].bedName;
	}
}

const wchar_t* __fastcall GetAIName(int id) {
	int nNumNames = nNumAIProfiles;
	const wchar_t* aNames[32] = {
			L"JACK BENTON",
			L"KATIE JACKSON",
			L"SOFIA MARTINEZ",
			L"SALLY TAYLOR",
			L"JASON WALKER",
			L"RAY CARTER",
			L"FRANK MALCOV",
			L"CURTIS WOLFE",
			L"LEWIS DURAN",
			L"LEI BING",
			L"JILL RICHARDS"
	};
	static bool bOnce = true;
	static wchar_t** aCustomNames = nullptr;
	if (bOnce) {
		aCustomNames = new wchar_t*[nNumNames];
		memset(aCustomNames, 0, sizeof(wchar_t*)*nNumNames);
		bOnce = false;
	}

	auto nameId = id % nNumNames;
	if (aCustomNames[nameId]) return aCustomNames[nameId];

	auto config = toml::parse_file("FlatOut2AILimitAdjuster_gcp.toml");
	auto str = (std::string)config["names"]["AI" + std::to_string(nameId + 1)].value_or("*NULL*");
	if (str != "*NULL*") {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		auto retStr = converter.from_bytes(str);
		auto wchar = new wchar_t[retStr.length()+1];
		wcscpy_s(wchar, retStr.length()+1, retStr.c_str());
		aCustomNames[nameId] = wchar;
		return aCustomNames[nameId];
	}
	return aNames[nameId];
}

void __attribute__((naked)) GetAINameASM() {
	__asm__ (
		"mov ecx, eax\n\t"
		"jmp %0\n\t"
			:
			: "i" (GetAIName)
	);
}

auto InitAIHooked_call = (void(__stdcall*)(void*, int))0x45D980;
void __stdcall InitAIHooked(void* a1, int count) {
	count = nNumAIToSpawn;
	return InitAIHooked_call(a1, count);
}

uintptr_t InitPlayersCountASM_jmp = 0x45DC58;
void __attribute__((naked)) InitPlayersCountASM() {
	__asm__ (
		"cmp esi, %1\n\t"
		"mov [esp+0x10], esi\n\t"
		"mov [esp+0x20], ecx\n\t"
		"jmp %0\n\t"
			:
			: "m" (InitPlayersCountASM_jmp), "m" (nNumPlayers)
	);
}

uintptr_t PlayerInfoDBInitCountASM_jmp = 0x45AB79;
void __attribute__((naked)) PlayerInfoDBInitCountASM() {
	__asm__ (
		"call dword ptr [edx+0xD0]\n\t"
		"inc esi\n\t"
		"cmp esi, %1\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerInfoDBInitCountASM_jmp), "m" (nNumPlayersForPlayerInfo)
	);
}

uintptr_t PlayerInfoDBWriteCountASM_jmp = 0x45A5DE;
void __attribute__((naked)) PlayerInfoDBWriteCountASM() {
	__asm__ (
		"add edi, 0x44\n\t"
		"cmp eax, %1\n\t"
		"mov [esp+0x10], eax\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerInfoDBWriteCountASM_jmp), "m" (nNumPlayersForPlayerInfo)
	);
}

uintptr_t CrashBonusCountASM_jmp = 0x46DE75;
void __attribute__((naked)) CrashBonusCountASM() {
	__asm__ (
		"mov dword ptr [ebx], 0xFFFF8AD0\n\t"
		"inc esi\n\t"
		"add ebx, 0x1C\n\t"
		"cmp esi, %1\n\t"
		"jmp %0\n\t"
			:
			: "m" (CrashBonusCountASM_jmp), "m" (nNumPlayers)
	);
}

uintptr_t PlayerHostCollisionCountASM1_jmp = 0x472B8F;
void __attribute__((naked)) PlayerHostCollisionCountASM1() {
	__asm__ (
		"cmp ecx, %1\n\t"
		"mov esi, 4\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionCountASM1_jmp), "m" (nNumPlayers)
	);
}

uintptr_t PlayerHostCollisionCountASM2_jmp = 0x472BD8;
void __attribute__((naked)) PlayerHostCollisionCountASM2() {
	__asm__ (
		"cmp ecx, %1\n\t"
		"mov edx, 0xFFFFFFFC\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionCountASM2_jmp), "m" (nNumPlayers)
	);
}

uintptr_t PlayerHostCollisionCountASM3_jmp = 0x472C9F;
void __attribute__((naked)) PlayerHostCollisionCountASM3() {
	__asm__ (
		"cmp ecx, %1\n\t"
		"push esi\n\t"
		"mov esi, 4\n\t"
		"jmp %0\n\t"
			:
			: "m" (PlayerHostCollisionCountASM3_jmp), "m" (nNumPlayers)
	);
}

void __fastcall DisplayPoolMemoryError(uintptr_t ptr) {
	MessageBoxA(nullptr, std::format("Out of poolmemory at 0x{:X}", ptr).c_str(), "Fatal error", 0x10);
	exit(0);
}

void __attribute__((naked)) PoolMemoryErrorASM1() {
	__asm__ (
		"mov ecx, esi\n\t"
		"jmp %0\n\t"
			:
			: "i" (DisplayPoolMemoryError)
	);
}

void __attribute__((naked)) PoolMemoryErrorASM2() {
	__asm__ (
		"mov ecx, edi\n\t"
		"jmp %0\n\t"
			:
			: "i" (DisplayPoolMemoryError)
	);
}

uintptr_t NitroCarCrashASM_jmp = 0x46EBA5;
void __attribute__((naked)) NitroCarCrashASM() {
	__asm__ (
		// using ebp as a counter
		"push ebp\n\t"
		"xor ebp, ebp\n\t"

		"start_46E96E:\n\t"
		"cmp ecx, ebp\n\t" // compare to counter
		"jz      loc_46E9BF\n\t"
		"push ecx\n\t"
		"push ebx\n\t"
		"mov ecx, %2\n\t"
		"mov ebx, ebp\n\t" // ebx = ebp * 0x1C
		"imul ebx, ebx, 0x1C\n\t"
		"add ecx, ebx\n\t"
		"add ecx, 4\n\t" // this checks for +0x560, base ptr is +0x55C
		"fld dword ptr [esi+ecx]\n\t"
		"pop ebx\n\t"
		"pop ecx\n\t"
		"fcomp   dword ptr [0x6970BC]\n\t"
		"fnstsw  ax\n\t"
		"test    ah, 0x41\n\t"
		"jnz     loc_46E9BF\n\t"
		"push ecx\n\t"
		"push ebx\n\t"
		"mov ecx, %2\n\t"
		"mov ebx, ebp\n\t" // ebx = ebp * 0x1C
		"imul ebx, ebx, 0x1C\n\t"
		"add ecx, ebx\n\t"
		"add ecx, 4\n\t" // this checks for +0x560, base ptr is +0x55C
		"fld dword ptr [esi+ecx]\n\t"
		"pop ebx\n\t"
		"pop ecx\n\t"
		"fsub    dword ptr [0x6970BC]\n\t"
		"fdiv    dword ptr [0x6970C0]\n\t"
		"fcom    dword ptr [0x67DB74]\n\t"
		"fnstsw  ax\n\t"
		"test    ah, 5\n\t"
		"jnp     loc_46E9AD\n\t"
		"fstp    st\n\t"
		"fld     dword ptr [0x67DB74]\n\t"

		"loc_46E9AD:\n\t"
		"fmul    dword ptr [0x67DEF8]\n\t"
		"fmul    dword ptr [0x6970C4]\n\t"
		"fmul    dword ptr [esp+0x10]\n\t"
		"faddp   st(1), st\n\t"

		// increment, jump back if not numplayers
		"loc_46E9BF:\n\t"
		"inc ebp\n\t"
		"cmp ebp, %1\n\t"
		"jne start_46E96E\n\t"

		// reset and continue
		"jmpout_46EBA5:\n\t"
		"pop ebp\n\t"
		"jmp %0\n\t"
			:
			: "m" (NitroCarCrashASM_jmp), "m" (nNumPlayers), "m" (nNewPlayerStructCustomVarsBegin)
	);
}

// lua functions
auto luaL_checknumber = (double(*)(void*, int))0x5B5F20;
auto lua_setfield = (void(*)(void*, int, const char*))0x5B4E70;
auto lua_pushcfunction = (void(*)(void*, void*, int))0x5B48A0;

int SetAICount(void* a1) {
	nNumAIToSpawn = luaL_checknumber(a1, 1);
	if (nNumAIToSpawn > nNumAI) {
		MessageBoxA(nullptr, std::format("LUA attempted to set the AI count further than the .toml maximum! (SetAICount({}), max is {})", nNumAIToSpawn, nNumAI).c_str(), "nya?!~", MB_ICONERROR);
		exit(0);
	}
	if (nNumAIToSpawn < 0) {
		MessageBoxA(nullptr, std::format("LUA attempted to set the AI count to an invalid value! (SetAICount({}))", nNumAIToSpawn).c_str(), "nya?!~", MB_ICONERROR);
		exit(0);
	}
	return 0;
}

auto lua_setfield_callback = (void(*)(void*, int, const char*))0x5B4E70;
void CustomLUAFunctions(void* lua, int field, const char* value) {
	lua_setfield_callback(lua, field, value);

	lua_pushcfunction(lua, (void*)&SetAICount, 0);
	lua_setfield(lua, -10002, "SetAICount");
}

auto FMODChannels1_call = (void(__stdcall*)(int))0x619F15;
void __stdcall FMODChannels1(int a1) {
	FMODChannels1_call(1024);
}

auto FMODChannels2_call = (void(__stdcall*)(int, int, int))0x61A3A9;
void __stdcall FMODChannels2(int a1, int a2, int a3) {
	FMODChannels2_call(a1, 1024, a3);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x202638) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using DRM-free v1.2 (.exe size of 2990080 bytes)", "nya?!~", MB_ICONERROR);
				exit(0);
				return TRUE;
			}

			// todo extend cupmanager at sub_457710

			auto config = toml::parse_file("FlatOut2AILimitAdjuster_gcp.toml");
			nNumAIToSpawn = nNumAI = config["main"]["ai_count"].value_or(7);
			nNumAIProfiles = config["main"]["ai_profile_count"].value_or(7);
			nNumPlayers = nNumAI + 1;
			nAISortingThing = new int[nNumPlayers];
			nInitPlayersArray = new int[nNumPlayers];
			nPlayerSettingsArray = new tPlayerSettings[nNumPlayers];
			nCameraArray43 = new int[nNumPlayers];
			nCameraArray44 = new int[nNumPlayers];
			nCameraArray45 = new int[nNumPlayers];
			nScoreboardArray108 = new int[nNumPlayers];
			nScoreboardArray110 = new int[nNumPlayers];
			nPlayerScoreboardArray = new tScoreboardPlayer[nNumPlayers];
			nSomeRenderArray = new int[nNumPlayers * 32];
			nSomeDerbyScoringArray1 = new float[nNumPlayers];
			nSomeDerbyScoringArray2 = new float[nNumPlayers];
			nSomeCarCollisionArray209AC = new int[nNumPlayers + 1];
			nSomeCarCollisionArray209E4 = new int[nNumPlayers + 1];
			nAIPortraitsArray = new int[nNumAIProfiles + 1];

			// capping PlayerInfo in the db to 160 for now, game crashes afterwards in AddMappedTable
			nNumPlayersForPlayerInfo = nNumPlayers;
			if (nNumPlayersForPlayerInfo > 160) nNumPlayersForPlayerInfo = 160;

			// setup ai profile count, offset the aicatchup and aihandicap ids
			NyaHookLib::Patch(0x408C58 + 1, nNumAIProfiles);
			NyaHookLib::Patch(0x408C6A + 1, nNumAIProfiles + 1);
			NyaHookLib::Patch(0x458EC7 + 6, nNumAIProfiles);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x458EDB, 0x459000); // don't load cars.cfg

			// ai faces are loaded at sub_4B8000
			// then accessed at 004BF856
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BF851, &AIPortraitsASM1);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x4B87BC, &LoadAIPortraitTextures);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x45D9C7, &GetAINameASM);

			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x45CD1E, &InitAIHooked);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x45E528, &InitAIHooked);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DC4D, &InitPlayersCountASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45AB6F, &PlayerInfoDBInitCountASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45A5D4, &PlayerInfoDBWriteCountASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45E26D, &AISortingThingASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45E372, &AISortingThingASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45E390, &AISortingThingASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x470C80, &InitPlayersASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x470C97, &InitPlayersASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x470CB0, &InitPlayersASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x470C74, &InitPlayersASM4);

			// playersettings read at 0x628
			// min offset is -0x34, 0x5F4
			// initialized at 0x612
			// min offset -0x1E, 0x5F4
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45D9B7, &InitPlayerSettingsASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DDE8, &InitAIPlayerInfoASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45D8F3, &InitLocalPlayerSettingsASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45D883, &InitLocalPlayerSettingsASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DC80, &GetNumPlayersOfType);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DA4C, &ReadPlayerSettingsASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x49F17B, &ReadPlayerSettingsASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4A24E7, &ReadPlayerSettingsASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x497175, &ReadPlayerSettingsASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x497468, &ReadPlayerSettingsASM5);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x498DD5, &ReadPlayerSettingsASM6);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x498EF8, &ReadPlayerSettingsASM7);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45CD6F, &ReadPlayerSettingsASM8);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45A49B, &ReadPlayerSettingsASM9);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x479AFB, &ReadPlayerSettingsASM10);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4610AE, &ReadPlayerSettingsASM11);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47992D, &ReadPlayerSettingsASM12);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x461827, &ReadPlayerSettingsASM13);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DFE6, &ReadPlayerSettingsASM14);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47AC24, &ReadPlayerSettingsASM15);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x484F6B, &ReadPlayerSettingsASM16);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x492DD0, &ReadPlayerSettingsASM17);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4DEA76, &ReadPlayerSettingsMPASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4DF335, &ReadPlayerSettingsMPASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4DFA2D, &ReadPlayerSettingsMPASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4DFF86, &ReadPlayerSettingsMPASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45E404, &ClearPlayerSettingsASM);

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472663, &PlayerUpdaterASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472700, &PlayerUpdaterASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472720, &PlayerUpdaterASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472755, &PlayerUpdaterASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472790, &PlayerUpdaterASM5);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4727C5, &PlayerUpdaterASM6);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472800, &PlayerUpdaterASM7);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472820, &PlayerUpdaterASM8);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472870, &PlayerUpdaterASM9);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472878, &PlayerUpdaterASM10);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4728E0, &PlayerUpdaterASM11);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472900, &PlayerUpdaterASM12);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472920, &PlayerUpdaterASM13);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472940, &PlayerUpdaterASM14);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472960, &PlayerUpdaterASM15);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47272E, &PlayerUpdaterASM16);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472763, &PlayerUpdaterASM17);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47279E, &PlayerUpdaterASM18);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4727D3, &PlayerUpdaterASM19);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4728C0, &PlayerUpdaterASM20);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472890, &PlayerUpdaterASM21);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4728A4, &PlayerUpdaterASM22);

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4B7D6A, &PlayerScoreboardASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4B7DA7, &PlayerScoreboardASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BD6A7, &PlayerScoreboardASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BDBE0, &PlayerScoreboardASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BDC08, &PlayerScoreboardASM5);

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BD66C, &ScoreboardArrayASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BD7C5, &ScoreboardArrayASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BDB38, &ScoreboardArrayASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4BDB50, &ScoreboardArrayASM4);

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47B937, &DerbyScoringArrayASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47B8EC, &DerbyScoringArrayASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47B8DE, &DerbyScoringArrayASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47B928, &DerbyScoringArrayASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47B922, &DerbyScoringArrayASM5);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47BAEE, &DerbyScoringArrayASM6);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47BC4E, &DerbyScoringArrayASM7);

			// rendering crashes with way too many cars, +254 off of scene ptr gets overwritten by 4C9C41
			// cant find anywhere this is read
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4C9C3E, &RenderArrayASM1);

			size_t nNewPlayerStructSize = nNewPlayerStructCustomVarsBegin + (0x1C * nNumPlayers);
			if (nNewPlayerStructSize < 0xF50) nNewPlayerStructSize = 0xF50;
			NyaHookLib::Patch(0x45DCE6 + 1, nNewPlayerStructSize); // local player
			NyaHookLib::Patch(0x45DDC7 + 1, nNewPlayerStructSize); // ai player
			NyaHookLib::Patch(0x45DA8B + 1, nNewPlayerStructSize); // network player

			// bonus array starts at +55C off of player
			// custom vars should therefore begin at +55C, size 0x380 for 32 players, size 0x1C each
			// bonus relocation
			NyaHookLib::Patch(0x46E3E3 + 2, nNewPlayerStructCustomVarsBegin);
			NyaHookLib::Patch(0x46E65F + 2, nNewPlayerStructCustomVarsBegin + 0x18); // +574
			NyaHookLib::Patch(0x46DE81 + 2, nNewPlayerStructCustomVarsBegin + 4); // +560
			NyaHookLib::Patch(0x46DE0C + 3, nNewPlayerStructCustomVarsBegin + 0xC); // +568
			NyaHookLib::Patch(0x46DE1F + 2, nNewPlayerStructCustomVarsBegin + 0xC); // +568
			NyaHookLib::Patch(0x46E3E9 + 1, nNumPlayers);
			NyaHookLib::Patch(0x46E665 + 4, nNumPlayers);
			NyaHookLib::Patch(0x46DEA2 + 4, nNumPlayers);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x46DE68, &CrashBonusCountASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x46E260, &ResetCrashBonusesASM);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x46E47B, &WriteCrashBonusesASM);
			// crashes are later calculated at 46E516, 46E973, 46E505, 46E513, 46E986

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x46E920, 0x46E96E);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x46E96E, &NitroCarCrashASM);

			NyaHookLib::Patch(0x42E1D2 + 2, nNumPlayers * 0xE0);
			NyaHookLib::Patch(0x42E1DD + 1, nNumPlayers * 0xE0);
			NyaHookLib::Patch(0x42E1F1 + 1, nNumPlayers * 0xE0);
			NyaHookLib::Patch(0x42E20A + 2, nNumPlayers * 0x1C0);
			NyaHookLib::Patch(0x42E218 + 1, nNumPlayers * 0x1C0);
			NyaHookLib::Patch(0x42E230 + 1, nNumPlayers * 0x1C0);
			// 42E19C array is an int8

			// this seems to be a "has collided" bool array but it's never read, only written to
			NyaHookLib::Fill(0x46E579, 0x90, 0x46E57E - 0x46E579);

			// 33 and above runs out of listnodes at 57B991
			if (nNumPlayers > 32) {
				int listnodeCount = nNumPlayers;
				int listnodeInitCount = listnodeCount - 1;
				int listnodeSize = (listnodeCount * 0xC) + 0x4;
				int listnodeLastOffset = listnodeSize - 0xC;
				NyaHookLib::Patch(0x650250 + 1, listnodeSize);
				NyaHookLib::Patch(0x650270 + 1, listnodeInitCount);
				NyaHookLib::Patch(0x65028B + 2, listnodeLastOffset);
			}
			// and 58BC56
			if (nNumPlayers > 32) {
				// size 128 for 32 cars
				int listnodeCount = nNumPlayers * 4;
				int listnodeInitCount = listnodeCount - 1;
				int listnodeSize = (listnodeCount * 0xC) + 0x4;
				int listnodeLastOffset = listnodeSize - 0xC;
				NyaHookLib::Patch(0x6504C0 + 1, listnodeSize);
				NyaHookLib::Patch(0x6504E0 + 1, listnodeInitCount);
				NyaHookLib::Patch(0x6504FB + 2, listnodeLastOffset);
			}
			// ragdoll data
			if (nNumAIProfiles > 15) {
				int listnodeCount = (nNumAIProfiles + 1) * 4;
				int listnodeInitCount = listnodeCount - 1;
				int listnodeSize = (listnodeCount * 0xC) + 0x4;
				int listnodeLastOffset = listnodeSize - 0xC;
				NyaHookLib::Patch(0x650790 + 1, listnodeSize);
				NyaHookLib::Patch(0x6507B0 + 1, listnodeInitCount);
				NyaHookLib::Patch(0x6507CB + 2, listnodeLastOffset);
			}
			// driver model
			if (nNumAIProfiles > 15) {
				int listnodeCount = (nNumAIProfiles + 1) * 4;
				int listnodeInitCount = listnodeCount - 1;
				int listnodeSize = (listnodeCount * 0xC) + 0x4;
				int listnodeLastOffset = listnodeSize - 0xC;
				NyaHookLib::Patch(0x650310 + 1, listnodeSize);
				NyaHookLib::Patch(0x650330 + 1, listnodeInitCount);
				NyaHookLib::Patch(0x65034B + 2, listnodeLastOffset);
			}

			// 57CD40 crashes with 127 cars
			// loading screen + 0x2C0 gets overwritten at 0057CC1E
			NyaHookLib::Patch<uint16_t>(0x57CBC5, 0x9090);

			// 472de9 crashes after a few seconds ingame at 126 opponents if you don't press start
			// crash at 472def when restarting a race
			// skipping the entire code branch for now
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472D9D, 0x472E75);

			// 43ccfb right after the loading screen on 126 player midwest ranch 1
			// 5ad2d8 on redpine river, feels more like lack of LAA than anything code related, this is a texture render function

			// derby crashes at 47b3bc after start race
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47B39E, 0x47B3FF);

			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x427636, &GhostForMoreOpponentsASM);
			NyaHookLib::Patch<uint8_t>(0x46C89A, 0xEB); // allow ai to ghost

			// 426907 reads car+0x6AA8, collision related
			// written to at 00472AD2 normally
			// array is written to at 00472C51
			// this odd check at 472AB3 looks like something interesting
			nSomeCarCollisionArrayMaxCount = nNumPlayers * 4 + 4;
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472B87, &PlayerHostCollisionCountASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472BD0, &PlayerHostCollisionCountASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472C96, &PlayerHostCollisionCountASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4704CE, &PlayerHostCollisionsASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x470780, &PlayerHostCollisionsASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4707CD, &PlayerHostCollisionsASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x471A0F, &PlayerHostCollisionsASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x471A6A, &PlayerHostCollisionsASM5);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x47076E, &PlayerHostCollisionBoundsASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4707BA, &PlayerHostCollisionBoundsASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4719FD, &PlayerHostCollisionBoundsASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x471A49, &PlayerHostCollisionBoundsASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472B2E, &PlayerHostCollisionBoundsASM5);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472AB3, &PlayerHostCollisionBoundsASM6);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472BAB, &PlayerHostCollisionBoundsASM7);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472C65, &PlayerHostCollisionBoundsASM8);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472BE8, &PlayerHostCollisionBoundsASM9);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472C0E, &PlayerHostCollisionBoundsASM10);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472CB8, &PlayerHostCollisionBoundsASM11);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x472CF1, &PlayerHostCollisionBoundsASM12);

			// FastestLapTime is at game + 0x544, array of 8?
			// best wrecker id is at game + 0x564
			// blast master id is at game + 0x568
			// fastest lap id is at game + 0x56C
			// daredevil id is at game + 0x570
			// written to in a lot of places but definitely overflowed
			// 0047D732 is the final result, likely overflowed
			// correct one seems to be 479F68
			// just skipping fastestlaptime write for all other players for now, as it's never read for anyone but the player
			NyaHookLib::Patch<uint16_t>(0x47D73E, 0x9090);

			// out of memory in dynamic pool made by 67CC88 vft
			// BVISUAL::VisibilitySet
			NyaHookLib::Patch(0x58AC23 + 3, 10000 * 10);

			int nNumTextures = nNumPlayers * 10; // should prolly be * 2 but just to be safe
			NyaHookLib::Patch(0x4512DF + 1, nNumTextures * 0x14);
			NyaHookLib::Patch(0x54D773 + 1, nNumTextures);
			NyaHookLib::Patch(0x54D7A8 + 2, nNumTextures * 0x14);
			NyaHookLib::Patch(0x54D7AE + 1, nNumTextures);

			NyaHookLib::Patch(0x69D2FC + 8, 8192 * 4); // texture pool memory max count

			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x54D273, &PoolMemoryErrorASM1);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x54D306, &PoolMemoryErrorASM2);

			lua_setfield_callback = (void(*)(void*, int, const char*))NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x452EC4, &CustomLUAFunctions);

			// add more bits to all previously 4bit synced values
			uintptr_t a4BitNetVFTs[] = {
					0x4EC3A7,
					0x4EC3D3,
					0x4EC3FF,
					0x4ECA9D,
					0x4ECACA,
					0x4ECAF6,
					0x4ECCE1,
					0x4ECD0D,
					0x4ECD39,
					0x4ECD65,
					0x4ECD91,
					0x4ECFEE,
					0x4ED01A,
					0x4ED046,
					0x4ED072,
			};
			for (auto& addr : a4BitNetVFTs) {
				NyaHookLib::Patch(addr, 0x66E4E4); // replace with int
			}
			// add more bits to lobby data
			NyaHookLib::Fill(0x51AFBB, 0x90, 3); // maxplayers
			NyaHookLib::Fill(0x51AFE7, 0x90, 3); // numplayers

			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x42077B, &FMODChannels1);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x4207AA, &FMODChannels2);

			// crash quitting a race at 42E9C8
			// player dtor, car->0x338, its object ptr

			// crash quitting a race at 532760
			// freeing something, heap is corrupt

			// 599E7A crashed on 126 player desert oil field
			// seems to be processing dynamic objects, something overwrote the ptr? this smells like pretty bad heap corruption

			// crash in 45affa with 1024 cars
			// is this dynamically allocated?

			//PlaceMemoryHooks();

			// 00472886 actually processes tires, that's funny :3
		} break;
		default:
			break;
	}
	return TRUE;
}