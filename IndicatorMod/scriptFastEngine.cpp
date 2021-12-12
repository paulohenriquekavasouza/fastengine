/*
	EN: CREATED BY PAULO HENRIQUE KAVA DE SOUZA - PHK 2017 JULY 26
	CREATED USING ALEXANDER BLADE'S CODE
	ONLY FOR GTA V. THIS SCRIPT ABLE YOU TO LET ON YOUR CAR ON MORE FASTER.

	BRAZIL 2017

	PT-BR: CRIADO POR PAULO HENRIQUE KAVA DE SOUZA - PHK 26 DE JULHO DE 2017
	CRIADO USANDO CODIGO DE ALEXANDER BLADE.
	SOMENTE PARA GTA V. ESTE SCRIPT POSSIBILITA VOCÊ LIGAR SEU CARRO RAPIDAMENTE.

	BRASIL 2017

*/

#include "scriptFastEngine.h"
#include "keyboard.h"

#include <string>
#include <ctime>
#include <tchar.h>

#pragma warning(disable : 4996) 
#pragma warning(disable : 4244 4305) 

#define DEVELOPER 0

using namespace std;

DWORD teclasSuportadas[22] = {
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,
	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9
};

LPCSTR teclasDisponiveis[22] = {
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9"
};

// KEYS AREA - START
bool key_pressed(DWORD keyV) {
	return IsKeyJustUp(keyV);
}
// KEYS AREA - END

// GRAPH AREA - START
void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7) {
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
}

void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, int r, int g, int b, bool rescaleText) {
	// default values
	int text_col[4] = {r, g, b, 255},
		rect_col[4] = {r, g, b, 255};
	float text_scale = 0.30;
	int font = 0;

	rect_col[0] = r;
	rect_col[1] = g;
	rect_col[2] = b;

	text_col[0] = r;
	text_col[1] = g;
	text_col[2] = b;

	// correcting values for active line
	if(active) {
		text_col[0] = r;
		text_col[1] = g;
		text_col[2] = b;

		rect_col[0] = r;
		rect_col[1] = g;
		rect_col[2] = b;

		if(rescaleText) text_scale = 0.40;
	}

	if(title) {
		rect_col[0] = r;
		rect_col[1] = g;
		rect_col[2] = b;

		if(rescaleText) text_scale = 0.50;
		font = 1;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height

	float lineLeftScaled = lineLeft / (float)screen_w;

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// text lower part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_GXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// rect
	draw_rect(lineLeftScaled, lineTopScaled + (0.00278f),
		lineWidthScaled, ((((float)(num25)* UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f),
		rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}

std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;

void update_status_text() {
	if (GetTickCount() < statusTextDrawTicksMax) {
		UI::_DRAW_TEXT(0.5, 0.5);
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry) {
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		} else {
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false) {
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}

void update_features() {
	update_status_text();
}
// GRAPH AREA - END

// VARIABLES
// READING KEY FROM nitroMod.ini FILE
LPCSTR versao = "1.0 (FINAL)";
LPCSTR arquivo = "fastEngine.ini";
bool scriptStarted = false;
bool arquivoEncontrado = false;
bool selecionouTeclaArquivo = false;
bool ligouCarro = false;
DWORD keyActiveMod = VK_F5;
char realKeyMod[32];

void notifyAboveMap(char* msg) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE); // = DRAW ABOVE MAP
}

void verificaArquivo() {
	/*FILE *file;

	file = fopen(arquivo, "r");

	if(file == NULL) {
		arquivoEncontrado = false;
	} else {
		arquivoEncontrado = true;

		LPCTSTR path = ".\\fastEngine.ini";

		if(selecionouTeclaArquivo == false) {
			GetPrivateProfileString(_T("CONFIGURATION"), _T("activateKeyScript"), _T(""), _T(realKeyMod), 32, path);

			for(int i = 0; i < 22; i++) {
				if(strcmp(_T(realKeyMod), teclasDisponiveis[i]) == 0) {
					keyActiveMod = teclasSuportadas[i];
				}
			}
		}

	}
	fclose(file);
	WAIT(0);*/
	arquivoEncontrado = true;
}

void mostraTextoEsquerda(char* texto) {
	UI::_0x8509B634FBE7DA11("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(texto);
	UI::_0x238FFE5C7B0498A6(0, 0, 1, -1);
}

void iniciaMod() {
	
	if(scriptStarted == true) {
		/*const int numElements = 10;
		const int arrSize = numElements * 2 + 2;
		int veh[arrSize];
		//0 index is the size of the array
		veh[0] = numElements;

		int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);

		if(veh != NULL) {
			//Simple loop to go through results
			for(int i = 0; i < count; i++) {
				int offsettedID = i * 2 + 2;
				//Make sure it exists
				if(veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID])) {
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh[offsettedID], false);
					VEHICLE::SET_VEHICLE_ALARM(veh[offsettedID], true);
				}
			}
		}*/

		
		Player playerPedId = PLAYER::PLAYER_PED_ID();
		if(ENTITY::DOES_ENTITY_EXIST(playerPedId) && PED::IS_PED_IN_ANY_VEHICLE(playerPedId, 1)) {
			if(ligouCarro == false) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPedId);				
				VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
				if(VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(veh)) {
					VEHICLE::SET_VEHICLE_ALARM(veh, false);
				}
				char text2[256];
				sprintf_s(text2, "~w~[~b~Fast Engine Mod~w~]\n~w~Car engine started ~g~faster~w~.\n--= By ~o~PhK ~w~=--");
				notifyAboveMap(text2);
				
				ligouCarro = true;
			}
		}
		if(ENTITY::DOES_ENTITY_EXIST(playerPedId) && PED::IS_PED_IN_ANY_VEHICLE(playerPedId, 0) == false) {
			if(ligouCarro == true) {
				ligouCarro = false;
			}
		}
	}
}

void main() {
	while (true) {
		verificaArquivo();		
		if (arquivoEncontrado == true) {
			scriptStarted = true;

			iniciaMod();			
		} else {
			keyActiveMod = VK_F5;
			DWORD time = GetTickCount() + 1000;
			while (GetTickCount() < time) {
				char text[256];
				sprintf_s(text, "-= File %s not found. Using F5 as default key. =-", arquivo);
				set_status_text(text);
				update_features();
				WAIT(0);
			}
		}
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
