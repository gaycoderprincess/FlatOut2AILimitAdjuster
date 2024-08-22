#include <windows.h>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"

int nNumAI = 7;
int nNumPlayers = 8;
int* nAISortingThing = nullptr;
int* nInitPlayersArray = nullptr;
struct tPlayerSettings {
	uint8_t _0[0x2C];
	uint32_t nPlayerType;
	uint8_t _30[0x14];
};
static_assert(sizeof(tPlayerSettings) == 0x44);
tPlayerSettings* nPlayerSettingsArray = nullptr;
int* nCameraArray43 = nullptr;
int* nCameraArray44 = nullptr;
int* nCameraArray45 = nullptr;
int* nScoreboardArray108 = nullptr;
int* nScoreboardArray110 = nullptr;

struct tScoreboardPlayer {
	uint8_t _0[0x8];
};
tScoreboardPlayer* nPlayerScoreboardArray = nullptr;

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
		"mov eax, [ebp+esi*4]\n"
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
		"mov eax, [ebp+esi*4]\n"
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
		"mov eax, [ebp+esi*4]\n"
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
		"mov ebx, [ebp+esi*4]\n"
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
		"mov eax, [ebp+esi*4]\n"
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
		"mov ecx, ebp\n\t"
		"pop ebp\n\t"
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
		"pop ebp\n"
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

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x202638) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using DRM-free v1.2 (.exe size of 2990080 bytes)", "nya?!~", MB_ICONERROR);
				exit(0);
				return TRUE;
			}

			auto config = toml::parse_file("FlatOut2AILimitAdjuster_gcp.toml");
			nNumAI = config["main"]["ai_count"].value_or(7);
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

			NyaHookLib::Patch<uint8_t>(0x45CD01 + 1, nNumAI);
			NyaHookLib::Patch(0x45CD15 + 2, &nNumAI);
			NyaHookLib::Patch<uint8_t>(0x45CD1B, 0x90);
			NyaHookLib::Patch<uint8_t>(0x45DC4D + 2, nNumPlayers);
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
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45D8F3, &InitLocalPlayerSettingsASM1);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45D883, &InitLocalPlayerSettingsASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DC80, &GetNumPlayersOfType);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45DA4C, &ReadPlayerSettingsASM);

			// 4DEA76 for multiplayer sync
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x49F17B, &ReadPlayerSettingsASM2);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x4A24E7, &ReadPlayerSettingsASM3);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x497175, &ReadPlayerSettingsASM4);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x497468, &ReadPlayerSettingsASM5);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x498DD5, &ReadPlayerSettingsASM6);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x498EF8, &ReadPlayerSettingsASM7);
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x45CD6F, &ReadPlayerSettingsASM8);
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

			// temporary removal of some stuff related to bonuses
			NyaHookLib::PatchRelative(NyaHookLib::JMP, 0x46D786, 0x46D877);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x409509, 0x46E058);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x46DCAB, 0x46E058);
		} break;
		default:
			break;
	}
	return TRUE;
}